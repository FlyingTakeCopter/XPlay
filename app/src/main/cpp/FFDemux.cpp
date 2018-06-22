//
// Created by liuqikang on 2018/6/22.
//

#include "FFDemux.h"
#include "XLog.h"

bool FFDemux::Open(const char *url) {
    XLOGI("open file %s", url);
    return true;
}

XData FFDemux::Read() {
    XData d;
    return d;
}
