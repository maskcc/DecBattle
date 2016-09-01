local load = load
local ipairs = ipairs
local table = table
local utils = require("lobbylib.utils")
local log = utils.log

local service = {}
service._FILE = "service.lua"
service._DEBUG = 1
service._WARN= 2
service._ERROR= 4

service._FILE = "service.lua"

function service.log(file, func, msg, level)
    err = "log type is not string"
    if("string" ~= type(file)) then
        error(err)
    end
    if("string" ~= type(func)) then
        error(err)
    end
    if("string" ~= type(msg)) then
        error(err)
    end
    if("number" ~= type(level)) then
        level = 1 --默认是debug绿色字体输出    
    end
    log(file, func, msg, level)
end





















return service
