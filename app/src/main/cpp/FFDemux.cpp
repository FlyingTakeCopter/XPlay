//
// Created by liuqikang on 2018/6/22.
//

#include "FFDemux.h"
#include "XLog.h"

extern "C"
{
#include "libavformat/avformat.h"
}

static double r2d(AVRational rational)
{
    return rational.den == 0 || rational.num == 0 ? 0 : (double)rational.num / (double)rational.den;
}

bool FFDemux::Open(const char *url) {
    // 打开url
    int res = avformat_open_input(&ic, url, 0, 0);
    if (res != 0)
    {
        char buf[1024] = {0};
        av_strerror(res, buf, sizeof(buf));
        XLOGE("open file %s failed, reason: %s", url, buf);
        return false;
    }
    XLOGI("open file %s success", url);

    // 读取文件信息
    res = avformat_find_stream_info(ic, 0);
    if (res != 0)
    {
        char buf[1024] = {0};
        av_strerror(res, buf, sizeof(buf));
        XLOGE("avformat_find_stream_info failed, reason: %s", buf);
        return false;
    }
    this->totalms = ic->duration / (AV_TIME_BASE / 1000);
    //XLOGI("total ms = %d", this->totalms);

    GetVParameter();
    GetAParameter();



    return true;
}

XData FFDemux::Read() {
    if (!ic) return XData();
    // 读取一帧
    AVPacket*pkt = av_packet_alloc();
    int res = av_read_frame(ic, pkt);
    if (res != 0)
    {
        av_packet_free(&pkt);   // 失败释放pkt防止内存泄漏
        return XData();
    }
    //XLOGI("packet size %d pts %lld", pkt->size, pkt->pts);
    XData d;
    d.data = (unsigned char *) pkt;
    d.size = pkt->size;

    // 判断是音频流还是视频流，并给XData赋值
    if (pkt->stream_index == audioStream)
    {
        d.isAudio = true;
    }else if(pkt->stream_index == videoStream)
    {
        d.isAudio = false;
    }else
    {
        // 其他流
        av_packet_free(&pkt);   // 失败释放pkt防止内存泄漏
        return XData();
    }

    // 转换PTS,记录到XData
    pkt->pts = pkt->pts * (1000 * r2d(ic->streams[pkt->stream_index]->time_base));
    pkt->dts = pkt->dts * (1000 * r2d(ic->streams[pkt->stream_index]->time_base));
    d.pts = (int) pkt->pts;

    return d;
}

FFDemux::FFDemux() {
    static bool isFirst = true; // 线程不安全
    if (isFirst)
    {
        isFirst = false;
        //注册解封装器
        av_register_all();
        //注册网络
        avformat_network_init();
        //注册编码器
        avcodec_register_all();
    }
}

XParameter FFDemux::GetVParameter() {
    if (!ic) return XParameter();

    int res = av_find_best_stream(ic,AVMEDIA_TYPE_VIDEO, -1,-1,0,0);
    if (res <0)
    {
        XLOGE("GetVParameter failed");
        return XParameter();
    }

    videoStream = res;  // 记录视频流

    XParameter parameter;
    parameter.para = ic->streams[res]->codecpar;

    return parameter;
}

XParameter FFDemux::GetAParameter() {
    if (!ic) return XParameter();

    int res = av_find_best_stream(ic,AVMEDIA_TYPE_AUDIO, -1,-1,0,0);
    if (res <0)
    {
        XLOGE("GetAParameter failed");
        return XParameter();
    }

    audioStream = res; // 记录音频流

    XParameter parameter;
    parameter.para = ic->streams[res]->codecpar;
    parameter.channels = ic->streams[res]->codecpar->channels;
    parameter.sample_rate = ic->streams[res]->codecpar->sample_rate;
    return parameter;
}
