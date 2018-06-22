//
// Created by liuqikang on 2018/6/22.
//

#ifndef XPLAY_IOBSERVER_H
#define XPLAY_IOBSERVER_H


#include "XData.h"
#include "XThread.h"
#include <vector>
#include <mutex>

class IObserver : public XThread{
public:
    // 观察者接受数据函数
    virtual void Update(XData data){}
    // 添加观察者，线程安全
    virtual void AddObs(IObserver*obs);
    // 通知所有观察者，线程安全
    virtual void Notify(XData data);

private:
    std::vector<IObserver*> vobs;
    std::mutex mutex;
};


#endif //XPLAY_IOBSERVER_H
