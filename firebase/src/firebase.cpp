#define EXTENSION_NAME FirebaseExt
#define LIB_NAME "Firebase"
#define MODULE_NAME "firebase"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/dlib/log.h>
#include <dmsdk/sdk.h>

#include "firebase_private.h"
#include "firebase_callback.h"

#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

namespace dmFirebase {

static int Lua_Initialize(lua_State* L) {
    DM_LUA_STACK_CHECK(L, 0);
    if (lua_isnoneornil(L, 1))
    {
        Initialize();
    }
    else
    {
        ReadAppOptions(L, options);
    }
    return 0;
}

static int Lua_SetCallback(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    SetLuaCallback(L, 1);
    return 0;
}

static int Lua_GetInstallationAuthToken(lua_State* L) {
    DM_LUA_STACK_CHECK(L, 0);
    GetInstallationAuthToken();
    return 0;
}

static int Lua_GetInstallationId(lua_State* L) {
    DM_LUA_STACK_CHECK(L, 0);
    GetInstallationId();
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Lua_Initialize},
    {"set_callback", Lua_SetCallback},
    {"get_installation_auth_token", Lua_GetInstallationAuthToken},
    {"get_installation_id", Lua_GetInstallationId},
    {0, 0}
};


static void LuaInit(lua_State* L) {
    DM_LUA_STACK_CHECK(L, 0);

    luaL_register(L, MODULE_NAME, Module_methods);	

    #define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name); \

    SETCONSTANT(MSG_ERROR)
    SETCONSTANT(MSG_INITIALIZED)
    SETCONSTANT(MSG_INSTALLATION_AUTH_TOKEN)
    SETCONSTANT(MSG_INSTALLATION_ID)

    #undef SETCONSTANT

    lua_pop(L, 1);
}


//--------------------------- Extension callbacks -------------------------//

dmExtension::Result AppInitializeFirebaseExtension(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeFirebaseExtension(dmExtension::Params* params) {
    dmLogInfo("Initialize Firebase");

    LuaInit(params->m_L);
    Initialize_Ext();
    InitializeCallback();

    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeFirebaseExtension(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeFirebaseExtension(dmExtension::Params* params) {
    FinalizeCallback();
    return dmExtension::RESULT_OK;
}

dmExtension::Result UpdateFirebaseExtension(dmExtension::Params* params) {
    UpdateCallback();
    return dmExtension::RESULT_OK;
}

} // namespace dmFirebase

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmFirebase::AppInitializeFirebaseExtension, dmFirebase::AppFinalizeFirebaseExtension, dmFirebase::InitializeFirebaseExtension, dmFirebase::UpdateFirebaseExtension, 0, dmFirebase::FinalizeFirebaseExtension)

#else // defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS) 

//-------------------- Not supported for other platforms --------------------//

static  dmExtension::Result InitializeFirebase(dmExtension::Params* params)
{
    dmLogInfo("Registered extension Firebase (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeFirebase(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeFirebase, 0, 0, FinalizeFirebase)

#endif // defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS) 

