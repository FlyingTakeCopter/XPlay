//
// Created by liuqikang on 2018/7/4.
//

#include "FFPlayerBuilder.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "FFResample.h"
#include "SLAudioPlay.h"
#include "GLVideoView.h"

IDemux *FFPlayerBuilder::CreateDemux() {
    return new FFDemux();
}

IDecode *FFPlayerBuilder::CreateDecode() {
    return new FFDecode();
}

IResample *FFPlayerBuilder::CreateResample() {
    return new FFResample();
}

IAudioPlay *FFPlayerBuilder::CreateAudioPlay() {
    return new SLAudioPlay();
}

IVideoView *FFPlayerBuilder::CreateVideoView() {
    return new GLVideoView();
}

IPlayer *FFPlayerBuilder::CreateIPlayer(unsigned char index) {
    return IPlayer::Get(index);
}

void FFPlayerBuilder::InitHard(JavaVM *vm) {
    FFDecode::InitHard(vm);
}
