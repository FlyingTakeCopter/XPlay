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

    virtual void Close();

    virtual XData Resample(XData inData);

private:
    SwrContext*actx;
    std::mutex mutex;
};


#endif //XPLAY_FFRESAMPLE_H
