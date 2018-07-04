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
        if(!texture->Init(view, (XTextureType) data.format))    //传入解码出来的格式(软硬解码器出来的格式不同)
        {
            return;
        }
    }
    texture->Draw(data.datas, data.width, data.height);
//    XLOGI("GLVideoView::Render Success");
}
