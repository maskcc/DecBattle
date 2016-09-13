local load = load
local ipairs = ipairs
local table = table
local utils = require("utils")
local snlua = require("lobbylib.snlua")
local core = require("lobbylib.core")
local cjson = require("cjson")


local utils = {}
local service = {}
service._F = "service.lua"

-- 注册回调函数
-- fun 回调函数
-- 函数参数类型要符合 integer type, string msg, integer size
function service.register(fun)
	snlua.callback(fun)
end 

-- 调用回调
-- sname service name
-- type 类型
-- msg 参数table, 在这里打包成json
function service.call(sname, typeid, msg)
	encodeMsg = cjson.encode(msg)
	ret = core.call(sname, typeid, encodeMsg, #encodeMsg)
	return ret
end 


return service
