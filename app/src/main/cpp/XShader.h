//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H

enum XShaderType
{
    XSHADER_YUV420P = 0,    //软解码和虚拟机
    XSHADER_NV12 = 25,      //手机
    XSHADER_NV21 = 26
};

class XShader {
public:
    virtual bool Init(XShaderType type=XSHADER_YUV420P);

    // 获取纹理并绑定到内存 isa：是否带透明通道NV12要用
    virtual void GetTexture(unsigned int index, int width, int height, unsigned char* buf,bool isa=false);
    virtual void Draw();

protected:
    unsigned int vsh;
    unsigned int fsh;
    unsigned int program;
    unsigned int txts[100] = {0};//记录材质层,便于清理
};


#endif //XPLAY_XSHADER_H
