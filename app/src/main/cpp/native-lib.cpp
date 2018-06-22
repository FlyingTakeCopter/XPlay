#include <jni.h>
#include <string>
#include "IDemux.h"
#include "FFDemux.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_xplay_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    IDemux* demux = new FFDemux();
    demux->Open("sdcard/ffmpegtest/1080.mp4");

    return env->NewStringUTF(hello.c_str());
}
