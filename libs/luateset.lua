--local utils = require("lobbylib.utils")
--utils.log("test.lua", "none", "test log debug", 1)
--utils.log("test.lua", "none", "test log warn", 2)
--utils.log("test.lua", "none", "test log error", 4)

--local b = loadfile("bootstrap.lua")
--pcall(b)
require "string"

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
a:show()
b:show()
c:show()
