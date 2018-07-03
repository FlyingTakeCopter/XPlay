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

    virtual bool Open(XParameter in, XParameter out) = 0;
};


#endif //XPLAY_IRESAMPLE_H
