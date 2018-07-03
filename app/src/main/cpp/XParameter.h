//
// Created by liuqikang on 2018/6/25.
//

#ifndef XPLAY_XPARAMETER_H
#define XPLAY_XPARAMETER_H

struct AVCodecParameters;

class XParameter {
public:
    AVCodecParameters*para;
    int channels = 2;
    int sample_rate = 44100;
};


#endif //XPLAY_XPARAMETER_H
