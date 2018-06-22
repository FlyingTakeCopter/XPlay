//
// Created by liuqikang on 2018/6/22.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H


#include "XData.h"

// 解封装接口类
class IDemux {
public:
    // 解封装 打开本地文件 或者流媒体 rtmp rtsp http
    virtual bool Open(const char* url) = 0;
    // 读取一帧数据，XData由调用者释放
    virtual XData Read() = 0;

    // 总时长 (毫秒)
    int totalms = 0;
};


#endif //XPLAY_IDEMUX_H
