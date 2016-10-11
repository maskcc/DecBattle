local svc = require("service")
local player = require("player")
local utils = require("utils")
local cjson = require("cjson")
require("functions")

local gate = {}
local handler = {}
--local users = {}
gate.users = {}

gate._F = "gate"

-- 接收新用户, 
-- 参数
-- argc.fd, 用户fd
-- argc.userid, 用户 userid
function handler.accept(argc)
	local p = player.new(argc.fd, argc.userid)
    if nil == p then 
        print("malloc table item fail")
        print("fd"..argc.fd)
    end
	gate.users[p.userid] = p
end

-- 添加用户信息
-- argc.userid 用户userid
-- argc 注册用户其他信息
function handler.add(argc)
	local p = gate.users[argc.userid]	
    if nil ~= p then
	    p:init(argc)
    else
        print("add fail")
    end
end

-- 显示用户信息
-- argc.userid 需要显示的用户id
function handler.show(argc)
	local p = gate.users[argc.userid]	
    if(nil ~= p) then
	    p:show()
    else
        print("show p is nil")
    end
end
function handler.release(argc)
    for _,v in pairs (gate.users) do
        v:dtor()
    end
    print("del ok")
    gate.users = nil

    collectgarbage("collect")
    print("after collect")

end

-- 这是这个服务的回调函数
svc.register(function(typeid, msg, size)
    print(msg)
	local tmsg = cjson.decode(msg)
    dump(tmsg)
    --[[
    if(nil == tmsg.cmd) then
        print("msg's cmd is nil")
        return 
    end
	local f = handler[tmsg.cmd]
	if nil ~= f then
	    pcall(f, tmsg)
    else 
        print("can not find function ")
	end
    --]]
end)



return gate;
