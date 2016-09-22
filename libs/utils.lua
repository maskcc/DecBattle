local load = load
local ipairs = ipairs
local table = table
local utl = require("lobbylib.utils")
local log = utl.log

local utils = {}
utils._F = "utils.lua" --file
utils._D = 1             --Debug
utils._W= 2              --Warn
utils._E= 4              --Error


function utils.log(file, func, msg, level)
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















return utils 
