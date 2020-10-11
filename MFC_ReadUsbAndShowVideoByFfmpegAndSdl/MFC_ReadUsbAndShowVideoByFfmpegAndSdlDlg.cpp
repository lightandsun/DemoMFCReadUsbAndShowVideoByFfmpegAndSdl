
// MFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_ReadUsbAndShowVideoByFfmpegAndSdl.h"
#include "MFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg 对话框



CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::IDD, pParent)
	, cam1(_T(""))
	, cam2(_T(""))
	, cam3(_T(""))
	, frame_rate1(_T(""))
	, frame_rate2(_T(""))
	, frame_rate3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAM_NAME1, cam1);
	DDX_Text(pDX, IDC_CAM_NAME2, cam2);
	DDX_Text(pDX, IDC_CAM_NAME3, cam3);
	DDX_Text(pDX, IDC_RATE1, frame_rate1);
	DDX_Text(pDX, IDC_RATE2, frame_rate2);
	DDX_Text(pDX, IDC_RATE3, frame_rate3);
}

BEGIN_MESSAGE_MAP(CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedOk)
	ON_BN_CLICKED(BTN_PLAY1, &CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedPlay1)
	ON_BN_CLICKED(BTN_PLAY2, &CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedPlay2)
	ON_BN_CLICKED(BTN_PLAY3, &CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedPlay3)
END_MESSAGE_MAP()


// CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg 消息处理程序

BOOL CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码


// 	cam1;
// 	cam2;
// 	cam3;
// 	frame_rate1;
// 	frame_rate2;
// 	frame_rate3;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#include "read_usb_video.h"
#include<iostream>
using namespace std;

void write(char* p, int len, char *path) {
	FILE *fp;
	if ((fp = fopen(path, "ab+")) == NULL) {
		cout << "文件打开失败！" << endl;
		exit(0);
	}

	if (fwrite(p, len, 1, fp) != 1) {
		cout << "写入失败！" << endl;
	}
	fclose(fp);
}


#include <chrono>
#include <string>
using namespace std;
std::string GenerateFileName()
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&t);
	char date[60] = { 0 };
	sprintf(date, "%d%02d%02d-%02d%02d%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return move(std::string(date));
}

void GetYUY2()
{
	UsbVideoService usb_svr;

	if (usb_svr.Init() < 0)
	{
		return;
	}
	//Integrated Webcam
	if (usb_svr.OpenCamera(DSHOW, "Intel(R) RealSense(TM) 3D Camera (Front F200) RGB", "") < 0)//
	{
		WriteLog("OpenCamera failed.");
		return;
	}

	WriteLog("will start while.");
	int count = 0;
	while (true)
	{
		count++;
		WriteLog("in while.");
		AVPacket pkt;

		if (1 == usb_svr.GetUsbFrame(pkt))
		{
			if (count > 50){
				std::string tmp_name = GenerateFileName();
				tmp_name = tmp_name + "." + std::to_string(count) + ".yuv";
				write((char*)pkt.data, pkt.size, (char*)tmp_name.c_str());
				break;
			}
		}
	}
}

#if 0
https://blog.csdn.net/komtao520/article/details/51098272
CString str("我爱中国");

//一、多字节字符集情况下CString转换为char*
//char *s=(LPSTR)(LPCTSTR)str;

//二、Unicode字符集情况下CString转换为char*
//①
int n = str.GetLength(); //按字符计算，str的长度
int len = WideCharToMultiByte(CP_ACP, 0, str, n, NULL, 0, NULL, NULL);//按Byte计算str长度
char *pChStr1 = new char[len + 1];//按字节为单位
WideCharToMultiByte(CP_ACP, 0, str, n, pChStr1, len, NULL, NULL);//宽字节转换为多字节编码
pChStr1[len] = '\0';//不要忽略末尾结束标志

//②使用函数：T2A,W2A(未尝试)
USES_CONVERSION;//声明标示符
//调用函数，T2A和W2A均支持ATL和MFC中字符转换
//char *pChStr2 = T2A(str);
char *pChStr2 = W2A(str);//也可以实现转换
#endif

