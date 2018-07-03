//
// Created by liuqikang on 2018/7/2.
//

#include <libavcodec/avcodec.h>
#include "FFResample.h"
#include "XLog.h"

extern "C"
{
#include "libswresample/swresample.h"
}

bool FFResample::Open(XParameter in, XParameter out) {

    // 初始化重采样参数
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(2),
                              AV_SAMPLE_FMT_S16,
                              in.para->sample_rate,
                              av_get_default_channel_layout(out.para->channels),
                              (AVSampleFormat) out.para->format,
                              out.para->sample_rate,
                              0, NULL);

    int res = swr_init(actx);
    if (res != 0)
    {
        XLOGE("swr_init failed");
        return false;
    }
    XLOGI("swr_init success");





    return true;
}
