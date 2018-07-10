//
// Created by liuqikang on 2018/6/25.
//

#include <android/native_window.h>
#include <EGL/egl.h>
#include <mutex>
#include "XEGL.h"
#include "XLog.h"

class CXEGL : public XEGL
{
public:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    std::mutex mutex;

    virtual void Close() {
        mutex.lock();
        // 去除绑定关系
        if (display == EGL_NO_DISPLAY)
        {
            mutex.unlock();
            return;
        }
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        // 清理surface
        if (surface != EGL_NO_SURFACE)
            eglDestroySurface(display, surface);
        // 清理context
        if (context != EGL_NO_CONTEXT)
            eglDestroyContext(display, context);
        // 终止display
        eglTerminate(display);

        display = EGL_NO_DISPLAY;
        surface = EGL_NO_SURFACE;
        context = EGL_NO_CONTEXT;
        mutex.unlock();
    }

    // 初始化EGL
    virtual bool Init(void *win)
    {
        Close();
        XLOGI("EGL Init Start");

        ANativeWindow*awin = (ANativeWindow *) win;
        mutex.lock();
        // 获取EGLDisplay显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY)
        {
            XLOGE("eglGetDisplay failed");
            mutex.unlock();
            return false;
        }
        XLOGI("eglGetDisplay success");

        // 初始化display
        if (EGL_TRUE != eglInitialize(display,0,0))
        {
            XLOGE("eglInitialize failed");
            mutex.unlock();
            return false;
        }
        XLOGI("eglInitialize success");
        // 获取配置并配置surface
        EGLint config[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig conf = 0;
        EGLint num = 0;
        if (EGL_TRUE != eglChooseConfig(display, config, &conf, 1, &num))
        {
            XLOGE("eglChooseConfig failed");
            mutex.unlock();
            return false;
        }
        XLOGI("eglChooseConfig success");
        // 关联窗口和EGL
        surface = eglCreateWindowSurface(display, conf,awin, 0);
        if (EGL_NO_SURFACE == surface)
        {
            XLOGE("eglCreateWindowSurface failed");
            mutex.unlock();
            return false;
        }
        XLOGI("eglCreateWindowSurface success");

        // 创建并打开上下文
        const EGLint attr[] = {
                EGL_CONTEXT_CLIENT_VERSION,
                2,
                EGL_NONE
        };
        context = eglCreateContext(display, conf, EGL_NO_CONTEXT, attr);
        if (EGL_NO_CONTEXT == context)
        {
            XLOGE("eglCreateContext failed");
            mutex.unlock();
            return false;
        }
        XLOGI("eglCreateContext success");
        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context))
        {
            XLOGE("eglMakeCurrent failed");
            mutex.unlock();
            return false;
        }
        XLOGI("EGL Init() success");

        mutex.unlock();

        return true;
    }

    virtual void Draw() {
        mutex.lock();
        if (surface == EGL_NO_SURFACE || display == EGL_NO_DISPLAY)
        {
            mutex.unlock();
            return;
        }
        // 窗口显示
        eglSwapBuffers(display, surface);
        mutex.unlock();
    }

};

XEGL *XEGL::GetInstance() {
    static CXEGL egl;
    return &egl;
}

