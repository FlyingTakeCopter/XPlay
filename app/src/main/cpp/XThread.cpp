//
// Created by liuqikang on 2018/6/22.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>
using namespace std;

void XThread::Start() {
    thread th(&XThread::ThreadMain, this);
    th.detach();// 移除当前线程对新建线程的控制，否自会资源访问冲突
}

void XThread::ThreadMain() {
    XLOGI("进入主线程");
    Main();
    XLOGI("退出主线程");
}

void XThread::Stop() {

}

