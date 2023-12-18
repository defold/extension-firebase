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
    };

    static FirebaseJNI g_firebase;

    static void CallVoidMethod(jobject instance, jmethodID method)
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        env->CallVoidMethod(instance, method);
    }

    static void InitJNIMethods(JNIEnv* env, jclass cls)
    {
        g_firebase.m_Initialize = env->GetMethodID(cls, "initialize", "()V");
        g_firebase.m_GetInstallationAuthToken = env->GetMethodID(cls, "getInstallationAuthToken", "()V");
        g_firebase.m_GetInstallationId = env->GetMethodID(cls, "getInstallationId", "()V");    
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

} //namespace dmAdmob

#endif // DM_PLATFORM_ANDROID
