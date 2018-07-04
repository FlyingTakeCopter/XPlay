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
    // 打开解码器,ishard硬解码
    virtual bool Open(XParameter p, bool isHard = false) = 0;
    // feature模型 发送数据到线程解码
    virtual bool SendPacket(XData pkt) = 0;
    // 从线程中接收解码结果，再次调用会释放上次的空间，线程不安全
    virtual XData RecvFrame() = 0;
    // 对应IDemux::Main的Notify，生产者：将传入的XData加入解码队列尾部
    virtual void Update(XData data);

protected:
    // 解码主函数,从解码队列头部取数据进行解码，解码完成通知各观察者
    virtual void Main();

protected:
    // 标识流类型
    bool isAudio = false;
    // 读取缓冲队列
    std::list<XData> packs;
    // 队列最大缓冲帧数，缓冲单位精确到秒，maxList = 缓冲几秒 * 每秒帧数，数字过大会占用过大内存
    int maxList = 100;
    // 缓冲队列锁
    std::mutex packMutex;

};


#endif //XPLAY_IDECODE_H
