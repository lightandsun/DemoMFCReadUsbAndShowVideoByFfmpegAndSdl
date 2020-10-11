#ifndef __READ_USB_VIDEO_H__
#define __READ_USB_VIDEO_H__

#define VFWCAP "vfwcap"
#define  DSHOW "dshow"
#define  V4L2 "v4l2"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"

#include "SDL.h"

#ifdef __cplusplus
}
#endif


#include <string>
#include <atomic>



void WriteLog(std::string log);

class UsbVideoService
{
public:
	UsbVideoService();
	~UsbVideoService();
	/** 初始化
	*
	* @param[in] 无
	* @param[out] 无
	*
	* @return int 成功返回0，失败返回小于0的值
	*/
	int Init(bool is_codec = false, void* hwnd = nullptr);

	/** 反初始化（释放资源）
	*
	* @param[in] 无
	* @param[out] 无
	*
	* @return int 成功返回0，失败返回小于0的值
	* @note 不支持多线程调用，调用该函数时一定要保证其他资源占用已经停止。
	*		例如不能并发调用Init、OpenCamera等
	*/
	void UnInit();

	/** 打印设备列表
	*
	* 暂时保留该函数，目前仅适用控制台显示设备列表
	*
	* @param[in] 无
	* @param[out] 无
	*
	* @return int 成功返回0，失败返回小于0的值
	*/
	int GetDevList();
	int OpenCamera(std::string way, std::string camera_name, std::string frame_rate);
	void CloseCamera();

	/** 获取USB视频设备原始帧
	*
	* 目前默认的原始数据是YUYV/YUV422(YUY2), AV_CODEC_ID_RAWVIDEO
	*
	* @param[in] 无
	* @param[out] 无
	*
	* @return int 成功返回0，失败返回小于0的值
	*/
	int GetUsbFrame(AVPacket& pkt);

	int GetYuv420pFrame(uint8_t** yuv420p_buf, int& buf_len);
protected:
private:
	int AnalysisUrl(std::string way, std::string camera_name);

	/*read usb source data*/
	std::string input_format_name = "";
	AVFormatContext* av_format_ctx = nullptr;
	int video_stream_index = -1;
	int audio_stream_index = -1;
	AVDictionary* options = nullptr;

	std::atomic<bool> is_init = false;
	std::string url = "";

	/*codec*/
	std::atomic<bool> is_init_codec = false;
	bool is_support_codec = false;
	int dst_width = 0;
	int dst_height = 0;
	AVCodecContext* avcode_ctx = nullptr;
	AVCodec* av_codec = nullptr;
	SwsContext* sws_ctx = nullptr;

	int CodecInit();
	int CodecUnInit();

	/*sdl*/
	void* sdl_hwnd = nullptr;
	std::atomic<bool> is_support_sdl = false;
	SDL_Window* sdl_window = NULL;
	SDL_Renderer* sdl_rend = NULL;
	SDL_Texture* sdl_texture = NULL;
	int SdlInit(void* hwnd, int width, int height);
	void SdlUnInit();
	void ShowYuv420p(const void* pixels, int pitch);
};


#endif