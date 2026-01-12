FROM lukemathwalker/cargo-chef:latest AS chef
WORKDIR /app
RUN apt update && apt install lld clang -y

FROM chef AS planner
COPY . .
# Compute a lock-like file for our project
RUN cargo chef prepare  --recipe-path recipe.json

FROM chef AS builder
COPY --from=planner /app/recipe.json recipe.json
# Build our project dependencies, not our application!
RUN cargo chef cook --release --recipe-path recipe.json
COPY . .
ENV SQLX_OFFLINE true
# Build our project
RUN cargo build --release --bin zero2prod

# Runtime stage
FROM debian:testing-slim AS runtime
WORKDIR /app
# Install OpenSSL - it is dynamically linked be some of our dependecies
# Install ca-cerificates - it is needed to verify TLS cerificates
# when establishing HTTPS connections
RUN apt-get update -y \
    && apt-get install -y --no-install-recommends openssl ca-certificates \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*
COPY --from=builder /app/target/release/zero2prod zero2prod
# We need the configuration file at runtime.
COPY configuration configuration
# setting the app_env
ENV APP_ENVIRONMENT production
# Launching the binary
ENTRYPOINT ["./zero2prod"]

