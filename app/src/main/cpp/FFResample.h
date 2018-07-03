//
// Created by liuqikang on 2018/7/2.
//

#ifndef XPLAY_FFRESAMPLE_H
#define XPLAY_FFRESAMPLE_H


#include "IResample.h"

struct SwrContext;
class FFResample : public IResample {
public:
    virtual bool Open(XParameter in, XParameter out);

private:
    SwrContext*actx;
};


#endif //XPLAY_FFRESAMPLE_H
