#!code='utf-8'
local svc = require("service")
local utils = require("utils")
local snlua = require("lobbylib.snlua")
local core = require("lobbylib.core")
local cjson = require("cjson")


local bootstrap = {}
bootstrap._F = "bootstrap.lua"

utils.log(bootstrap._F, "none", "------ bootstrap start ------", utils._ERROR)

core.launch("gate.lua", "gate")
--require"luatest"
