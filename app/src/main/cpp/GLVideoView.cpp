//
// Created by liuqikang on 2018/6/25.
//

#include "GLVideoView.h"
#include "XTexture.h"
#include "XLog.h"

void GLVideoView::SetRender(void *win) {
    view = win;
}

void GLVideoView::Render(XData data) {
    XLOGI("GLVideoView::Render Start");
    if(!view) return;
    if(!texture)
    {
        texture = XTexture::Create();
        texture->Init(view);
    }
    XLOGI("GLVideoView::Render Success");
}
