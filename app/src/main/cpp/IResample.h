//
// Created by liuqikang on 2018/7/2.
//

#ifndef XPLAY_IRESAMPLE_H
#define XPLAY_IRESAMPLE_H


#include "IObserver.h"
#include "XParameter.h"

class IResample : public IObserver {
public:
    virtual void Update(XData data);

    virtual bool Open(XParameter in, XParameter out=XParameter()) = 0;

    virtual XData Resample(XData inData) = 0;

    // 外部指定
    int outChannels = 2;// 输出的声道数
    int outFormat = 1;  // 输出的sample类型(AVSampleFormat),1:AV_SAMPLE_FMT_S16
};


#endif //XPLAY_IRESAMPLE_H
