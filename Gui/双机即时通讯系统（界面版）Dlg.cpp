
// 双机即时通讯系统（界面版）Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "双机即时通讯系统（界面版）.h"
#include "双机即时通讯系统（界面版）Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString IPA[4] = { _T("0"),_T("0"),_T("0"),_T("0") };
CString IPAddress;
char ipAddress[16];
CString readString;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C双机即时通讯系统（界面版）Dlg 对话框



C双机即时通讯系统（界面版）Dlg::C双机即时通讯系统（界面版）Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C双机即时通讯系统（界面版）Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C双机即时通讯系统（界面版）Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &C双机即时通讯系统（界面版）Dlg::OnIpnFieldchangedIpaddress1)
	ON_BN_CLICKED(IDC_BUTTON1, &C双机即时通讯系统（界面版）Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C双机即时通讯系统（界面版）Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C双机即时通讯系统（界面版）Dlg 消息处理程序

BOOL C双机即时通讯系统（界面版）Dlg::OnInitDialog()
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

	SetDlgItemText(IDC_IPADDRESS1, (CString)"127.0.0.1");
	// TODO: 在此添加额外的初始化代码
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		SetDlgItemText(IDC_EDIT2, (CString)"ERROR : Winsock load failed !");
		SetDlgItemText(IDC_EDIT3, (CString)"ERROR : Winsock load failed !");
		return false;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C双机即时通讯系统（界面版）Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C双机即时通讯系统（界面版）Dlg::OnPaint()
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
HCURSOR C双机即时通讯系统（界面版）Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C双机即时通讯系统（界面版）Dlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	IPA[pIPAddr->iField].Format(_T("%d"), pIPAddr->iValue);
	IPAddress = IPA[0] + _T(".") + IPA[1] + _T(".") + IPA[2] + _T(".") + IPA[3];
	*pResult = 0;
}


void C双机即时通讯系统（界面版）Dlg::OnBnClickedButton1()
{
	GetDlgItemText(IDC_IPADDRESS1,IPAddress);
	wchar_t *changeTemp = IPAddress.GetBuffer();
	size_t len = wcslen(changeTemp) + 1;
	size_t converted = 0;
	wcstombs_s(&converted, ipAddress, len, changeTemp, _TRUNCATE);
	hThreadServer = CreateThread(NULL, 0, serverWork, NULL, 0, NULL);
}


void C双机即时通讯系统（界面版）Dlg::OnBnClickedButton2()
{
	ResumeThread(hThreadClient);
}
