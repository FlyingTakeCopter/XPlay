//
// Created by liuqikang on 2018/7/4.
//

#ifndef XPLAY_IPLAYERBUILDER_H
#define XPLAY_IPLAYERBUILDER_H


#include "IPlayer.h"

// 建造者模式，只需要通过builder进行构建播放器
class IPlayerBuilder {
public:
    virtual IPlayer* BuildPlayer(unsigned char index = 0);

protected:
    virtual IDemux* CreateDemux() = 0;
    virtual IDecode* CreateDecode() = 0;
    virtual IResample* CreateResample() = 0;
    virtual IAudioPlay* CreateAudioPlay() = 0;
    virtual IVideoView* CreateVideoView() = 0;

    virtual IPlayer* CreateIPlayer(unsigned char index = 0) = 0;
};


#endif //XPLAY_IPLAYERBUILDER_H
