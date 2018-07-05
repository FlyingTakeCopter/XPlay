//
// Created by liuqikang on 2018/7/4.
//

#include "IPlayerBuilder.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IAudioPlay.h"
#include "IVideoView.h"

IPlayer *IPlayerBuilder::BuildPlayer(unsigned char index) {
    // 创建解封装器
    IDemux* demux = CreateDemux();
    // 创建视频解码器
    IDecode*vDecode = CreateDecode();
    // 创建音频解码器
    IDecode*aDecode = CreateDecode();
    // 添加视频/音频解码器为demux的观察者
    demux->AddObs(vDecode);
    demux->AddObs(aDecode);
    //GLVideoView作为视频解码器的观察者
    IVideoView* view = CreateVideoView();
    vDecode->AddObs(view);
    //创建重采样类并添加为，音频解码器的观察者
    IResample*resample = CreateResample();
    aDecode->AddObs(resample);
    //创建音频播放，作为重采样观察者
    IAudioPlay*audioPlay = CreateAudioPlay();
    resample->AddObs(audioPlay);
    // 创建播放器
    IPlayer*player = CreateIPlayer(index);

    player->demux = demux;
    player->vDecode = vDecode;
    player->aDecode = aDecode;
    player->resample = resample;
    player->audioPlay = audioPlay;
    player->videoView = view;
    
    return player;
}
