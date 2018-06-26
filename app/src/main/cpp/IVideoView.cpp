//
// Created by liuqikang on 2018/6/25.
//

#include "IVideoView.h"

void IVideoView::Update(XData data) {
    if(data.isAudio || data.size ==0)
    {
        return;
    }
    Render(data);
}
