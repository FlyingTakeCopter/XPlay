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
    if (type == AVPACKET_TYPE)
    {
        av_packet_free((AVPacket **) &data);    // 注意类型匹配
    } else
    {
        delete data;
    }
    data = 0;
    size = 0;
}

bool XData::Alloc(int size, const char *d) {
    Drop();
    type = UCHAR_TYPE;
    if(size <= 0) return false;

    this->data = new unsigned char[size];
    if (!this->data) return false;

    this->size = size;
    if (d)
    {
        memcpy(this->data, d, size);
    }

    return true;
}
