//
// Created by liuqikang on 2018/7/4.
//

#ifndef XPLAY_IPLAYER_H
#define XPLAY_IPLAYER_H

#include <ctime>
#include "XThread.h"
#include "XParameter.h"

class IDemux;
class IDecode;
class IResample;
class IAudioPlay;
class IVideoView;

class IPlayer : public XThread {
public:
    static IPlayer* Get(unsigned char index = 0);

    virtual bool Open(const char* path);

    virtual bool Start();

    virtual void InitView(void*win);

    IDemux* demux;
    IDecode* vDecode;
    IDecode* aDecode;
    IResample* resample;
    IAudioPlay* audioPlay;
    IVideoView* videoView;

    XParameter outP;
protected:
    IPlayer(){};
};


#endif //XPLAY_IPLAYER_H
