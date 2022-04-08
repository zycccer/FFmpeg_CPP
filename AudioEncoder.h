//
// Created by zyc on 2022/4/8.
//

#ifndef FFMPEG1_AUDIOENCODER_H
#define FFMPEG1_AUDIOENCODER_H

#include "iostream"
extern"C"{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
};
class AudioEncoder {
public:
    AudioEncoder();
    ~AudioEncoder();
    int InitAAC(int channels,int sample_rate,int bit_rate);
    void DeInit();
    AVPacket* Encode(AVFrame *frame,int stream_index,int64_t pts,int64_t time_base);
    int GetFrameSize();//获取一帧数据 每个通道需要多少个采样点
    int GetSampleFormat();//获取编码器需要的采样格式

private:
    int channels_ = 2;
    int sample_rate_ = 44100;
    int bit_rate_ = 128*1024;
    int64_t pts_ = 0;
    AVCodecContext* codec_ctx_ = NULL;




};


#endif //FFMPEG1_AUDIOENCODER_H
