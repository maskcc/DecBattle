local math = require("math")
require("class")
local player = class()

function player:ctor(fd, userid)
	self.fd = fd
	self.userid = userid
	self.login = 0
	self.passwd = 0
	self.name = ""
	self.sex = 0
	self.items = {}

end


function player:change_sex()
	self.sex = math.abs(1 - self.sex)
	print("now sex is", self.sex)
end

function player:init(info)
	self.login = 1
	self.passwd = info.passwd
	self.name = info.name
	self.sex = info.sex
	for k, v in pairs(info.items) do
		self.items[k] = v --Ç³¿½±´, »¹ÒªÐÞ¸Ä
	end
end

function player:show()
	print("player fd:",self.fd)
	print("player userid:",self.userid)
	print("player has login:",self.login)
	print("player passwd:",self.passwd)
	print("player name:",self.name)
	print("player sex:",self.sex)
	for k, v in pairs(self.items) do
		print("item:"..k, "count:",v)
	end
end
return player
