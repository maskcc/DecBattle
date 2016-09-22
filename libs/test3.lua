#!code='utf-8'
local cjson = require("cjson")


for i = 1, 500000 do
    t = {}
    t.msg = "good good study"
    m = cjson.encode(t)
    a = cjson.decode(m)
end
print("ok")

--require "luatest"



