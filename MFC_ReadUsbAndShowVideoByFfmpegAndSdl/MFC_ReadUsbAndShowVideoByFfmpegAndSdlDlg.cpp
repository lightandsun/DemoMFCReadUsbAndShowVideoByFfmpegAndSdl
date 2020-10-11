
// MFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_ReadUsbAndShowVideoByFfmpegAndSdl.h"
#include "MFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg �Ի���



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


// CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg ��Ϣ�������

BOOL CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������


// 	cam1;
// 	cam2;
// 	cam3;
// 	frame_rate1;
// 	frame_rate2;
// 	frame_rate3;


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		cout << "�ļ���ʧ�ܣ�" << endl;
		exit(0);
	}

	if (fwrite(p, len, 1, fp) != 1) {
		cout << "д��ʧ�ܣ�" << endl;
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
CString str("�Ұ��й�");

//һ�����ֽ��ַ��������CStringת��Ϊchar*
//char *s=(LPSTR)(LPCTSTR)str;

//����Unicode�ַ��������CStringת��Ϊchar*
//��
int n = str.GetLength(); //���ַ����㣬str�ĳ���
int len = WideCharToMultiByte(CP_ACP, 0, str, n, NULL, 0, NULL, NULL);//��Byte����str����
char *pChStr1 = new char[len + 1];//���ֽ�Ϊ��λ
WideCharToMultiByte(CP_ACP, 0, str, n, pChStr1, len, NULL, NULL);//���ֽ�ת��Ϊ���ֽڱ���
pChStr1[len] = '\0';//��Ҫ����ĩβ������־

//��ʹ�ú�����T2A,W2A(δ����)
USES_CONVERSION;//������ʾ��
//���ú�����T2A��W2A��֧��ATL��MFC���ַ�ת��
//char *pChStr2 = T2A(str);
char *pChStr2 = W2A(str);//Ҳ����ʵ��ת��
#endif

// Unicode �ǿ��ַ���һ��
std::string Unicode2StdString(CString v)
{
	int n = v.GetLength(); //���ַ����㣬str�ĳ���
	int len = WideCharToMultiByte(CP_ACP, 0, v, n, NULL, 0, NULL, NULL);//��Byte����str����
	char *pChStr1 = new char[len + 1];//���ֽ�Ϊ��λ
	WideCharToMultiByte(CP_ACP, 0, v, n, pChStr1, len, NULL, NULL);//���ֽ�ת��Ϊ���ֽڱ���
	pChStr1[len] = '\0';//��Ҫ����ĩβ������־

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
	CWnd *pWnd = dlg_this->GetDlgItem(IDC_STATIC1); // ȡ�ÿؼ���ָ��
	HWND hwnd = pWnd->GetSafeHwnd(); // ȡ�ÿؼ��ľ��
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
	CWnd *pWnd = dlg_this->GetDlgItem(IDC_STATIC2); // ȡ�ÿؼ���ָ��
	HWND hwnd = pWnd->GetSafeHwnd(); // ȡ�ÿؼ��ľ��
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
	CWnd *pWnd = dlg_this->GetDlgItem(IDC_STATIC3); // ȡ�ÿؼ���ָ��
	HWND hwnd = pWnd->GetSafeHwnd(); // ȡ�ÿؼ��ľ��
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


	CWnd *pWnd = GetDlgItem(IDC_STATIC1); // ȡ�ÿؼ���ָ��
	HWND hwnd = pWnd->GetSafeHwnd(); // ȡ�ÿؼ��ľ��
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


	CWnd *pWnd = GetDlgItem(IDC_STATIC2); // ȡ�ÿؼ���ָ��
	HWND hwnd = pWnd->GetSafeHwnd(); // ȡ�ÿؼ��ľ��
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

#include <chrono> //C++11ʱ�����׼ģ���
#include<thread>
using namespace std;

void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	thread mythread1(ShowThread, (void*)this);
	mythread1.detach();
	UpdateData(TRUE);
}


void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedPlay2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);;
	thread mythread2(ShowThread2, (void*)this);
	mythread2.detach();
}


void CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg::OnBnClickedPlay3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	thread mythread3(ShowThread3, (void*)this);
	mythread3.detach();
}
