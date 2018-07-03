//
// Created by liuqikang on 2018/7/2.
//

#include "IResample.h"

void IResample::Update(XData data) {
    XData d = this->Resample(data);
    if (d.size > 0)
    {
        this->Notify(d);
    }
}
