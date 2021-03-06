//
// Created by liuqikang on 2018/7/3.
//

#include "IAudioPlay.h"
#include "XLog.h"

XData IAudioPlay::GetData() {
    XData d;

    while (!isExit)
    {
        frameMutex.lock();

        if (!frames.empty())
        {
            // 获取数据成功
            d = frames.front();
            frames.pop_front();
            frameMutex.unlock();

            pts = d.pts;// 记录音频的pts用于给视频做同步
            return d;
        }

        frameMutex.unlock();
        XSleep(1);
    }
    // 获取数据失败
    return d;
}

void IAudioPlay::Update(XData data) {
//    XLOGI("IAudioPlay::Update %d", data.size);
    if (data.size <= 0 || !data.data)
        return;

    while(!isExit)
    {
        // 压入缓冲队列, 队列满了阻塞
        frameMutex.lock();
        if (frames.size() > 100)
        {
            frameMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        frameMutex.unlock();
        break;
    }

}

