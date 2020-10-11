/*
* Copyright (c) 2000 FD Inc. All Rights Reserved.
*
* filename:	read_usb_video.cpp
* function: 实现从usb读取视频流
* create:	2020-10-05
* author:	fd
*/
#include "stdafx.h"

#include "read_usb_video.h"
#include <iostream>

#define _HZG_SDL_ 1

#ifdef __cplusplus
extern "C" {
#endif

#if _MSC_VER
#define snprintf _snprintf
#endif

#include "libavdevice/avdevice.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavfilter/avfilter.h"
#include "libavutil/imgutils.h"
#include "libavutil/fifo.h"
#include "libavutil/samplefmt.h"
#include "libavutil/time.h"
#include "libavutil/timestamp.h"
#include "libavutil/avassert.h"
#include "libavutil/channel_layout.h"
#include "libavutil/mathematics.h"
#include "libavutil/opt.h"
#include "libswresample/swresample.h"
#include "libavdevice/avdevice.h"

#ifdef __cplusplus
}
#endif


#include <chrono>
#include <string.h>
#include <math.h>
#include<thread>
#include <atomic>
#include<iostream>
using namespace std;
//using namespace std;


UsbVideoService::UsbVideoService()
{
}
UsbVideoService::~UsbVideoService()
{
}

int UsbVideoService::GetDevList()
{
	AVFormatContext* format_ctx = nullptr;
	format_ctx = avformat_alloc_context();
	if (nullptr == format_ctx) {
		return -1;
	}

	AVDictionary* options = nullptr;
	av_dict_set(&options, "list_devices", "true", 0);

	AVInputFormat *in_format = nullptr;
	in_format = av_find_input_format("dshow");
	if (nullptr == in_format) {
		avformat_free_context(av_format_ctx);
		return -2;
	}

	printf("========Device Info=============\n");
	if (avformat_open_input(&format_ctx, "video=dummy", in_format, &options) != 0) {
		return -3;
	}
	printf("================================\n");

	avformat_free_context(format_ctx);
}


const std::string GetCurrentSystemTime()
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&t);
	char date[60] = { 0 };
	sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return move(std::string(date));
}

void WriteLog(std::string log) {

	FILE *fp = nullptr;
	fp = fopen("usb.log", "ab+");
	if (nullptr == fp) {
		cout << "文件打开失败！" << endl;
	}
	else {
		std::string t = GetCurrentSystemTime() + " ";
		fwrite((const void*)t.c_str(), t.length(), 1, fp);
		fwrite((const void*)log.c_str(), log.length(), 1, fp);
		fwrite("\n", strlen("\n"), 1, fp);
		//cout << "写入失败！" << endl;
	}
	fclose(fp);
}

int UsbVideoService::Init(bool is_codec, void* hwnd)
{
	WriteLog("Init begin.");

	static int m = 0;
	if (m==0)
	{
		avdevice_register_all();
		m = 1;
	}

	is_init = true;
	is_support_codec = is_codec;
	if (nullptr != hwnd) {
		is_support_sdl = true;
		sdl_hwnd = hwnd;
	}

	WriteLog("Init end.");
	return 0;
}

int UsbVideoService::AnalysisUrl(std::string way, std::string camera_name)
{
	WriteLog("AnalysisUrl begin.");
	if (!is_init) {
		WriteLog("!is_init");
		return -10000;
	}

	if (way.compare(VFWCAP) != 0 && way.compare(DSHOW) != 0 && way.compare(V4L2) != 0) {
		WriteLog("compare failed.");
		return -1;
	}

	std::string tmp_url("");

	input_format_name = way;

	if (0 == way.compare(VFWCAP)) { //_MSC_VER windows
		tmp_url = "";
	}
	else if (0 == way.compare(DSHOW)) { //_MSC_VER windows
		tmp_url = camera_name;
	}
	else if (0 == way.compare(V4L2)) { //linux
		tmp_url = camera_name; // example: /dev/video0
	}

	url = std::string("video=") + tmp_url;

	WriteLog("url is: " + url);
	WriteLog("AnalysisUrl end.");
	return 0;
}

