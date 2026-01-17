
local auth_token = arg[1]

if not auth_token or auth_token == '' then
    print('Usage: lua ./scripts/load_authorization_token.lua [token]')
    os.exit(1)
end

auth_token = auth_token:match("^%s*(.-)%s*$")

local config_path = "./configuration/base.yaml"

local file, err = io.open(config_path, 'r')
if not file then
    error('Failed to open config file: '..err)
end

local content = file:read('*a')

file:close()

local updated, count = content:gsub(
    'authorization_token:%s*".-"',
    'authorization_token: "' .. auth_token .. '"'
)

if count == 0 then
    error("authorization_token not found in base.yaml")
end

local file, err = io.open(config_path, 'w')
if not file then
    error("Could not open "..config_path.." for writing: "..err)
end

file:write(updated)
file:close()

print("authorization_token updated")