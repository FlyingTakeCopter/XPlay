//
// Created by liuqikang on 2018/7/2.
//

#include "FFResample.h"
#include "XLog.h"

extern "C"
{
#include "libswresample/swresample.h"
#include <libavcodec/avcodec.h>
}

bool FFResample::Open(XParameter in, XParameter out) {

    XLOGI("FFResample Open start");
    // 初始化重采样参数
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(out.channels),
                              AV_SAMPLE_FMT_S16,
                              out.para->sample_rate,
                              av_get_default_channel_layout(in.para->channels),
                              (AVSampleFormat) in.para->format,
                              in.para->sample_rate,
                              0, NULL);

    int res = swr_init(actx);
    if (res != 0)
    {
        XLOGE("swr_init failed");
        return false;
    }
    outChannels = in.para->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    XLOGI("swr_init success");
    return true;
}

XData FFResample::Resample(XData inData) {
    if (!inData.data || inData.size <= 0) return XData();
    if (!actx) return XData();
//    XLOGI("Resample start inData.size = %d", inData.size);
//    return XData();
    AVFrame*frame = (AVFrame*)inData.data;
    XData out;
    //音频总大小: 单声道字节数 * 单声道总帧数 * 声道数
    //int size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2;
    int size = outChannels * frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat) outFormat);
    if (size <= 0)
    {
        return XData();
    }
    out.Alloc(size);

    uint8_t *outArr[2] = {0};
    outArr[0] = out.data;
    int len = swr_convert(actx, outArr, frame->nb_samples,
                          (const uint8_t **) frame->data, frame->nb_samples);

    if (len <= 0)
    {
        out.Drop();
        return XData();
    }

//    XLOGI("swr_convert success len = %d", len);
    return out;
}