int UsbVideoService::OpenCamera(std::string way, std::string camera_name, std::string frame_rate)
{
	WriteLog("OpenCamera begin.");
	if (!is_init) {
		WriteLog("!is_init");
		return -10000;
	}

	if (way.compare(VFWCAP) != 0 && way.compare(DSHOW) != 0 && way.compare(V4L2) != 0) {
		WriteLog("compare failed. way is " + way);
		return -1;
	}

	if (AnalysisUrl(way, camera_name) < 0) {
		WriteLog("AnalysisUrl failed.");
		return -1;
	}

// 	av_format_ctx = avformat_alloc_context();
// 	if (nullptr == av_format_ctx) {
// 		return -1;
// 	}

	AVInputFormat* av_input_fmt = nullptr;
	av_input_fmt = av_find_input_format(input_format_name.c_str());
	if (nullptr == av_input_fmt) {
		return -1;
	}

	if (av_dict_set(&options, "video_size", frame_rate.c_str(), 0) < 0) { //"1280x720"
		WriteLog("av_dict_set 1280x720 failed.");
		return -1;
	}
	WriteLog("av_dict_set 1280x720 succ.");

	if (av_dict_set(&options, "input_format", "mjpeg", 0) < 0) { //
		WriteLog("av_dict_set mjpeg failed.");
		return -1;
	}
	WriteLog("av_dict_set mjpeg succ.");

	if (av_dict_set(&options, "frame_rate", "30", 0) < 0) {
		WriteLog("av_dict_set framerate failed.");
		return -1;
	}
	WriteLog("av_dict_set framerate succ.");
	
	int ret = avformat_open_input(&av_format_ctx, url.c_str(), av_input_fmt, &options);// nullptr
	if (ret != 0) {
		WriteLog("Couldn't open input stream.");
		fprintf(stderr, "Couldn't open input stream: %d\n", ret);
		return -1;
	}
	WriteLog("avformat_open_input succ.");

	ret = avformat_find_stream_info(av_format_ctx, nullptr);
	if (ret < 0) {
		WriteLog("fail to get stream information." + std::to_string(ret));
		return -1;
	}

	fprintf(stdout, "Number of elements in AVFormatContext.streams: %d\n", av_format_ctx->nb_streams);
	for (int i = 0; i < av_format_ctx->nb_streams; ++i) {
		const AVStream* stream = av_format_ctx->streams[i];
		fprintf(stdout, "type of the encoded data: %d\n", stream->codecpar->codec_id);
		if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			video_stream_index = i;
			dst_width = stream->codecpar->width;
			dst_height = stream->codecpar->height;
			WriteLog(std::string("dimensions of the video frame in pixels: width:") + std::to_string(stream->codecpar->width) +
				std::string("height:") + std::to_string(stream->codecpar->height) +
				std::string("pixel format:") + std::to_string(stream->codecpar->format));
		}
		else if (stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
			audio_stream_index = i;
			fprintf(stdout, "audio sample format: %d\n", stream->codecpar->format);
		}
	}

	if (video_stream_index == -1 && audio_stream_index == -1) {
		WriteLog("Error: no video stream.Warning: no audio stream.");
		return -1;
	}

	if (is_support_codec && 0 != CodecInit()) {
		WriteLog("CodecInit failed.");
		return -1;
	}

	if (is_support_sdl && 0 != SdlInit(sdl_hwnd, dst_width, dst_height)) {
		WriteLog("CodecInit failed.");
		return -1;
	}

	WriteLog(std::string("video_stream_index is ") + std::to_string(video_stream_index));

	WriteLog("OpenCamera end.");
	return video_stream_index;
}


int UsbVideoService::GetUsbFrame(AVPacket& pkt)
{
	WriteLog("GetH264Frame begin.");
	if (!is_init) {
		WriteLog("!is_init");
		return -10000;
	}

	if (pkt.stream_index == video_stream_index) {//fprintf(stdout, "video stream, packet size: %d\n", pkt.size);
		char tmp_buf[256] = {0};
		sprintf(tmp_buf, "pkt.size is %d.", pkt.size);
		WriteLog(tmp_buf);
		return 1;
	}

	if (pkt.stream_index == audio_stream_index) {//fprintf(stdout, "audio stream, packet size: %d\n", pkt.size);
		return 2;
	}
	//av_packet_unref(&pkt);
	WriteLog("GetH264Frame end.");
	return 0;
}

