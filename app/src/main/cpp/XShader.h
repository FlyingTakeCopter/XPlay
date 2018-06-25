//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H


class XShader {
public:
    virtual bool Init();

protected:
    unsigned int vsh;
    unsigned int fsh;
};


#endif //XPLAY_XSHADER_H
