//
// Created by liuqikang on 2018/7/4.
//

#ifndef XPLAY_FFPLAYERBUILDER_H
#define XPLAY_FFPLAYERBUILDER_H


#include <jni.h>
#include "IPlayerBuilder.h"

class FFPlayerBuilder : public IPlayerBuilder {
public:
    // 初始化硬解码
    static void InitHard(JavaVM*vm);
    static FFPlayerBuilder*Get()
    {
        static FFPlayerBuilder builder;
        return &builder;
    }
protected:
    FFPlayerBuilder(){}
    virtual IDemux *CreateDemux();
    virtual IDecode *CreateDecode();
    virtual IResample *CreateResample();
    virtual IAudioPlay *CreateAudioPlay();
    virtual IVideoView *CreateVideoView();
    virtual IPlayer *CreateIPlayer(unsigned char index);

};


#endif //XPLAY_FFPLAYERBUILDER_H
