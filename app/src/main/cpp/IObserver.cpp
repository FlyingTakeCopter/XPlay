//
// Created by liuqikang on 2018/6/22.
//

#include "IObserver.h"

void IObserver::AddObs(IObserver *obs) {
    mutex.lock();
    vobs.push_back(obs);
    mutex.unlock();
}

void IObserver::Notify(XData data) {
    if (data.size == 0)
        return;

    mutex.lock();
    int num = vobs.size();
    for (int i = 0; i < num; ++i) {
        vobs[i]->Update(data);
    }

    mutex.unlock();
}
