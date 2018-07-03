//
// Created by liuqikang on 2018/7/3.
//

#ifndef XPLAY_SLAUDIOPLAY_H
#define XPLAY_SLAUDIOPLAY_H


#include "IAudioPlay.h"
#include "XParameter.h"

class SLAudioPlay : public IAudioPlay{
public:
    virtual bool StartPlay(XParameter out);
    void PlayCall(void *bufq);
};


#endif //XPLAY_SLAUDIOPLAY_H
