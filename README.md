# DemoMFCReadUsbAndShowVideoByFfmpegAndSdl
# 第三方依赖库下载
## ffmpeg
- 官网： http://ffmpeg.org/
- 菜单栏 -> Download ， 有Linux、windows、苹果三个图标，选择windows ->Windows builds from gyan.dev -> release -> https://www.gyan.dev/ffmpeg/builds/ffmpeg-release-full-shared.7z
- 本次使用的是 https://www.gyan.dev/ffmpeg/builds/packages/ffmpeg-4.3.1-2020-10-01-full_build-shared.7z 版本

## SDL
- 官网： http://www.libsdl.org/
- 菜单栏 ->  Download -> SDL Releases ， Development Libraries -> Windows -> [SDL2-devel-2.0.12-mingw.tar.gz](http://www.libsdl.org/release/SDL2-devel-2.0.12-mingw.tar.gz) 
- 本次使用的是 http://www.libsdl.org/release/SDL2-devel-2.0.12-mingw.tar.gz 版本

## 将上述依赖库放到第配置vs2013 或者直接从我的网盘里直接下载
- 链接: https://pan.baidu.com/s/1io_xoPMTf7dx9utg7iMt4g 提取码: t7xf
- 将ffmpeg-4.3.1-2020-09-21-full_build-shared 和 SDL2-2.0.12 放在MFC_ReadUsbAndShowVideoByFfmpegAndSdl.vcxproj同级目录下

## 扩展（直接使用本工程者可以忽略，仅仅是记录创建工程的过程）
### 配置管理器->活动结局方案配置
- Release
### 配置管理器->活动结局方案平台
- x64 -> 平台（新建）-> x64
- C/C++ -> 常规 -> 附加包含目录
  $(Projectdir)ffmpeg-4.3.1-2020-09-21-full_build-shared\include
  $(Projectdir)SDL2-2.0.12\include
- C/C++ -> 常规 -> 预处理
  _CRT_SECURE_NO_WARNINGS
  __STDC_CONSTANT_MACROS
### 连接器 -> 常规 -> 附加库目录
  $(Projectdir)ffmpeg-4.3.1-2020-09-21-full_build-shared\lib\
  $(Projectdir)SDL2-2.0.12\lib\x64\
### 连接器 -> 常规 -> 附加依赖项
  avcodec.lib
  avdevice.lib
  avfilter.lib
  avformat.lib
  avutil.lib
  postproc.lib
  swresample.lib
  swscale.lib
  SDL2.lib
