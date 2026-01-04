use std::net::TcpListener;
use zero2prod::run;

const DEFAULT_ADDRESS: &str = "127.0.0.1:8000";

#[tokio::main]
async fn main() -> Result<(), std::io::Error> {
    let listener = TcpListener::bind(DEFAULT_ADDRESS).expect("Failed to bind address to listener!");
    run(listener)?.await
}
