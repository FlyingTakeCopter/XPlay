//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H

// 被GLVideoView直接调用
// 内部包含shader和egl的封装,头文件并不暴露
class XTexture {
public:
    virtual bool Init(void* win) = 0;
    static XTexture* Create();

    virtual void Draw(unsigned char* data[], int width, int height) = 0;
};


#endif //XPLAY_XTEXTURE_H
