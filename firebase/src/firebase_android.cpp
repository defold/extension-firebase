#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>
#include "com_defold_firebase_FirebaseJNI.h"
#include "firebase_private.h"
#include "firebase_callback.h"


JNIEXPORT void JNICALL Java_com_defold_firebase_FirebaseJNI_firebaseAddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmFirebase::AddToQueueCallback((dmFirebase::Message)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}


namespace dmFirebase {

    struct FirebaseJNI {
        jobject        m_FirebaseJNI;

        jmethodID      m_Initialize;
        jmethodID      m_GetInstallationAuthToken;
        jmethodID      m_GetInstallationId;
        jmethodID      m_SetOption;
    };

    static FirebaseJNI g_firebase;

    static void CallVoidMethod(jobject instance, jmethodID method)
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        env->CallVoidMethod(instance, method);
    }

    static bool CallBoolMethodCharChar(jobject instance, jmethodID method, const char* cstr, const char* cstr2)
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        jstring jstr = env->NewStringUTF(cstr);
        jstring jstr2 = env->NewStringUTF(cstr2);
        jboolean return_value = (jboolean)env->CallBooleanMethod(instance, method, jstr, jstr2);
        env->DeleteLocalRef(jstr);
        env->DeleteLocalRef(jstr2);
        return JNI_TRUE == return_value;
    }

    static void InitJNIMethods(JNIEnv* env, jclass cls)
    {
        g_firebase.m_Initialize = env->GetMethodID(cls, "initialize", "()V");
        g_firebase.m_GetInstallationAuthToken = env->GetMethodID(cls, "getInstallationAuthToken", "()V");
        g_firebase.m_GetInstallationId = env->GetMethodID(cls, "getInstallationId", "()V");
        g_firebase.m_SetOption = env->GetMethodID(cls, "setOption", "(Ljava/lang/String;Ljava/lang/String;)Z");
    }

    void Initialize_Ext() {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        jclass cls = dmAndroid::LoadClass(env, "com.defold.firebase.FirebaseJNI");

        InitJNIMethods(env, cls);

        jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");

        g_firebase.m_FirebaseJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
    }


    void Initialize() {
        CallVoidMethod(g_firebase.m_FirebaseJNI, g_firebase.m_Initialize);
    }

    void GetInstallationAuthToken() {
        CallVoidMethod(g_firebase.m_FirebaseJNI, g_firebase.m_GetInstallationAuthToken);
    }

    void GetInstallationId() {
        CallVoidMethod(g_firebase.m_FirebaseJNI, g_firebase.m_GetInstallationId);
    }

    bool SetOption(const char* key, const char* value) {
        return CallBoolMethodCharChar(g_firebase.m_FirebaseJNI, g_firebase.m_SetOption, key, value);
    }

} //namespace dmAdmob

#endif // DM_PLATFORM_ANDROID
