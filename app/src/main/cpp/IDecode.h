//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "XData.h"
#include "IObserver.h"
#include <list>

// 解码接口
class IDecode : public IObserver {
public:
    // 打开解码器
    virtual bool Open(XParameter p) = 0;
    // feature模型 发送数据到线程解码
    virtual bool SendPacket(XData pkt) = 0;
    // 从线程中接收解码结果
    virtual XData RecvFrame() = 0;
    // 相应主体IDemux::Main的Notify
    virtual void Update(XData data);

protected:
    // 解码主线程函数
    virtual void Main();

protected:
    // 标识流类型
    bool isAudio = false;
    // 读取缓冲队列
    std::list<XData> packs;
};


#endif //XPLAY_IDECODE_H
