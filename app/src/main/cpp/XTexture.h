//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H

enum XTextureType
{
    XTEXTURE_YUV420P = 0,  // Y 4  u 1 v 1
    XTEXTURE_NV12 = 25,    // Y4   uv1
    XTEXTURE_NV21 = 26     // Y4   vu1

};

// 被GLVideoView直接调用
// 内部包含shader和egl的封装,头文件并不暴露
class XTexture {
public:
    virtual bool Init(void* win, XTextureType type = XTEXTURE_YUV420P) = 0;
    static XTexture* Create();

    virtual void Draw(unsigned char* data[], int width, int height) = 0;
};


#endif //XPLAY_XTEXTURE_H
