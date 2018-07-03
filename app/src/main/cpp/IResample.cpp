//
// Created by liuqikang on 2018/7/2.
//

#include "IResample.h"
#include "XLog.h"

void IResample::Update(XData data) {
//    XLOGI("IResample::Notify %d", data.size);
    XData d = this->Resample(data);
//    XLOGI("IResample::Notify %d", d.size);
    if (d.size > 0)
    {
        this->Notify(d);
    }
}
