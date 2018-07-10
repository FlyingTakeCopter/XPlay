//
// Created by liuqikang on 2018/7/3.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver {
public:
    virtual void Update(XData data);// 接受重采样完成的数据,缓冲满之后阻塞

    virtual XData GetData();//获取缓冲数据，如没有会阻塞,在SLAudioPlay的播放回调函数中调用

    virtual bool StartPlay(XParameter out) = 0;

    int maxFrame = 100;//最大缓冲 单位：帧

    int pts;
protected:
    std::list<XData> frames;
    std::mutex frameMutex;
};


#endif //XPLAY_IAUDIOPLAY_H
