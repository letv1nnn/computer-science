use std::{future::Future, task::Poll, thread, time::Duration};
use crate::async_runtime_advanced::advanced_async_runtime::{FutureOrderLabel, FutureType};

pub struct CounterFuture {
    pub count: u32,
    pub order: FutureType
}

impl Future for CounterFuture {
    type Output = u32;

    fn poll(mut self: std::pin::Pin<&mut Self>, cx: &mut std::task::Context<'_>) -> std::task::Poll<Self::Output> {
        self.count += 1;
        println!("polling with result: {}", self.count);
        thread::sleep(Duration::from_secs(1));
        if (self.count < 5) {
            cx.waker().wake_by_ref();
            return Poll::Pending;
        } else {
            return Poll::Ready(self.count)
        }
    }
}

impl FutureOrderLabel for CounterFuture {
    fn get_order(&self) -> FutureType {
        self.order
    }
}