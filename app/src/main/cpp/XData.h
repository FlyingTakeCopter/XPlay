//
// Created by liuqikang on 2018/6/22.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


struct XData {
public:
    unsigned char* data = 0;// 指针地址
    unsigned char* datas[8] = {0};// 实际数据
    int width = 0;  // 当前帧宽高
    int height = 0; // 当前帧宽高
    int size = 0;
    void Drop();
    bool isAudio = false;
};


#endif //XPLAY_XDATA_H
