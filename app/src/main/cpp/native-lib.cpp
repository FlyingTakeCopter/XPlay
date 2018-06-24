#include <jni.h>
#include <string>
#include "IDemux.h"
#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"

// 观察者测试类
class TestObs : public IObserver
{
public:
    TestObs(){}
    void Update(XData data) override {
        XLOGI("TestObs : accept data size = %d", data.size);
    }

};

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

    TestObs* testObs = new TestObs();
    demux->AddObs(testObs);

    IDecode*decode = new FFDecode();
    decode->Open(demux->GetXParameter());

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
