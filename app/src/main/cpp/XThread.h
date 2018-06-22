//
// Created by liuqikang on 2018/6/22.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H

// sleep毫秒
void XSleep(int ms);

class XThread {
public:
    // 启动线程
    virtual void Start();
    // 安全停止线程，通过控制isExit参数，不一定退出成功
    virtual void Stop();
    // 线程主函数，用于子类重载
    virtual void Main(){}

private:
    // 包裹Main函数，方便控制
    void ThreadMain();

protected:
    bool isExit = false;            // 线程运行/停止变量
    bool isThreadRunning = false;   // 标识Main()函数是否运行结束
};


#endif //XPLAY_XTHREAD_H
