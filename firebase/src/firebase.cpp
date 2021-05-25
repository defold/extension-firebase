#define LIB_NAME "Firebase"
#define MODULE_NAME "firebase"
#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/dlib/log.h>
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#include "luautils.h"
#include "platform_utils.h"
#include "firebase/app.h"


static firebase::App* firebase_app_;

using namespace firebase;


static int Firebase_Init(lua_State* L) {
	DM_LUA_STACK_CHECK(L, 0);
	dmLogInfo("Firebase_Init");

#if defined (DM_DEBUG)
	// do some stuff for debug purposes
	FIR_PlatformDebugInit();
#endif
#if defined(DM_PLATFORM_ANDROID)
	dmLogInfo("Creating app");
	JNIEnv* env = 0;
	dmGraphics::GetNativeAndroidJavaVM()->AttachCurrentThread(&env, NULL);
	firebase_app_ = App::Create(env, dmGraphics::GetNativeAndroidActivity());
#else
	dmLogInfo("Creating app");
	firebase_app_ = App::Create();
#endif

	if(!firebase_app_) {
		dmLogError("firebase::App::Create failed");
		return 0;
	}

	dmLogInfo("Firebase_Init done");
	return 0;
}


firebase::App* Firebase_GetFirebaseApp()
{
	return firebase_app_;
}

static void LuaInit(lua_State* L) {
	DM_LUA_STACK_CHECK(L, 0);

	// get or create firebase global table
	lua_getglobal(L, "firebase");
	if (lua_isnil(L, lua_gettop(L)))
	{
		lua_pushstring(L, "firebase");
		lua_newtable(L);
		lua_settable(L, LUA_GLOBALSINDEX);
		lua_pop(L, 1);
		lua_getglobal(L, "firebase");
	}

	// push functions on the firebase global table
	lua_pushtablestringfunction(L, "init", Firebase_Init);

	lua_pop(L, 1); // pop "firebase" global table
}

#endif


dmExtension::Result AppInitializeFirebaseExtension(dmExtension::AppParams* params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeFirebaseExtension(dmExtension::Params* params) {
#if !defined(DM_PLATFORM_ANDROID) && !defined(DM_PLATFORM_IOS)
	dmLogInfo("Extension %s is not supported", LIB_NAME);
#else
	LuaInit(params->m_L);
#endif
	return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeFirebaseExtension(dmExtension::AppParams* params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeFirebaseExtension(dmExtension::Params* params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result UpdateFirebaseExtension(dmExtension::Params* params) {
	return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(Firebase, LIB_NAME, AppInitializeFirebaseExtension, AppFinalizeFirebaseExtension, InitializeFirebaseExtension, UpdateFirebaseExtension, 0, FinalizeFirebaseExtension)
