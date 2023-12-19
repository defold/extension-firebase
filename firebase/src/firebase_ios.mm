#if defined(DM_PLATFORM_IOS)

#include <FirebaseInstallations/FirebaseInstallations.h>

#include "firebase_private.h"
#include "firebase_callback.h"

namespace dmFirebase {

    void SendSimpleMessage(Message msg, id obj) {
        NSError* error;
        NSData* jsonData = [NSJSONSerialization dataWithJSONObject:obj options:(NSJSONWritingOptions)0 error:&error];

        if (jsonData)
        {
            NSString* nsstring = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
            AddToQueueCallback(msg, (const char*)[nsstring UTF8String]);
            [nsstring release];
        }
        else
        {
            NSMutableDictionary *dict = [NSMutableDictionary dictionary];
            [dict setObject:error.localizedDescription forKey:@"error"];
            NSError* error2;
            NSData* errorJsonData = [NSJSONSerialization dataWithJSONObject:dict options:(NSJSONWritingOptions)0 error:&error2];
            if (errorJsonData)
            {
                NSString* nsstringError = [[NSString alloc] initWithData:errorJsonData encoding:NSUTF8StringEncoding];
                AddToQueueCallback(MSG_ERROR, (const char*)[nsstringError UTF8String]);
                [nsstringError release];
            }
            else
            {
                AddToQueueCallback(MSG_ERROR, [[NSString stringWithFormat:@"{ \"error\": \"Error while converting simple message to JSON.\"}"] UTF8String]);
            }
        }
    }

    void SendErrorMessage(NSError *error) {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        [dict setObject:error.localizedDescription forKey:@"error"];
        SendSimpleMessage(MSG_ERROR, dict);
    }

    void SendSimpleMessage(Message msg) {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        SendSimpleMessage(msg, dict);
    }

    void SendSimpleMessage(Message msg, NSString *key, NSString *value) {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        [dict setObject:value forKey:key];
        SendSimpleMessage(msg, dict);
    }

    void Initialize_Ext() {
        
    }

    bool SetOption(const char* key, const char* value) {
        
    }

    void Initialize() {
        @try {
            if(![FIRApp defaultApp]) {
                [FIRApp configure];
            }
            SendSimpleMessage(MSG_INITIALIZED);
        } @catch (NSException* e) {
            AddToQueueCallback(MSG_ERROR, [[NSString stringWithFormat:@"{ \"error\": \"Unable to init Firebase (%1$@)\"}", e.reason] UTF8String]);
        }
    }

    void GetInstallationAuthToken() {
        @try {
            [[FIRInstallations installations] authTokenForcingRefresh:true
                                                     completion:^(FIRInstallationsAuthTokenResult *result, NSError *error) {
                if (error != nil) {
                    SendErrorMessage(error);
                } else {
                    SendSimpleMessage(MSG_INSTALLATION_AUTH_TOKEN, @"id", [result authToken]);
                }
            }];
        } @catch (NSException* e) {
            AddToQueueCallback(MSG_ERROR, [[NSString stringWithFormat:@"{ \"error\": \"Unable to get auth token (%1$@)\"}", e.reason] UTF8String]);
        }
    }

    void GetInstallationId() {
        @try {
            [[FIRInstallations installations] installationIDWithCompletion:^(NSString *identifier, NSError *error) {
                if (error != nil) {
                    SendErrorMessage(error);
                } else {
                    SendSimpleMessage(MSG_INSTALLATION_ID, @"id", identifier);
                }
            }];		
        } @catch (NSException* e) {
            AddToQueueCallback(MSG_ERROR, [[NSString stringWithFormat:@"{ \"error\": \"Unable to get installation id (%1$@)\"}", e.reason] UTF8String]);
        }
    }

} // namespace dmFirebase

#endif // DM_PLATFORM_IOS