local load = load
local ipairs = ipairs
local table = table
local utils = require("utils")
local snlua = require("lobbylib.snlua")

local utils = {}
local service = {}
service._F = "service.lua"

function service.register(fun)
	snlua.callback(fun)
end














return service