int UsbVideoService::GetYuv420pFrame(uint8_t** yuv420p_buf, int& buf_len)
{
	WriteLog("GetYuv420pFrame begin.");
	if (!is_init) {
		WriteLog("!is_init");
		return -10000;
	}

	AVPacket *pkt = nullptr;
	AVFrame *fr = nullptr;
	AVFrame *yuv = nullptr;
	uint8_t *buf = nullptr;
	int vsize = 0;
	pkt = av_packet_alloc(); //free
	fr = av_frame_alloc(); //free
	yuv = av_frame_alloc();//free
	vsize = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, avcode_ctx->width, avcode_ctx->height, 1);
	buf = (uint8_t *)av_malloc(vsize); //free
	av_image_fill_arrays(yuv->data, yuv->linesize, buf, AV_PIX_FMT_YUV420P, avcode_ctx->width, avcode_ctx->height, 1);

	//AVPacket* pkt = nullptr;
	int ret = 0;

	ret = av_read_frame(av_format_ctx, pkt);
	if (ret < 0) {
		fprintf(stderr, "error or end of file: %d\n", ret);
		return -1;
	}

	if (is_support_codec && pkt->stream_index == video_stream_index) {
		char tmp_buf[256] = { 0 };
		sprintf(tmp_buf, "pkt.size is %d.", pkt->size);
		WriteLog(tmp_buf);

		if ((ret = avcodec_send_packet(avcode_ctx, pkt)) != 0)
		{
			char err_buf[256] = { 0 };
			cout << "Send video stream packet failed." << endl;
			av_strerror(ret, err_buf, 256);
			WriteLog(err_buf);
			return -2;
		}
		if ((ret = avcodec_receive_frame(avcode_ctx, fr)) != 0)
		{
			char err_buf[256] = { 0 };
			WriteLog("Receive video frame failed.");
			av_strerror(ret, err_buf, 256);
			WriteLog(err_buf);
			return -1;
		}
		sws_scale(sws_ctx, fr->data, fr->linesize, 0, avcode_ctx->height, yuv->data, yuv->linesize);

		if (is_support_sdl) {
			ShowYuv420p(yuv->data[0], yuv->linesize[0]);
		}

#ifdef SAVE_YUV420P_FILE
		uint8_t* p = new uint8_t[vsize];
		if (nullptr == p) {
			WriteLog("Receive video frame failed.");
			return -1;
		}

		int a = 0, i;
		for (i = 0; i < avcode_ctx->height; i++)
		{
			memcpy(p + a, yuv->data[0] + i * yuv->linesize[0], avcode_ctx->width);
			a += avcode_ctx->width;
		}
		for (i = 0; i < avcode_ctx->height / 2; i++)
		{
			memcpy(p + a, yuv->data[1] + i * yuv->linesize[1], avcode_ctx->width / 2);
			a += avcode_ctx->width / 2;
		}
		for (i = 0; i < avcode_ctx->height / 2; i++)
		{
			memcpy(p + a, yuv->data[2] + i * yuv->linesize[2], avcode_ctx->width / 2);
			a += avcode_ctx->width / 2;
		}

		{
			char tmp_buf[256] = { 0 };
			sprintf(tmp_buf, "vsize is %d, a is %d,  %d - %d - %d, yuv->pkt_size is %d", vsize, a, yuv->linesize[0], yuv->linesize[1], yuv->linesize[2], yuv->pkt_size);
			WriteLog(tmp_buf);

		}
		//memcpy((void*)p, (void*)yuv->data[0], (int)vsize);
		*yuv420p_buf = p;
		buf_len = vsize;//yuv->linesize[0] (int)yuv->linesize[0];
#endif

		av_packet_free(&pkt);
		av_frame_free(&fr);
		av_frame_free(&yuv);
		av_free(buf);
		return 1;

	} else if (pkt->stream_index == audio_stream_index) {//fprintf(stdout, "audio stream, packet size: %d\n", pkt.size);
		WriteLog("audio_stream_index");
		return 2;
	} else {
		//goto end.
	}

	WriteLog("GetYuv420pFrame end.");
	return 0;
}

void UsbVideoService::UnInit()
{
	if (!is_init) {
		WriteLog("!is_init");
		return;
	}

	CloseCamera();
// 	if (nullptr != av_format_ctx) {
// 		avformat_free_context(av_format_ctx);
// 		av_format_ctx = nullptr;
// 	}

	is_init = false;
}

void UsbVideoService::CloseCamera()
{
	if (!is_init) {
		WriteLog("!is_init");
		return;
	}

	if (nullptr != av_format_ctx) {
		avformat_close_input(&av_format_ctx);
		av_format_ctx = nullptr;
	}

	if (nullptr != sdl_window) {
		SdlUnInit();
		av_format_ctx = nullptr;
	}
	

	is_init = false;
}

void UsbVideoService::SdlUnInit()
{
	SDL_DestroyTexture(sdl_texture);
	SDL_DestroyRenderer(sdl_rend);
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}


