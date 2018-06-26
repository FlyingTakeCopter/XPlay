//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H


class XShader {
public:
    virtual bool Init();

    // 获取纹理并绑定到内存
    virtual void GetTexture(unsigned int index, int width, int height, unsigned char* buf);
    virtual void Draw();

protected:
    unsigned int vsh;
    unsigned int fsh;
    unsigned int program;
    unsigned int txts[100] = {0};//记录材质层,便于清理
};


#endif //XPLAY_XSHADER_H
