use std::{future::Future, task::Poll, time::{Duration, Instant}};

pub struct AsyncSleep {
    start_time: Instant,
    duration: Duration
}

impl AsyncSleep {
    #[allow(unused)]
    fn new(duration: Duration) -> Self {
        Self {
            start_time: Instant::now(),
            duration
        }
    }
}

impl Future for AsyncSleep {
    type Output = bool;

    fn poll(self: std::pin::Pin<&mut Self>, cx: &mut std::task::Context<'_>) -> std::task::Poll<Self::Output> {
        let elapsed_time = self.start_time.elapsed();
        if elapsed_time >= self.duration {
            Poll::Ready(true)
        } else {
            cx.waker().wake_by_ref();
            Poll::Pending
        }
    }
}