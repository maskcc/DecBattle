local svc = require("service")
local player = require("player")
local utils = require("utils")
local cjson = require("cjson")

local gate = {}
local handler = {}
local users = {}

gate._F = "gate"

-- 接收新用户, 
-- 参数
-- argc.fd, 用户fd
-- argc.userid, 用户 userid
function handler.accept(argc)
	p = player.new(argc.fd, argc.userid)
	users[p.userid] = p
end

-- 添加用户信息
-- argc.userid 用户userid
-- argc 注册用户其他信息
function handler.add(argc)
	p = users[argc.userid]	
	p:init(argc)
end

-- 显示用户信息
-- argc.userid 需要显示的用户id
function handler.show(argc)
	p = users[argc.userid]	
	p:show()
end

-- 这是这个服务的回调函数
svc.register(function(typeid, msg, size)
	tmsg = cjson.decode(msg)
	f = handler[tmsg.cmd]
	if nil ~= f then
		f(tmsg)
	end
end)













return gate;
