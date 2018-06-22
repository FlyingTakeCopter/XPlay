//
// Created by liuqikang on 2018/6/22.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>
using namespace std;

void XSleep(int ms){
    chrono::milliseconds du(ms);
    this_thread::sleep_for(du); // 对当前线程sleep
}


void XThread::Start() {
    isExit = false;
    thread th(&XThread::ThreadMain, this);
    th.detach();// 移除当前线程对新建线程的控制，否自会资源访问冲突
}

void XThread::ThreadMain() {
    isThreadRunning = true;
    XLOGI("进入主线程");
    Main();
    XLOGI("退出主线程");
    isThreadRunning = false;
}

void XThread::Stop() {
    XLOGI("Stop() 停止线程开始");
    isExit = true;

    // 200毫秒 等待线程退出
    for (int i = 0; i < 200; ++i) {
        if (!isThreadRunning)   // 根据线程运行标识判断线程是否停止成功
        {
            XLOGI("Stop() 停止线程成功");
            return;
        }
        XSleep(1);
    }
    XLOGI("Stop() 停止线程超时!");
}

