#include <jni.h>
#include <string>
#include "IPlayerProxy.h"
#include <android/native_window_jni.h>

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm,void *res)
{
    IPlayerProxy::Get()->Init(vm);
    IPlayerProxy::Get()->Open("sdcard/ffmpegtest/bolan.mp4");
    IPlayerProxy::Get()->Start();
    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_xplay_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow*awin = ANativeWindow_fromSurface(env ,surface);
    IPlayerProxy::Get()->InitView(awin);
}

extern "C"
JNIEXPORT jstring
JNICALL
Java_xplay_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";



    return env->NewStringUTF(hello.c_str());
}

