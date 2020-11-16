
// RsaGuiDlg.h: 头文件
//

#pragma once


// CRsaGuiDlg 对话框
class CRsaGuiDlg : public CDialogEx
{
// 构造
public:
	CRsaGuiDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RSAGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString digits;
	CString N;
	CString d;
	CString p;
	CString q;
	CString plaintext;
	CString ciphertext;
	CString decrypt_text;
	afx_msg void OnBnClickedInit();
	afx_msg void OnBnClickedEncrypt();
	afx_msg void OnBnClickedDecrypt();
	CButton buttonInit;
	CButton buttonEncrypt;
	CButton buttonDecrypt;
};
