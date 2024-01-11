#include <dmsdk/sdk.h>
#include "luautils.h"

void lua_pushtablestringstring(lua_State* L, const char* key, const char* value) {
	int top = lua_gettop(L);
	lua_pushstring(L, key);
	lua_pushstring(L, value);
	lua_settable(L, -3);
	assert(top == lua_gettop(L));
}

// void lua_pushtablestringfunction(lua_State* L, const char* key, lua_CFunction function) {
// 	int top = lua_gettop(L);
// 	lua_pushstring(L, key);
// 	lua_pushcfunction(L, function);
// 	lua_settable(L, -3);
// 	assert(top == lua_gettop(L));
// }

// void lua_printstack(lua_State* L) {
// 	int n = lua_gettop(L);
// 	for (int i = 1; i <= n; i++)  {
// 		dmLogInfo("STACK %d %s %s\r\n", i, lua_tostring(L, i), luaL_typename(L, i));
// 	}
// }

// void lua_setfieldstringstring(lua_State* L, const char* key, const char* value) {
// 	int top = lua_gettop(L);
// 	lua_pushstring(L, value);
// 	lua_setfield(L, -2, key);
// 	assert(top == lua_gettop(L));
// }

// void lua_setfieldstringnumber(lua_State* L, const char* key, const int value) {
// 	int top = lua_gettop(L);
// 	lua_pushnumber(L, value);
// 	lua_setfield(L, -2, key);
// 	assert(top == lua_gettop(L));
// }
