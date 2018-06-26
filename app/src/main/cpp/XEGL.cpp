//
// Created by liuqikang on 2018/6/25.
//

#include <android/native_window.h>
#include <EGL/egl.h>
#include "XEGL.h"
#include "XLog.h"

class CXEGL : public XEGL
{
public:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    // 初始化EGL
    virtual bool Init(void *win)
    {
        XLOGI("EGL Init Start");

        ANativeWindow*awin = (ANativeWindow *) win;
        // 获取EGLDisplay显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY)
        {
            XLOGE("eglGetDisplay failed");
            return false;
        }
        XLOGI("eglGetDisplay success");

        // 初始化display
        if (EGL_TRUE != eglInitialize(display,0,0))
        {
            XLOGE("eglInitialize failed");
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
            return false;
        }
        XLOGI("eglChooseConfig success");
        // 关联窗口和EGL
        surface = eglCreateWindowSurface(display, conf,awin, 0);
        if (EGL_NO_SURFACE == surface)
        {
            XLOGE("eglCreateWindowSurface failed");
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
            return false;
        }
        XLOGI("eglCreateContext success");
        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context))
        {
            XLOGE("eglMakeCurrent failed");
            return false;
        }
        XLOGI("EGL Init() success");

        return true;
    }

    virtual void Draw() {
        if (surface == EGL_NO_SURFACE || display == EGL_NO_DISPLAY)
        {
            return;
        }
        // 窗口显示
        eglSwapBuffers(display, surface);
    }

};

XEGL *XEGL::GetInstance() {
    static CXEGL egl;
    return &egl;
}

