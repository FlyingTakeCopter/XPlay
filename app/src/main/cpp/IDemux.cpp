//
// Created by liuqikang on 2018/6/22.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    for (;;)
    {
        XData data = Read();
        XLOGI("packet size %d", data.size);
        if(data.size == 0)
        {
            XLOGI("Read finish");
            break;
        }
    }
}
