
// ˫����ʱͨѶϵͳ������棩Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "˫����ʱͨѶϵͳ������棩.h"
#include "˫����ʱͨѶϵͳ������棩Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString IPA[4] = { _T("0"),_T("0"),_T("0"),_T("0") };
CString IPAddress;
char ipAddress[16];
CString readString;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// C˫����ʱͨѶϵͳ������棩Dlg �Ի���



C˫����ʱͨѶϵͳ������棩Dlg::C˫����ʱͨѶϵͳ������棩Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C˫����ʱͨѶϵͳ������棩Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C˫����ʱͨѶϵͳ������棩Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &C˫����ʱͨѶϵͳ������棩Dlg::OnIpnFieldchangedIpaddress1)
	ON_BN_CLICKED(IDC_BUTTON1, &C˫����ʱͨѶϵͳ������棩Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C˫����ʱͨѶϵͳ������棩Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C˫����ʱͨѶϵͳ������棩Dlg ��Ϣ�������

BOOL C˫����ʱͨѶϵͳ������棩Dlg::OnInitDialog()
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

	SetDlgItemText(IDC_IPADDRESS1, (CString)"127.0.0.1");
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		SetDlgItemText(IDC_EDIT2, (CString)"ERROR : Winsock load failed !");
		SetDlgItemText(IDC_EDIT3, (CString)"ERROR : Winsock load failed !");
		return false;
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C˫����ʱͨѶϵͳ������棩Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C˫����ʱͨѶϵͳ������棩Dlg::OnPaint()
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
HCURSOR C˫����ʱͨѶϵͳ������棩Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C˫����ʱͨѶϵͳ������棩Dlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	IPA[pIPAddr->iField].Format(_T("%d"), pIPAddr->iValue);
	IPAddress = IPA[0] + _T(".") + IPA[1] + _T(".") + IPA[2] + _T(".") + IPA[3];
	*pResult = 0;
}


void C˫����ʱͨѶϵͳ������棩Dlg::OnBnClickedButton1()
{
	GetDlgItemText(IDC_IPADDRESS1,IPAddress);
	wchar_t *changeTemp = IPAddress.GetBuffer();
	size_t len = wcslen(changeTemp) + 1;
	size_t converted = 0;
	wcstombs_s(&converted, ipAddress, len, changeTemp, _TRUNCATE);
	hThreadServer = CreateThread(NULL, 0, serverWork, NULL, 0, NULL);
}


void C˫����ʱͨѶϵͳ������棩Dlg::OnBnClickedButton2()
{
	ResumeThread(hThreadClient);
}
