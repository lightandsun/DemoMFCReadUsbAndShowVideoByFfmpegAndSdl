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
  
# 附：Git Submodule 管理项目子模块
- 添加一个子模块
  git submodule add 子模块地址 自定义到当前工程的路径
  git commit
  git push

- 克隆/更新带子模块的工程
  方法一：
  git clone 工程地址，  进入工程后
  git submodule init  (init 操作只需要在刚clone下来时执行一下就行了，以后就不需要执行了)
  git submodule update

  方法二：
  git clone 工程地址 --recursive

- 注意：上述两种方法只能更新父工程的提交时的状态，如果把所有子模块都更新到最新的状态需要再执行下述命令
  git submodule update --remote --merge
- 或者在项目中，进入到子模块目录下，执行 git pull更新，查看git log查看相应提交。完成后返回到项目目录，可以看到子模块有待提交的更新，使用git add，提交即可。

- 问题来了，那么经过2.3后，还想保存此时的状态怎么办
  git status 后会发现对应改动的子模块，之后
  git add 最新的子模块即可
  git commit
  git pull

- 更新包含子模块的工程
  git pull
  git submodule update

- 批量操作
  git submodule foreach  + git命令即可
  例如 批量切换所有子模块到 master ， git submodule foreach git checkout master

- 其他：删除子模块
  rm -rf 子模块目录 删除子模块目录及源码
  vi .gitmodules 删除项目目录下.gitmodules文件中子模块相关条目
  vi .git/config 删除配置项中子模块相关条目
  rm .git/module/* 删除模块下的子模块目录，每个子模块对应一个目录，注意只删除对应的子模块目录即可
  git rm --cached 子模块名称 （如果再添加子模块报错的话可以执行该命令）
