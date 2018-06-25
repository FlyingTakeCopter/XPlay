//
// Created by liuqikang on 2018/6/25.
//

#include "FFDecode.h"
#include "XLog.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
}

bool FFDecode::Open(XParameter p) {
    if(!p.para)
        return false;
    AVCodecParameters*parameters = p.para;
    //查找解码器
    AVCodec*codec = avcodec_find_decoder(parameters->codec_id);
    if (!codec)
    {
        XLOGE("avcodec_find_decoder failed %d", parameters->codec_id);
        return false;
    }
    //创建解码器上下文，并拷贝参数
    codecxt = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecxt, parameters);
    //打开解码器
    int res = avcodec_open2(codecxt, codec, 0);
    if (res != 0)
    {
        char buf[1024] = {0};
        av_strerror(res, buf, sizeof(buf));
        XLOGE("avcodec_open2 failed reason %s", buf);
        return false;
    }
    XLOGI("avcodec_open2 success");
    return true;
}

bool FFDecode::SendPacket(XData pkt) {
    if (!pkt.data) return false;
    int res = avcodec_send_packet(codecxt, (const AVPacket *) pkt.data);
    if (res != 0)
    {
        return false;
    }
    return true;
}

XData FFDecode::RecvFrame() {
    if (!codecxt)
        return XData();
    int res = avcodec_receive_frame(codecxt, frame);
    if (res != 0)
    {
        return  XData();
    }
    XData d;
    d.data = (unsigned char *) frame;
    if (codecxt->codec_type == AVMEDIA_TYPE_VIDEO)
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;// (Y + U + V)一行总大小 * 高度
    return d;
}
