
// MFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg.h : 头文件
//

#pragma once


// CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg 对话框
class CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg : public CDialogEx
{
// 构造
public:
	CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC_READUSBANDSHOWVIDEOBYFFMPEGANDSDL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void GetYuv420p();
	void TestSdl();
	CString cam1;
	CString cam2;
	CString cam3;
	CString frame_rate1;
	CString frame_rate2;
	CString frame_rate3;
	afx_msg void OnBnClickedPlay1();
	afx_msg void OnBnClickedPlay2();
	afx_msg void OnBnClickedPlay3();
};
