//
// Created by liuqikang on 2018/6/22.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H

enum XDataType{
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1,
};

struct XData {
public:
    XDataType type = AVPACKET_TYPE;
    int pts = 0;    // 记录当前frame的pts用于音视频同步，同步方法视频同步到音频
    unsigned char* data = 0;// 指针地址
    unsigned char* datas[8] = {0};// 实际数据
    int width = 0;  // 当前帧宽高
    int height = 0; // 当前帧宽高
    int size = 0;
    int format = 0;//标识软硬解 解码出的数据类型
    bool Alloc(int size, const char* data = 0);//分配空间,用于音频拷贝
    void Drop();//释放空间
    bool isAudio = false;
};


#endif //XPLAY_XDATA_H