// Unicode 是宽字符的一种
std::string Unicode2StdString(CString v)
{
	int n = v.GetLength(); //按字符计算，str的长度
	int len = WideCharToMultiByte(CP_ACP, 0, v, n, NULL, 0, NULL, NULL);//按Byte计算str长度
	char *pChStr1 = new char[len + 1];//按字节为单位
	WideCharToMultiByte(CP_ACP, 0, v, n, pChStr1, len, NULL, NULL);//宽字节转换为多字节编码
	pChStr1[len] = '\0';//不要忽略末尾结束标志

	return std::string(pChStr1);
}


	//USB2.0_CAM1
	//Integrated Webcam 
	//Intel(R) RealSense(TM) 3D Camera (Front F200) RGB
	//Intel(R) RealSense(TM) 3D Camera (Front F200) Depth
void ShowThread(void* dlg)
{
	UsbVideoService usb_svr;

	CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg* dlg_this = (CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg*)dlg;
	CWnd *pWnd = dlg_this->GetDlgItem(IDC_STATIC1); // 取得控件的指针
	HWND hwnd = pWnd->GetSafeHwnd(); // 取得控件的句柄
	if (usb_svr.Init(true, hwnd) < 0)
	{
		return;
	}

	if (usb_svr.OpenCamera(DSHOW, Unicode2StdString(dlg_this->cam1), Unicode2StdString(dlg_this->frame_rate1)) < 0)// "640x480"
	{
		WriteLog("OpenCamera failed.");
		return;
	}

	WriteLog("will start while.");
	int count = 0;
	uint8_t* yuv420p_buf = nullptr;
	int buf_len = 0;


	while (true)
	{
		buf_len = 0;
		count++;
		WriteLog("in while.");

		if (1 == usb_svr.GetYuv420pFrame(&yuv420p_buf, buf_len))
		{
// 			if (count > 3000){
// 				std::string tmp_name = GenerateFileName();
// 				tmp_name = tmp_name + "-yuv420p-" + std::to_string(count) + ".yuv";
// 				write((char*)yuv420p_buf, buf_len, (char*)tmp_name.c_str());
// 				break;
// 			}
		}
	}
}

void ShowThread2(void* dlg)
{
	UsbVideoService usb_svr;

	CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg* dlg_this = (CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg*)dlg;
	CWnd *pWnd = dlg_this->GetDlgItem(IDC_STATIC2); // 取得控件的指针
	HWND hwnd = pWnd->GetSafeHwnd(); // 取得控件的句柄
	if (usb_svr.Init(true, hwnd) < 0)
	{
		return;
	}

	if (usb_svr.OpenCamera(DSHOW, Unicode2StdString(dlg_this->cam2), Unicode2StdString(dlg_this->frame_rate2)) < 0)// "640x480"
	{
		WriteLog("OpenCamera failed.");
		return;
	}

	WriteLog("will start while.");
	int count = 0;
	uint8_t* yuv420p_buf = nullptr;
	int buf_len = 0;

	while (true)
	{
		buf_len = 0;
		count++;
		WriteLog("in while.");

		if (1 == usb_svr.GetYuv420pFrame(&yuv420p_buf, buf_len))
		{
			// 			if (count > 3000){
			// 				std::string tmp_name = GenerateFileName();
			// 				tmp_name = tmp_name + "-yuv420p-" + std::to_string(count) + ".yuv";
			// 				write((char*)yuv420p_buf, buf_len, (char*)tmp_name.c_str());
			// 				break;
			// 			}
		}
	}
}

