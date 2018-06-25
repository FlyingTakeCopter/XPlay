//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:
    virtual bool Open(XParameter p);
    // 发送数据解码，内有判空处理
    virtual bool SendPacket(XData pkt);

    virtual XData RecvFrame();

protected:
    AVCodecContext*codecxt;
    AVFrame*frame;
};


#endif //XPLAY_FFDECODE_H
