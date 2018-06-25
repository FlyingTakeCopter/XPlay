//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "XData.h"

// 解码接口
class IDecode {
public:
    // 打开解码器
    virtual bool Open(XParameter p) = 0;
    // feature模型 发送数据到线程解码
    virtual bool SendPacket(XData pkt) = 0;
    // 从线程中接收解码结果
    virtual XData RecvFrame() = 0;
};


#endif //XPLAY_IDECODE_H
