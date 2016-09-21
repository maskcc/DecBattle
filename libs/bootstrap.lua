#!code='utf-8'
local svc = require("service")
local utils = require("utils")
local snlua = require("lobbylib.snlua")
local core = require("lobbylib.core")
local cjson = require("cjson")


local bootstrap = {}
bootstrap._F = "bootstrap.lua"

utils.log(bootstrap._F, "none", "------ bootstrap start ------", utils._ERROR)

core.launch("gate.lua")
t = {}
t.msg = "good good study"
m = cjson.encode(t)
core.send("boots", "dbserver", 3, #m, m)

require "luatest"



