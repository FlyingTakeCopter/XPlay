//
// Created by liuqikang on 2018/7/9.
//

#ifndef XPLAY_IPLAYERPROXY_H
#define XPLAY_IPLAYERPROXY_H


#include <mutex>
#include "IPlayer.h"

class IPlayerProxy : public IPlayer{
public:
    static IPlayerProxy*Get()
    {
        static IPlayerProxy proxy;
        return &proxy;
    }
    void Init(void *vm);

    virtual bool Open(const char* path);
    virtual bool Start();
    virtual void InitView(void* win);

protected:
    IPlayer* player = 0;
    std::mutex mutex;
};


#endif //XPLAY_IPLAYERPROXY_H
