//
// Created by zyc on 2022/4/8.
//

#include "Muxer.h"


Muxer::Muxer() {}
Muxer::~Muxer() {}

int Muxer::init(const char *url) {
    int ret = avformat_alloc_output_context2(&fmt_ctx_,NULL,NULL,url);
    if (ret!=0){
        char errbuf[1024]={0};
        av_strerror(ret,errbuf,sizeof(errbuf)-1);
        printf("avformat_alloc_output_context2 failed:%s\n", ret);
        return -1;
    }
}

void Muxer::DeInit() {
    if (fmt_ctx_){
        avformat_close_input(&fmt_ctx_);
    }
    url_ = "";
    aud_codec_ctx_ = NULL;
    aud_stream_ = NULL;
    audio_index_ = -1;

    vid_codec_ctx_ = NULL;
    vid_stream_ = NULL;
    video_index_= -1;

}
int Muxer::AddStream(AVCodecContext *codec_ctx) {
    if(!fmt_ctx_) {
        printf("fmt ctx is NULL\n");
        return -1;
    }
    if(!codec_ctx) {
        printf("codec ctx is NULL\n");
        return -1;
    }

    AVStream* st = avformat_new_stream(fmt_ctx_,NULL);
    if (!st){
        printf("avformat_new_stream failed\n");
        return -1;
    }

    //从编码器上下文复试流信息  啦啦啦啦啦
    avcodec_parameters_from_context(st->codecpar,codec_ctx);
    av_dump_format(fmt_ctx_,0,url_.c_str(),1);
}
int Muxer::SendHeader() {
    if (!fmt_ctx_){
        printf("fmt ctx is NULL\n");
        return -1;
    }
    int ret = avformat_write_header(fmt_ctx_,NULL);
    if(ret != 0) {
        char errbuf[1024] = {0};
        av_strerror(ret, errbuf, sizeof(errbuf) - 1);
        printf("avformat_write_header failed:%s\n", ret);
        return -1;
    }
    return 0;

}
int Muxer::SendPacket(AVPacket *packet) {
    int stream_index = packet->stream_index;

    if(!packet || packet->size <= 0 || !packet->data) {
        printf("packet is null\n");
        if(packet)
            av_packet_free(&packet);

        return -1;
    }

    AVRational src_time_base; //编码后的包
    AVRational dst_time_base; //mp4输出文件对应的time_base

    if (vid_stream_ && vid_codec_ctx_ && stream_index == video_index_){
        src_time_base = vid_codec_ctx_->time_base;
        dst_time_base = vid_stream_->time_base;
    } else if (aud_stream_ && aud_codec_ctx_ && stream_index == audio_index_){
        src_time_base = aud_codec_ctx_->time_base;
        dst_time_base = aud_stream_->time_base;
    }


    packet->pts = av_rescale_q(packet->pts,src_time_base,dst_time_base);
    packet->dts = av_rescale_q(packet->dts,src_time_base,dst_time_base);
    packet->duration = av_rescale_q(packet->duration,src_time_base,dst_time_base);

    int ret =0;
    ret = av_interleaved_write_frame(fmt_ctx_,packet);//不是立即写入文件 写入内部缓存 然后对pts 进行排序

    av_packet_free(&packet);
    if(ret == 0) {
        return 0;
    }else{
        char errbuf[1024] = {0};
        av_strerror(ret, errbuf, sizeof(errbuf) - 1);
        printf("avformat_write_header failed:%s\n", ret);
        return -1;
    }



}
int Muxer::SendTrailer() {
    if (!fmt_ctx_){
        printf("fmt ctx is NULL\n");
        return -1;
    }
    int ret = av_write_trailer(fmt_ctx_);
    if(ret != 0) {
        char errbuf[1024] = {0};
        av_strerror(ret, errbuf, sizeof(errbuf) - 1);
        printf("av_write_trailer failed:%s\n", ret);
        return -1;
    }
    return 0;
}
