#include <string>
#include <cassert>
#include <lua.hpp>
#include <errno.h>


int main() {
    lua_State *L = luaL_newstate();
    //int r = luaL_dofile(l, "bootstrap.lua");
 //   int r = luaL_loadfile(l, "bootstrap.lua");
    
  //  printf("result is %d\n", r);
   // perror(strerror(errno));
   // r = lua_pcall(l, 0, LUA_MULTRET, 0);
   // printf("result is %d\n", r);
   // perror(strerror(errno));
 luaL_openlibs(L);
    
int errorCode = 0;
if(errorCode != luaL_dofile(L,"bootstrap.lua"))
{
    puts(lua_tostring(L, -1));
    abort();
}


    // Clean up the lua context
    lua_close(L);
}
