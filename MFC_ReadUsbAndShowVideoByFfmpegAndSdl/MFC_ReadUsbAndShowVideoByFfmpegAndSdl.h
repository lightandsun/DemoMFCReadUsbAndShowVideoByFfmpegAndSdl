
// MFC_ReadUsbAndShowVideoByFfmpegAndSdl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_ReadUsbAndShowVideoByFfmpegAndSdlApp: 
// �йش����ʵ�֣������ MFC_ReadUsbAndShowVideoByFfmpegAndSdl.cpp
//

class CMFC_ReadUsbAndShowVideoByFfmpegAndSdlApp : public CWinApp
{
public:
	CMFC_ReadUsbAndShowVideoByFfmpegAndSdlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_ReadUsbAndShowVideoByFfmpegAndSdlApp theApp;