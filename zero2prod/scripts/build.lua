-- build.lua
-- Simple task runner for Rust projects

local tasks = {}

local function run(cmd)
    print("> " .. cmd)
    local success, exit_type, code = os.execute(cmd)

    if not success then
        error(string.format(
            "Command failed (%s, code %d): %s",
            exit_type or "unknown",
            code or -1,
            cmd
        ))
    end
end

tasks.build = function()
    run('cargo build')
end

tasks.release = function()
    run('cargo build --release')
end

tasks.test = function()
    run('cargo test')
end

tasks.fmt = function()
    run("cargo fmt")
end

tasks.clippy = function()
    run("cargo clippy -- -D warnings")
end

tasks.all = function()
    tasks.fmt()
    tasks.clippy()
    tasks.test()
    tasks.build()
end

local task = arg[1]

if not task or not tasks[task] then
    print("Usage: lua build.lua [task]")
    print("Available tasks:")
    for name in pairs(tasks) do
        print("  - " .. name)
    end
    os.exit(1)
end

tasks[task]()
os.exit(0)
