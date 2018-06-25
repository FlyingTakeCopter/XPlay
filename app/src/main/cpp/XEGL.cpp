//
// Created by liuqikang on 2018/6/25.
//

#include "XEGL.h"

class CXEGL : public XEGL
{
public:
    virtual bool Init(void *win)
    {
        return true;
    }

};

XEGL *XEGL::GetInstance() {
    static XEGL egl;
    return &egl;
}
