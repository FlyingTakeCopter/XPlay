//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include "IDecode.h"

class FFDecode : public IDecode {
public:
    bool Open(XParameter p) override;

};


#endif //XPLAY_FFDECODE_H
