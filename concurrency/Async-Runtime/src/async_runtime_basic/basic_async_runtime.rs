use std::{future::Future, panic::catch_unwind, thread};
use std::sync::LazyLock;

use async_task::{Runnable, Task};

// Building a task-spawning function. This is where we pass a future into the function.
// The function then converts the future into a task and puts the task on the queue to be executed.
pub fn spawn_task<F, T>(future: F) -> Task<T>
where
    F: Future<Output = T> + Send + 'static,
    T: Send + 'static
{
    static QUEUE: LazyLock<flume::Sender<Runnable>> = LazyLock::new(|| {
        // channel and mechanism for receiving futures sent to the channel.
        let (tx, rx) = flume::unbounded::<Runnable>();
        // small thread pool
        for _ in 0..3 {
            let receiver = rx.clone();
            thread::spawn(move || {
                while let Ok(runnable) = receiver.recv() {
                    println!("runnable accepted");
                    let _ = catch_unwind(|| runnable.run());
                }
            });
        }
        tx
    });
  
    let schedule = |runnable| QUEUE.send(runnable).unwrap();
    let (runnable, task) = async_task::spawn(future, schedule);
    // put the task on the queue to be processed.
    runnable.schedule();
    println!("Here is the queue count: {:?}", QUEUE.len());
    task
}
