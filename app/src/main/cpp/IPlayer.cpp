//
// Created by liuqikang on 2018/7/4.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "XLog.h"

IPlayer *IPlayer::Get(unsigned char index) {
    static IPlayer p[255];
    return &p[index];
}

void IPlayer::Main() {
    while (!isExit)
    {
        mutex.lock();
        if (!audioPlay || !vDecode)
        {
            mutex.unlock();
            XSleep(2);
            continue;
        }
        //同步
        //获取音频的PTS,告诉视频加码器来做同步
        int apts = audioPlay->pts;
//        XLOGI("IPlayer::Main pts = %d", apts);
        vDecode->synPts = apts;

        mutex.unlock();
        XSleep(2);
    }
}

bool IPlayer::Open(const char *path) {
    mutex.lock();

    XLOGI("IPlayer::Open path %s", path);

    if (!demux || !demux->Open(path))
    {
        mutex.unlock();
        XLOGE("IPlayer::Open demux->Open failed!");
        return false;
    }

    // 如果解封装之后就是原始数据，并不需要解码
    if (!vDecode || !vDecode->Open(demux->GetVParameter(), false))
    {
        XLOGE("IPlayer::Open vDecode failed!");
//        return false;
    }

    if (!aDecode || !aDecode->Open(demux->GetAParameter()))
    {
        XLOGE("IPlayer::Open aDecode failed!");
        //        return false;
    }

    // 重采样有可能不需要，解码或解封之后的数据直接能用
    if (!outP.para)
        outP = demux->GetAParameter();
    if (!resample || !resample->Open(demux->GetAParameter(), outP))
    {
        XLOGE("IPlayer::Open resample failed!");
//        return false;
    }


    XLOGI("IPlayer::Open success");
    mutex.unlock();
    return true;
}

bool IPlayer::Start() {
    mutex.lock();

    if (!demux || !demux->Start())
    {
        mutex.unlock();

        XLOGE("IPlayer::Start demux failed!");
        return false;
    }

    // 让音频优先于视频启动，多缓冲
    if (aDecode)
        aDecode->Start();
    if (audioPlay)
        audioPlay->StartPlay(outP);

    if (vDecode)
        vDecode->Start();

    XThread::Start();//启动IPlayer::Main()
    mutex.unlock();
    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView)
        videoView->SetRender(win);
}


