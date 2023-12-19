#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#pragma once

namespace dmFirebase {

void Initialize_Ext();

void Initialize();
void GetInstallationAuthToken();
void GetInstallationId();

bool SetOption(const char* key, const char* value);

} //namespace dmFirebase

#endif

