
// MFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg.h : ͷ�ļ�
//

#pragma once


// CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg �Ի���
class CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg : public CDialogEx
{
// ����
public:
	CMFC_ReadUsbAndShowVideoByFfmpegAndSdlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_READUSBANDSHOWVIDEOBYFFMPEGANDSDL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
