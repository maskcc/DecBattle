local utils = require("lobbylib.utils")
utils.log("test.lua", "none", "test log debug", 1)
utils.log("test.lua", "none", "test log warn", 2)
utils.log("test.lua", "none", "test log error", 4)

local b = loadfile("bootstrap.lua")
pcall(b)
