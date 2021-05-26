#pragma once

#include <dmsdk/sdk.h>


void lua_pushtablestringstring(lua_State* L, const char* key, const char* value);
void lua_pushtablestringfunction(lua_State* L, const char* key, lua_CFunction function);
void lua_printstack(lua_State* L);
void lua_setfieldstringstring(lua_State* L, const char* key, const char* value);
