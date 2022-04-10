cmake_minimum_required(VERSION 3.21)
project(Cpp_FFmpeg)

set(CMAKE_CXX_STANDARD 11)



set(INC_DIR /usr/local/ffmpeg/include)


#设置链接库路径x
set(LINK_DIR /usr/local/ffmpeg/lib )

#引入头文件
include_directories(${INC_DIR})

#引入库文件
link_directories(${LINK_DIR})


add_executable(Cpp_FFmpeg main.cpp Muxer.cpp Muxer.h AudioEncoder.cpp AudioEncoder.h VideoEncoder.cpp VideoEncoder.h AudioResampler.cpp AudioResampler.h)
target_link_libraries(Cpp_FFmpeg libavformat.dylib libavutil.dylib libswscale.dylib libavcodec.dylib libswresample.dylib)


