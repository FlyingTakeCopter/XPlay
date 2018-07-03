//
// Created by liuqikang on 2018/7/3.
//

#ifndef XPLAY_SLAUDIOPLAY_H
#define XPLAY_SLAUDIOPLAY_H


#include "IAudioPlay.h"
#include "XParameter.h"

class SLAudioPlay : public IAudioPlay{
public:
    SLAudioPlay();
    virtual ~SLAudioPlay();

    virtual bool StartPlay(XParameter out);
    void PlayCall(void *bufq);

protected:
    unsigned char* buf = 0;//用来临时存储播放的data,在播放的回调函数中调用
};


#endif //XPLAY_SLAUDIOPLAY_H
