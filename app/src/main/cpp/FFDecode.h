//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include "IDecode.h"

struct AVCodecContext;

class FFDecode : public IDecode {
public:
    bool Open(XParameter p) override;

protected:
    AVCodecContext*codecxt;
};


#endif //XPLAY_FFDECODE_H
