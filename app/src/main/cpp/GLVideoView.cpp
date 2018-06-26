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
//    XLOGI("GLVideoView::Render Start");
    if(!view)
    {
        XLOGE("view is null");
        return;
    }
    if(!texture)
    {
        texture = XTexture::Create();
        if(!texture->Init(view))
        {
            return;
        }
    }
    texture->Draw(data.datas, data.width, data.height);
//    XLOGI("GLVideoView::Render Success");
}