void UsbVideoService::ShowYuv420p(const void* pixels, int pitch) {
	SDL_Rect srect = { 0 };
	srect.w = dst_width;
	srect.h = dst_height;

	//SDL_UpdateTexture(sdl_texture, &srect, yuv->data[0], yuv->linesize[0]);
	SDL_UpdateTexture(sdl_texture, &srect, pixels, pitch);
	SDL_RenderClear(sdl_rend);
	SDL_RenderCopy(sdl_rend, sdl_texture, NULL, NULL);
	SDL_RenderPresent(sdl_rend);

	//std::this_thread::sleep_for(std::chrono::milliseconds(25));
}

int UsbVideoService::SdlInit(void* hwnd, int width, int height)
{
	//SDL_Rect srect = { 0 };

#ifdef _HZG_SDL_22
	//sw = SDL_CreateWindowFrom(hWnd);
	sw = SDL_CreateWindow("video", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 680, 540, SDL_WINDOW_OPENGL);

	//sw = (SDL_Window *)hWnd;


	sr = SDL_CreateRenderer(sw, -1, 0);
	ste = SDL_CreateTexture(sr, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, cctx->width, cctx->height);
	if (!sw || !sr || !ste) {
		cout << "Create SDL windows failed!" << endl;
		return -1;
	}
	srect.w = cctx->width;
	srect.h = cctx->height;
#endif

	static int m = 0;
	if (m == 0)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			WriteLog("SDL init failed.");
			return -1;
		}
		m = 1;
	}

	if (nullptr == hwnd) {
		WriteLog("SDL_CreateWindow." + std::to_string(width) + std::string(",") + std::to_string(height));
		sdl_window = SDL_CreateWindow("video", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 680, 540, SDL_WINDOW_OPENGL);
	} else {
		sdl_window = SDL_CreateWindowFrom(hwnd);
		WriteLog("SDL_CreateWindowFrom.");
		//sdl_window = (SDL_Window *)hwnd;
	}

	if (nullptr == sdl_window) {
		WriteLog("CreateWindow failed.");
		return -1;
	}

	sdl_rend = SDL_CreateRenderer(sdl_window, -1, 0);
	sdl_texture = SDL_CreateTexture(sdl_rend, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!sdl_window || !sdl_rend || !sdl_texture) {
		WriteLog("Create SDL windows failed.");
		return -1;
	}
// 	srect.w = dst_width;
// 	srect.h = dst_height;
	return 0;
}

int UsbVideoService::CodecInit()
{
	WriteLog("CodecInit begin.");
	if (!is_init) {
		WriteLog("!is_init");
		return -10000;
	}

	avcode_ctx = avcodec_alloc_context3(NULL);
	if (nullptr == avcode_ctx) {
		WriteLog("avcode_ctx faild.");
		return -1;
	}

	if (avcodec_parameters_to_context(avcode_ctx, av_format_ctx->streams[video_stream_index]->codecpar) < 0)
	{
		WriteLog("Error: Copy stream failed.");
		return -1;
	}

	av_codec = avcodec_find_decoder(avcode_ctx->codec_id); // example : AV_CODEC_ID_H264
	if (nullptr == av_codec) {
		WriteLog("Error: Find Decoder failed.");
		return -1;
	}

	if (avcodec_open2(avcode_ctx, av_codec, NULL) != 0) {
		WriteLog("Error: Open codec failed.");
		return -1;
	}


	dst_width = avcode_ctx->width;
	dst_height = avcode_ctx->height;
	sws_ctx = sws_getContext(avcode_ctx->width, avcode_ctx->height, avcode_ctx->pix_fmt, dst_width, dst_height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
	if (nullptr == av_codec) {
		WriteLog("Error: Get swscale context failed.");
		return -1;
	}
	char tmp[256] = {0};
	sprintf(tmp, "cctx->pix_fmt: %d, AV_PIX_FMT_YUYV422=%d, cctx->width=%d,cctx->height=%d, cctx->codec_id=%d\n", 
		avcode_ctx->pix_fmt, AV_PIX_FMT_YUYV422, avcode_ctx->width, avcode_ctx->height, avcode_ctx->codec_id);
	WriteLog(tmp);
	WriteLog("CodecInit end.");
	is_init_codec = true;
	return 0;
}

int UsbVideoService::CodecUnInit()
{
	WriteLog("CodecUnInit begin.");
	if (!is_init) {
		WriteLog("!is_init");
		return -10000;
	}

	if (nullptr != sws_ctx) {
		sws_freeContext(sws_ctx);
		sws_ctx = nullptr;
	}

	is_init_codec = false;
	WriteLog("CodecUnInit end.");
}
