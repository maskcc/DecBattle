#include <string>
#include <cassert>
#include <lua.hpp>


int main() {
    lua_State *l = luaL_newstate();
    luaL_dofile(l, "bootstrap.lua");

    // Push function name to the stack
    lua_getglobal(l, "subtract_and_hello");
    // Push two numbers to the stack
    lua_pushinteger(l, 1);
    lua_pushinteger(l, 3);

    // Call the function
    const int num_args = 2;
    const int num_return_values = 2;
    lua_call(l, num_args, num_return_values);

    // Note that the stack is 1-indexed from the bottom
    const int diff = lua_tointeger(l, 1);
    const std::string greeting = lua_tostring(l, 2);

    // Pop the returned values from the stack
    lua_pop(l, 2);

    // Check that things worked correctly
    assert(diff == -2 && greeting == "hello");

    // Clean up the lua context
    lua_close(l);
}
