//
// Created by liuqikang on 2018/7/9.
//

#include "IPlayerProxy.h"
#include "FFPlayerBuilder.h"

void IPlayerProxy::Init(void *vm) {
    mutex.lock();
    if (vm)
        FFPlayerBuilder::Get()->InitHard((JavaVM *) vm);
    if (!player)
        player = FFPlayerBuilder::Get()->BuildPlayer();
    mutex.unlock();
}

bool IPlayerProxy::Open(const char *path) {
    bool re = false;
    mutex.lock();
    if (player)
        re = player->Open(path);
    mutex.unlock();
    return re;
}

bool IPlayerProxy::Start() {
    bool re = false;
    mutex.lock();
    if (player)
        re = player->Start();
    mutex.unlock();
    return re;
}

void IPlayerProxy::InitView(void *win) {
    mutex.lock();
    if (player)
        player->InitView(win);
    mutex.unlock();
}
