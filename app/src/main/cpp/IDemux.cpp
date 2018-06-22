//
// Created by liuqikang on 2018/6/22.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    while (!isExit)
    {
        XData data = Read();
        if (data.size > 0)
        {
            Notify(data);   // 通知所有观察者
        }
        //XLOGI("packet size %d", data.size);
//        if(data.size == 0) break;

    }
}
