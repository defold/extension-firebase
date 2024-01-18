#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)
#pragma once

#include <dmsdk/sdk.h>

namespace dmFirebase {

enum Message
{
    MSG_ERROR =                   0,
    MSG_INITIALIZED =             1,
    MSG_INSTALLATION_AUTH_TOKEN = 2,
    MSG_INSTALLATION_ID =         3,
};

struct CallbackData
{
    Message msg;
    char* json;
};

void SetLuaCallback(lua_State* L, int pos);
void UpdateCallback();
void InitializeCallback();
void FinalizeCallback();

void AddToQueueCallback(Message type, const char* json);

} //namespace dmFirebase

#endif // defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)
