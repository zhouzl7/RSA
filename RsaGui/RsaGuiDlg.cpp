
// RsaGuiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "RsaGui.h"
#include "RsaGuiDlg.h"
#include "afxdialogex.h"
#include "RSA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRsaGuiDlg 对话框

RSA rsa;

CRsaGuiDlg::CRsaGuiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RSAGUI_DIALOG, pParent)
	, digits(_T(""))
	, N(_T(""))
	, d(_T(""))
	, p(_T(""))
	, q(_T(""))
	, plaintext(_T(""))
	, ciphertext(_T(""))
	, decrypt_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRsaGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, digits);
	DDX_Text(pDX, IDC_EDIT3, N);
	DDX_Text(pDX, IDC_EDIT2, d);
	DDX_Text(pDX, IDC_EDIT4, p);
	DDX_Text(pDX, IDC_EDIT5, q);
	DDX_Text(pDX, IDC_EDIT6, plaintext);
	DDX_Text(pDX, IDC_EDIT7, ciphertext);
	DDX_Text(pDX, IDC_EDIT8, decrypt_text);
	DDX_Control(pDX, IDC_INIT, buttonInit);
	DDX_Control(pDX, IDC_ENCRYPT, buttonEncrypt);
	DDX_Control(pDX, IDC_DECRYPT, buttonDecrypt);
}

BEGIN_MESSAGE_MAP(CRsaGuiDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INIT, &CRsaGuiDlg::OnBnClickedInit)
	ON_BN_CLICKED(IDC_ENCRYPT, &CRsaGuiDlg::OnBnClickedEncrypt)
	ON_BN_CLICKED(IDC_DECRYPT, &CRsaGuiDlg::OnBnClickedDecrypt)
END_MESSAGE_MAP()


// CRsaGuiDlg 消息处理程序

BOOL CRsaGuiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRsaGuiDlg::OnPaint()
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
HCURSOR CRsaGuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRsaGuiDlg::OnBnClickedInit()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	buttonEncrypt.EnableWindow(0);
	buttonDecrypt.EnableWindow(0);
	buttonInit.EnableWindow(0);
	rsa.init(_ttoi(digits));
	N = rsa.N.toString().c_str();
	d = rsa.d.toString().c_str();
	p = rsa.p.toString().c_str();
	q = rsa.q.toString().c_str();
	buttonEncrypt.EnableWindow(1);
	buttonInit.EnableWindow(1);
	UpdateData(FALSE);
}


void CRsaGuiDlg::OnBnClickedEncrypt()
{
	UpdateData();
	if (plaintext.IsEmpty())
		return;
	string str(CW2A(plaintext.GetString()));
	BigInt m(str);
	ciphertext = rsa.encrypt(m).toString().c_str();
	buttonDecrypt.EnableWindow(1);
	UpdateData(FALSE);
	// TODO: 在此添加控件通知处理程序代码
}


void CRsaGuiDlg::OnBnClickedDecrypt()
{
	UpdateData();
	if (ciphertext.IsEmpty())
		return;
	string str(CW2A(ciphertext.GetString()));
	BigInt m(str);
	decrypt_text = rsa.decrypt(m).toString().c_str();
	//buttonEncrypt.EnableWindow(0);
	buttonDecrypt.EnableWindow(0);
	UpdateData(FALSE);
	// TODO: 在此添加控件通知处理程序代码
}
