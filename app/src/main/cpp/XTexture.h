//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H


class XTexture {
public:
    virtual bool Init(void* win) = 0;
    static XTexture* Create();
};


#endif //XPLAY_XTEXTURE_H
