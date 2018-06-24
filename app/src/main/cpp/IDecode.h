//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"

// 解码接口
class IDecode {
public:
    // 打开解码器
    virtual bool Open(XParameter p) = 0;

};


#endif //XPLAY_IDECODE_H