void ShowThread3(void* dlg)
{
	UsbVideoService usb_svr;

	CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg* dlg_this = (CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg*)dlg;
	CWnd *pWnd = dlg_this->GetDlgItem(IDC_STATIC3); // 取得控件的指针
	HWND hwnd = pWnd->GetSafeHwnd(); // 取得控件的句柄
	if (usb_svr.Init(true, hwnd) < 0)
	{
		return;
	}

	if (usb_svr.OpenCamera(DSHOW, Unicode2StdString(dlg_this->cam3), Unicode2StdString(dlg_this->frame_rate3)) < 0)// "640x480"
	{
		WriteLog("OpenCamera failed.");
		return;
	}

	WriteLog("will start while.");
	int count = 0;
	uint8_t* yuv420p_buf = nullptr;
	int buf_len = 0;

	while (true)
	{
		buf_len = 0;
		count++;
		WriteLog("in while.");

		if (1 == usb_svr.GetYuv420pFrame(&yuv420p_buf, buf_len))
		{
			// 			if (count > 3000){
			// 				std::string tmp_name = GenerateFileName();
			// 				tmp_name = tmp_name + "-yuv420p-" + std::to_string(count) + ".yuv";
			// 				write((char*)yuv420p_buf, buf_len, (char*)tmp_name.c_str());
			// 				break;
			// 			}
		}
	}
}



void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::GetYuv420p()
{
	UsbVideoService usb_svr;


	CWnd *pWnd = GetDlgItem(IDC_STATIC1); // 取得控件的指针
	HWND hwnd = pWnd->GetSafeHwnd(); // 取得控件的句柄
	if (usb_svr.Init(true, hwnd) < 0)
	{
		return;
	}
	//Integrated Webcam 
	//Intel(R) RealSense(TM) 3D Camera (Front F200) RGB
	if (usb_svr.OpenCamera(DSHOW, "Intel(R) RealSense(TM) 3D Camera (Front F200) Depth", "") < 0)//
	{
		WriteLog("OpenCamera failed.");
		return;
	}

	WriteLog("will start while.");
	int count = 0;
	uint8_t* yuv420p_buf = nullptr;
	int buf_len = 0;


	while (true)
	{
		buf_len = 0;
		count++;
		WriteLog("in while.");

		if (1 == usb_svr.GetYuv420pFrame(&yuv420p_buf, buf_len))
		{
			if (count > 3000){
				std::string tmp_name = GenerateFileName();
				tmp_name = tmp_name + "-yuv420p-" + std::to_string(count) + ".yuv";
				write((char*)yuv420p_buf, buf_len, (char*)tmp_name.c_str());
				break;
			}
		}
	}
}

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL.h"

#ifdef __cplusplus
}
#endif

void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::TestSdl()
{

	SDL_Window *sw = NULL;
	SDL_Renderer *sr = NULL;
	SDL_Texture *ste = NULL;
	SDL_Rect srect = { 0 };
	//	av_register_all();  //ffmpeg 4.0 After no
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		WriteLog("SDL init failed!");
		return;
	}


	CWnd *pWnd = GetDlgItem(IDC_STATIC2); // 取得控件的指针
	HWND hwnd = pWnd->GetSafeHwnd(); // 取得控件的句柄
	sw = SDL_CreateWindowFrom(hwnd);
	if (!sw) {
		WriteLog("!sw failed!");
		return;
	}
	//sw = SDL_CreateWindow("video", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 680, 540, SDL_WINDOW_OPENGL);

	//sw = (SDL_Window *)hWnd;


	sr = SDL_CreateRenderer(sw, -1, 0);
	if (!sr) {
		WriteLog("!sr failed!");
		return;
	}
	ste = SDL_CreateTexture(sr, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, 680, 540);
	if (!ste) {
		WriteLog("!sw failed!");
		return;
	}
// 	srect.w = cctx->width;
// 	srect.h = cctx->height;
}

#include <chrono> //C++11时间类标准模板库
#include<thread>
using namespace std;

void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();Integrated Webcam


	//GetYuv420p();

	thread mythread1(ShowThread, (void*)this);
	mythread1.detach();
	thread mythread2(ShowThread2, (void*)this);
	mythread2.detach();
	thread mythread3(ShowThread3, (void*)this);
	mythread3.detach();

	//TestSdl();
	//CDialogEx::OnOK();
}


void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedPlay1()
{
	// TODO:  在此添加控件通知处理程序代码

	thread mythread1(ShowThread, (void*)this);
	mythread1.detach();
	UpdateData(TRUE);
}


void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedPlay2()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);;
	thread mythread2(ShowThread2, (void*)this);
	mythread2.detach();
}


void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedPlay3()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	thread mythread3(ShowThread3, (void*)this);
	mythread3.detach();
}
