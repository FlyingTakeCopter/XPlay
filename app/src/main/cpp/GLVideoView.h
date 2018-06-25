//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_GLVIDEOVIEW_H
#define XPLAY_GLVIDEOVIEW_H

#include "IVideoView.h"

class XTexture;

class GLVideoView : public IVideoView {
public:
    virtual void SetRender(void *win);

    virtual void Render(XData data);


protected:
    void*view = 0;
    XTexture*texture = 0;
};


#endif //XPLAY_GLVIDEOVIEW_H
