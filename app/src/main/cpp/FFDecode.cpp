//
// Created by liuqikang on 2018/6/25.
//

#include "FFDecode.h"
#include "XLog.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
#include <libavcodec/jni.h>
}

void FFDecode::InitHard(JavaVM *vm) {
    av_jni_set_java_vm(vm,0);
}

void FFDecode::Close() {
    mutex.lock();
    vPts = 0;
    synPts = 0;
    if (codecxt)
    {
        avcodec_close(codecxt);
        avcodec_free_context(&codecxt);
    }
    if (frame)
        av_frame_free(&frame);//@param frame frame to be freed. The pointer will be set to NULL.

    mutex.unlock();
}

bool FFDecode::Open(XParameter p, bool isHard) {
    Close();

    if(!p.para)
        return false;
    AVCodecParameters*parameters = p.para;
    //查找解码器
    AVCodec*codec = avcodec_find_decoder(parameters->codec_id);
    //硬解码
    if (isHard)
    {
        codec = avcodec_find_decoder_by_name("h264_mediacodec");
    }

    if (!codec)
    {
        XLOGE("avcodec_find_decoder failed %d", parameters->codec_id);
        return false;
    }
    mutex.lock();
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
        mutex.unlock();
        return false;
    }
    // 设置流类型
    isAudio = (codec->type == AVMEDIA_TYPE_AUDIO);
    // 初始化frame内存，RecvFrame中会用到
    frame = av_frame_alloc();
    XLOGI("FFDecode::Open success");
    mutex.unlock();
    return true;
}

bool FFDecode::SendPacket(XData pkt) {
    if (!pkt.data) return false;
    mutex.lock();
    int res = avcodec_send_packet(codecxt, (const AVPacket *) pkt.data);
    mutex.unlock();
    if (res != 0)
    {
        return false;
    }
    return true;
}

XData FFDecode::RecvFrame() {
    mutex.lock();
    if (!codecxt)
    {
        mutex.unlock();
        return XData();
    }
    // 内部会释放上次的资源
    int res = avcodec_receive_frame(codecxt, frame);
    if (res != 0)
    {
        mutex.unlock();
        return  XData();
    }
    XData d;
    d.data = (unsigned char *) frame;
    if (codecxt->codec_type == AVMEDIA_TYPE_VIDEO)
    {
        // 视频总大小： (Y + U + V)单行总大小 * 高度
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
        d.width = frame->width;d.height = frame->height;

    }
    else    //音频总大小: 单声道字节数 * 单声道总帧数 * 声道数
        d.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2;
    //标识YUV420P和NV21,解码之后能准确知道格式
    d.format = frame->format;
    // 内存拷贝
    memcpy(d.datas, frame->data, sizeof(d.datas));
    // pts赋值
    d.pts = (int) frame->pts;
    mutex.unlock();
    return d;
}



