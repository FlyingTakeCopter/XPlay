//
// Created by liuqikang on 2018/6/22.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H


#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

// 解封装接口类
class IDemux : public IObserver{
public:
    // 解封装 打开本地文件 或者流媒体 rtmp rtsp http
    virtual bool Open(const char* url) = 0;
    // 获取视频解码器参数
    virtual XParameter GetVParameter() = 0;
    // 获取音频解码器参数
    virtual XParameter GetAParameter() = 0;
    // 读取一帧数据，XData由调用者释放
    virtual XData Read() = 0;

    // 总时长 (毫秒)
    int totalms = 0;

    // 重载线程主函数
    virtual void Main();
};


#endif //XPLAY_IDEMUX_H
