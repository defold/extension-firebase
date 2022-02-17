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
static dmScript::LuaCallbackInfo* g_AuthTokenCallback;

using namespace firebase;


static int Firebase_Init(lua_State* L) {
	DM_LUA_STACK_CHECK(L, 2);

#if defined (DM_DEBUG)
	FIR_PlatformDebugInit();
#endif

#if defined(DM_PLATFORM_ANDROID)
	JNIEnv* env = 0;
	dmGraphics::GetNativeAndroidJavaVM()->AttachCurrentThread(&env, NULL);
	firebase_app_ = App::Create(env, dmGraphics::GetNativeAndroidActivity());
#else
	firebase_app_ = App::Create();
#endif

	if(!firebase_app_)
	{
		lua_pushboolean(L, 0);
		lua_pushstring(L, "Failed to create Firebase App");
	}
	else
	{
		lua_pushboolean(L, 1);
		lua_pushnil(L);
	}

	return 2;
}

static int Firebase_GetAuthToken(lua_State* L) {
	DM_LUA_STACK_CHECK(L, 0);

	g_AuthTokenCallback = dmScript::CreateCallback(L, 1);

	auto* installations_object = installations::Installations::GetInstance(firebase::App::GetInstance());

	installations_object->GetToken(false)
		.OnCompletion([](const Future< std::string >& completed_future) {
		if (!dmScript::IsCallbackValid(g_AuthTokenCallback))
		{
			dmLogWarning("Firebase auth token callback is not valid");
			return;
		}

		if (dmScript::SetupCallback(g_AuthTokenCallback))
		{
			lua_State* L = dmScript::GetCallbackLuaContext(g_AuthTokenCallback);

			if (completed_future.error() == 0) {
				lua_pushstring(L, completed_future.result()->c_str());
				int ret = lua_pcall(L, 2, 0, 0);
				if (ret != 0) {
					lua_pop(L, 1);
				}
			}
			else {
				dmLogError("%d: %s", completed_future.error(), completed_future.error_message());
				lua_pushnil(L);
				lua_pushstring(L, completed_future.error_message());
				int ret = lua_pcall(L, 3, 0, 0);
				if (ret != 0) {
					lua_pop(L, 2);
				}
			}
			dmScript::TeardownCallback(g_AuthTokenCallback);
		}

		dmScript::DestroyCallback(g_AuthTokenCallback);
		g_AuthTokenCallback = 0;
			});
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
	lua_pushtablestringfunction(L, "get_auth_token", Firebase_GetAuthToken);

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
