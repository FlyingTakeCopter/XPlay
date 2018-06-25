//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_XEGL_H
#define XPLAY_XEGL_H


class XEGL {
public:
    virtual bool Init(void*win) = 0;
    static XEGL* GetInstance();

protected:
    XEGL(){}

};


#endif //XPLAY_XEGL_H
