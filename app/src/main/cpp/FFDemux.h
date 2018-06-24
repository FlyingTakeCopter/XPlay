//
// Created by liuqikang on 2018/6/22.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H


#include "IDemux.h"
struct AVFormatContext;

class FFDemux : public IDemux {
public:
    // 解封装 打开本地文件 或者流媒体 rtmp rtsp http
    virtual bool Open(const char* url);

    virtual XParameter GetXParameter();

    // 读取一帧数据，XData由调用者释放
    virtual XData Read();

    FFDemux();

public:
    AVFormatContext*ic = 0;//头文件中初始化，只适用于构造函数没有参数(C++11的坑)

};


#endif //XPLAY_FFDEMUX_H
