//
// Created by zyc on 2022/4/10.
//

#ifndef FFMPEG1_AUDIORESAMPLER_H
#define FFMPEG1_AUDIORESAMPLER_H
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
#include "libavformat/avformat.h"
}


AVFrame* AllocFltpPcmFrame(int channls,int nb_samples);
void FreePcmFrame(AVFrame* frame);
class AudioResampler {
public:
    AudioResampler();
    ~AudioResampler();
    int InitFromS16ToFLTP(int in_channels,int in_sample_rate,int out_channels,int out_sample_rate);
    int ResampleFromS16ToFLTP(uint8_t* in_data, AVFrame *out_frame);
    void DeInit();

private:
    int in_channels_;
    int in_sample_rate_;
    int out_channels_;
    int out_sample_rate_;
    SwrContext* ctx_ = NULL;

};


#endif //FFMPEG1_AUDIORESAMPLER_H
