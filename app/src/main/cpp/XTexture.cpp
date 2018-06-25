//
// Created by liuqikang on 2018/6/25.
//

#include "XTexture.h"
#include "XEGL.h"
#include "XShader.h"
#include "XLog.h"

class CXTexture : public XTexture
{
public:
    virtual bool Init(void *win) {
        XLOGI("CXTexture Init() Start");
        if(!win)
        {
            XLOGI("win is null");
            return false;
        }

        if(!XEGL::GetInstance()->Init(win))
            return false;

        XShader shader;
        if(shader.Init())
            return false;

        XLOGI("CXTexture Init() Success");

        return true;
    }
};

XTexture *XTexture::Create() {
    return new CXTexture();
}
