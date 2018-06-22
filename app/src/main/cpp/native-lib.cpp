#include <jni.h>
#include <string>
#include "IDemux.h"
#include "FFDemux.h"
#include "XLog.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_xplay_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    ///////////////////////////////////////////////////
    // 测试代码
    IDemux* demux = new FFDemux();
    demux->Open("sdcard/ffmpegtest/1080.mp4");
    demux->Start();

    XSleep(3000);
    demux->Stop();
//    for (;;)
//    {
//        XData data = demux->Read();
//        XLOGI("packet size %d", data.size);
//    }


    return env->NewStringUTF(hello.c_str());
}
