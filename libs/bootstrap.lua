#!code='utf-8'
local svc = require("service")
local utils = require("utils")
local snlua = require("lobbylib.snlua")


local bootstrap = {}
bootstrap._F = "bootstrap.lua"

utils.log(bootstrap._F, "none", "------ bootstrap start ------", utils._ERROR)

snlua.callback(function(a, b, c)
    utils.log(bootstrap._F, "none", tostring(a), utils._D)
    utils.log(bootstrap._F, "none", tostring(b), utils._D)
    utils.log(bootstrap._F, "none", tostring(c), utils._D)


end)

