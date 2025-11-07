use std::{future::Future, task::Poll, thread, time::Duration};

pub struct CounterFuture {
    pub counter: u32,
}

impl Future for CounterFuture {
    type Output = u32;

    fn poll(mut self: std::pin::Pin<&mut Self>, cx: &mut std::task::Context<'_>) -> std::task::Poll<Self::Output> {
        self.counter += 1;
        println!("polling with result: {}", self.counter);
        thread::sleep(Duration::from_secs(1));
        if self.counter < 5 {
            cx.waker().wake_by_ref();
            Poll::Pending
        } else {
            Poll::Ready(self.counter)
        }
    }
}

pub async fn async_fn() {
    thread::sleep(Duration::from_secs(1));
    println!("async function");
}