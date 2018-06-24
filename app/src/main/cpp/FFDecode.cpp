//
// Created by liuqikang on 2018/6/25.
//

#include "FFDecode.h"

bool FFDecode::Open(XParameter p) {
    if(!p.para)
        return false;
    AVCodecParameters*parameters = p.para;
    return true;
}
