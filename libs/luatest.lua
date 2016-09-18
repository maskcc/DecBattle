--local utils = require("lobbylib.utils")
--utils.log("test.lua", "none", "test log debug", 1)
--utils.log("test.lua", "none", "test log warn", 2)
--utils.log("test.lua", "none", "test log error", 4)

--local b = loadfile("bootstrap.lua")
--pcall(b)
require "string"
local cjson = require "cjson"

require "class"

p = class()

function p:ctor(x)
	self.x = x
end

function p:show()
	print(self.x)
end

a = p.new(1)
b = p.new(2)
c = p.new(3)
--a:show()
--b:show()
--c:show()

local core = require("lobbylib.core")
data = cjson.encode({cmd="accept", fd=9, userid=12})
ret = core.call("gate.lua", 3, data, #data)

data = cjson.encode({cmd="add", userid=12, passwd="ss123", name="GQGQ", sex=1, items={["1400001"]=5, ["140002"] = 7}})
ret = core.call("gate.lua", 3, data, #data)


data = cjson.encode({cmd="show", userid=12})
ret = core.call("gate.lua", 3, data, #data)
