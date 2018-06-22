//
// Created by liuqikang on 2018/6/22.
//

#include "XData.h"

extern "C"
{
#include <libavcodec/avcodec.h>
}

void XData::Drop() {
    if(!data) return;
    av_packet_free((AVPacket **) &data);    // 注意类型匹配
}
