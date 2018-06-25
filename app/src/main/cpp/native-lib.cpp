#include <jni.h>
#include <string>
#include "IDemux.h"
#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include <android/native_window_jni.h>

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

//    TestObs* testObs = new TestObs();
//    demux->AddObs(testObs);
    // 创建视频解码器
    IDecode*vDecode = new FFDecode();
    vDecode->Open(demux->GetVParameter());
    // 创建音频解码器
    IDecode*aDecode = new FFDecode();
    aDecode->Open(demux->GetAParameter());
    // 添加视频/音频解码器为demux的观察者
    demux->AddObs(vDecode);
    demux->AddObs(aDecode);

    demux->Start();// 线程读取，读取出一帧Notify到各观察者
    vDecode->Start();
    aDecode->Start();

    XSleep(3000);
    demux->Stop();

//    for (;;)
//    {
//        XData data = demux->Read();
//        XLOGI("packet size %d", data.size);
//    }


    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_xplay_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow*awin = ANativeWindow_fromSurface(env ,surface);

    XEGL::GetInstance()->Init(awin);
}