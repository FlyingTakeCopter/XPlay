//
// Created by liuqikang on 2018/7/3.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver {
public:
    virtual void Update(XData data);// 接受重采样完成的数据
    virtual bool StartPlay(XParameter out) = 0;

};


#endif //XPLAY_IAUDIOPLAY_H
