//
// Created by liuqikang on 2018/6/25.
//

#include "IDecode.h"
#include "XLog.h"

void IDecode::Update(XData data) {
    // 检测当前解码器类型和传入XData数据类型是否一致
    if (data.isAudio != isAudio)
    {
        return;
    }

    while(!isExit)
    {
        packMutex.lock();
        // 阻塞
        if (packs.size() < maxList)
        {
            // 生产者 将产品加入缓冲队列
            packs.push_back(data);
            //XLOGI("packs push_back success size %d", packs.size());
            packMutex.unlock();
            break;
        }
        packMutex.unlock();
        XSleep(1);// 释放CPU资源
    }

}

void IDecode::Main() {
    //XLOGI("IDecode::Main() in");
    while (!isExit)
    {
        packMutex.lock();

        // 视频解码器同步到音频pts
        if (!isAudio && synPts > 0)
        {
            if (synPts < vPts)
            {
                // 当前音频的pts小于当前解码出的视频的pts,要等待音频播放完视频才可以继续解码
                packMutex.unlock();
                XSleep(1);
                continue;
            }
        }

        if (packs.empty())
        {
            packMutex.unlock();
            XSleep(1);
            continue;
        }
        // 消费者从缓冲队列中提取数据 开始消费
        // 取出第一个pkt
        XData pack = packs.front();
        packs.pop_front();
        //XLOGI("packs.pop_front()");

        // 发送pack数据到解码线程
        if (this->SendPacket(pack))
        {
            //XLOGI("SendPacket()");

            while(!isExit)
            {
                // 获取解码数据,不需要清理，RecvFrame内部有清理
                XData frame = this->RecvFrame();
                //XLOGI("RecvFrame()");

                if (!frame.data) break;
                vPts = frame.pts;   // 记录当前freame的pts
                //XLOGI("RecvFrame size %d", frame.size);
                // 通知到所有观察者(GLVideoView 和 )
                this->Notify(frame);
            }
        }

        // 释放pkt
        pack.Drop();

        packMutex.unlock();
    }
}
