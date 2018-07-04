//
// Created by liuqikang on 2018/6/25.
//

#include "XTexture.h"
#include "XEGL.h"
#include "XShader.h"
#include "XLog.h"

// CXTexture 存在cpp内部，并不对外暴露
class CXTexture : public XTexture
{
public:
    XShader shader;
    XTextureType type;

    virtual bool Init(void *win, XTextureType type) {
        XLOGI("CXTexture Init() Start");
        if(!win)
        {
            XLOGI("win is null");
            return false;
        }
        this->type = type;

        if(!XEGL::GetInstance()->Init(win))
            return false;

        if(shader.Init((XShaderType) type))
            return false;

        XLOGI("CXTexture Init() Success");

        return true;
    }

    virtual void Draw(unsigned char* data[], int width, int height) {
        // 设置三个材质
        shader.GetTexture(0,width,height,data[0]);//Y

        if(type == XTEXTURE_YUV420P)
        {
            shader.GetTexture(1,width/2,height/2,data[1]);  // U
            shader.GetTexture(2,width/2,height/2,data[2]);  // V
        }
        else
        {
            shader.GetTexture(1,width/2,height/2,data[1], true);  // UV 包含一个透明通道
        }
        // opengl绘制
        shader.Draw();
        // egl绘制
        XEGL::GetInstance()->Draw();
    }
};

XTexture *XTexture::Create() {
    return new CXTexture();
}
