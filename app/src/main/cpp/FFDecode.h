//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include <jni.h>
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:
    // 初始化硬解码
    static void InitHard(JavaVM*vm);

    virtual void Close();
    virtual bool Open(XParameter p, bool isHard);
    // 发送数据解码，内有判空处理
    virtual bool SendPacket(XData pkt);

    virtual XData RecvFrame();

protected:
    AVCodecContext*codecxt;
    AVFrame*frame;
    std::mutex mutex;
};


#endif //XPLAY_FFDECODE_H
