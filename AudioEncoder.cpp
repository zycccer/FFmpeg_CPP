//
// Created by zyc on 2022/4/8.
//

#include "AudioEncoder.h"
AudioEncoder::AudioEncoder() {

}
AudioEncoder::~AudioEncoder() {
    if (codec_ctx_){
        DeInit();
    }
}

int AudioEncoder::InitAAC(int channels, int sample_rate, int bit_rate) {
   channels_ = channels;
   sample_rate_ = sample_rate;
   bit_rate_ = bit_rate;

   AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_AAC);
    if (!codec){
        printf("avcodec_find_encoder AV_CODEC_ID_AAC failed\n");
        return -1;
    }
    codec_ctx_ = avcodec_alloc_context3(codec);
    if(!codec_ctx_) {
        printf("avcodec_alloc_context3 AV_CODEC_ID_AAC failed\n");
        return -1;
    }

}
void AudioEncoder::DeInit() {}

AVPacket* AudioEncoder::Encode(AVFrame *frame, int stream_index, int64_t pts, int64_t time_base) {

}

int AudioEncoder::GetFrameSize() {}

int AudioEncoder::GetSampleFormat() {}


