//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_IVIDEOVIEW_H
#define XPLAY_IVIDEOVIEW_H


#include "XData.h"
#include "IObserver.h"

class IVideoView : public IObserver{
public:
    virtual void SetRender(void*win) = 0;
    virtual void Render(XData data) = 0;
    // 作为视频解码器的观察者，接受解码后的数据并显示
    virtual void Update(XData data);


};


#endif //XPLAY_IVIDEOVIEW_H
