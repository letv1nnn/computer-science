#![allow(unused)]

use std::{thread, time::Duration};
use futures_lite::future;
use crate::async_runtime_basic::{basic_async_runtime::spawn_task, testing_futures::{async_fn, CounterFuture}};

pub mod async_sleep;
pub mod basic_async_runtime;
pub mod testing_futures;

pub fn test_basic_async_runtime() {
    // running some futures in our runtime
    let one = CounterFuture { counter: 0 };
    let two = CounterFuture { counter: 0 };

    let t_one = spawn_task(one);
    let t_two = spawn_task(two);
    let t_three = spawn_task(async {
        async_fn().await;
        async_fn().await;
        async_fn().await;
        async_fn().await;        
    });

    thread::sleep(Duration::from_secs(3));
    println!("before the block");
    future::block_on(t_one);
    future::block_on(t_two);
    future::block_on(t_three);
}