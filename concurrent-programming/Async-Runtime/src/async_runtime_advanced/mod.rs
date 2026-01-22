#![allow(unused)]

use futures_lite::future;
use crate::{
    async_runtime_advanced::advanced_async_runtime::FutureType,
    async_runtime_basic::testing_futures::{
        async_fn, CounterFuture
    },
};
use crate::async_runtime_advanced::advanced_async_runtime::spawn_task;

pub mod advanced_async_runtime;
pub mod testing_futures;

// Creating spawn_task, join and try_join macros, just like in tokio.
#[macro_export]
macro_rules! spawn_task {
    ($future:expr) => {
        spawn_task!($future, FutureType::Low)
    };
    ($future:expr, $order:expr) => {
        spawn_task($future, $order)
    };
}

#[macro_export]
macro_rules! join {
    ($($future:expr), *) => {
        {
            let mut results = Vec::new();
            $(
                results.push(futures_lite::future::block_on($future));
            )*
            results
        }
    };
}

#[macro_export]
macro_rules! try_join {
    ($($future:expr), *) => {
        {
            let mut results = Vec::new();
            $(
                let result = catch_unwind(|| future::block_on($future));
                results.push(result);
            )*
            results
        }
    };
}

pub fn test_advanced_async_runtime() {
    let one = CounterFuture {counter: 0};
    let two = CounterFuture {counter: 0};

    let t_one = spawn_task!(one, FutureType::High);
    let t_two = spawn_task!(two);
    let t_three = spawn_task!(async_fn());
    let t_four = spawn_task!(async {
        async_fn().await;
        async_fn().await;        
    }, FutureType::High);

    future::block_on(t_one);
    future::block_on(t_two);
    future::block_on(t_three);
    future::block_on(t_four);
}