#pragma once
#include "stdafx.h"
#include "Resource.h"

CString serverHistory;
CString clientHistory;
DWORD WINAPI serverWork(LPVOID lpparameter)
{
	int ipLen, ipSend;
	SOCKET sockListen, sockAccept;
	struct sockaddr_in server, client;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, (CString)"ERROR : Winsock load failed !");
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT3, (CString)"ERROR : Winsock load failed !");
		return false;
	}
	if ((sockListen = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		WSACleanup();
		CString temp;
		temp.Format(_T("SERVER ERROR : socket failed - %d \r\n"), WSAGetLastError());
		serverHistory += temp;
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, serverHistory);
		return false;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockListen, (LPSOCKADDR)&server, sizeof(server)) == SOCKET_ERROR) {
		WSACleanup();
		CString temp;
		temp.Format(_T("SERVER ERROR : bind failed -  %d \r\n"), WSAGetLastError());
		serverHistory += temp;
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, serverHistory);
		return false;
	}
	if (listen(sockListen, 5) == SOCKET_ERROR) {
		WSACleanup();
		CString temp;
		temp.Format(_T("SERVER ERROR : listen failse -  %d \r\n"), WSAGetLastError());
		serverHistory += temp;
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, serverHistory);
		return false;
	}
	ipLen = sizeof(client);
	hThreadClient = CreateThread(NULL, 0, clientWork, NULL, 0, NULL);
	while (true) {
		serverHistory += (CString)"SERVER Wating connect ...\r\n";
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, serverHistory);
		if ((sockAccept = accept(sockListen, (struct sockaddr*)&client, &ipLen)) == INVALID_SOCKET) {
			WSACleanup();
			CString temp;
			temp.Format(_T("SERVER ERROR : accept failed -  %d \r\n"), WSAGetLastError());
			serverHistory += temp;
			SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, serverHistory);
			return false;
		}
		{
			CString temp;
			temp += (CString)"SERVER Client IP : [" + (CString)inet_ntoa(client.sin_addr) + (CString)"] , port : [";
			CString temp1;
			temp1.Format(_T("%d]\r\n"), ntohs(client.sin_port));
			temp += temp1;
			serverHistory += temp;
			SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, serverHistory);
		}
		char *msg = new char[500];
		int msgLen = recv(sockAccept, msg, 500, 0);
		msg[msgLen] = 0;
		if (msgLen > 0) {
			CString temp;
			temp += (CString)"SERVER TIP : new message : " + (CString)msg + (CString)"\r\n";
			serverHistory += temp;
			SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, serverHistory);
		}
		for (int i = 0; i < msgLen; ++i) {
			++msg[i];
		}
		if ((ipSend = send(sockAccept, msg, strlen(msg), 0)) == SOCKET_ERROR) {
			WSACleanup();
			CString temp;
			temp.Format(_T("SERVER ERROR : send failed -  %d \r\n"), WSAGetLastError());
			serverHistory += temp;
			SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, serverHistory);
			return false;
		}
		delete[] msg;
		msg = NULL;
		closesocket(sockAccept);
	}
	closesocket(sockListen);
	WSACleanup();
}

DWORD WINAPI clientWork(LPVOID lpparameter)
{
	int ipLen;
	SOCKET client;
	struct sockaddr_in server;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT2, (CString)"ERROR : Winsock load failed !");
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT3, (CString)"ERROR : Winsock load failed !");
		return false;
	}
	

	//SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT1, IPAddress);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ipAddress);
	server.sin_port = htons(PORT);
	CString temp;
	temp += (CString)"CLIENT TIP : connect to [" + (CString)inet_ntoa(*((in_addr *)&(server.sin_addr))) + (CString)"] \r\n";
	clientHistory += temp;
	SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT3, clientHistory);
	while (true) {
		if ((client = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
			WSACleanup();
			CString temp;
			temp.Format(_T("CLIENT ERROR : socket failed - %d \r\n"), WSAGetLastError());
			clientHistory += temp;
			SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT3, clientHistory);
			return false;
		}
		if (connect(client, (struct sockaddr*)&server, sizeof(server)) == INVALID_SOCKET) {
			WSACleanup();
			CString temp;
			temp.Format(_T("CLIENT ERROR : connect failed - %d \r\n"), WSAGetLastError());
			clientHistory += temp;
			SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT3, clientHistory);
			return false;
		}
		SuspendThread(hThreadClient);
		char* msg = new char[500];
		GetDlgItemTextA((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT1, msg, 500);
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT1, (CString)"");
		int msgLen;
		if ((msgLen = send(client, msg, strlen(msg), 0)) == SOCKET_ERROR) {
			WSACleanup();
			CString temp;
			temp.Format(_T("CLIENT ERROR : send msg failed - %d \r\n"), GetLastError());
			clientHistory += temp;
			SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT3, clientHistory);
		}
		if ((ipLen = recv(client, msg, strlen(msg), 0)) == SOCKET_ERROR) {
			WSACleanup();
			CString temp;
			temp.Format(_T("CLIENT ERROR : recv failed - %d \r\n"), WSAGetLastError());
			clientHistory += temp;
			SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT3, clientHistory);
			return false;
		}
		CString temp;
		temp += (CString)"CLIENT TIP : this is the return message : " + (CString)msg + (CString)"\r\n";
		clientHistory += temp;
		SetDlgItemText((HWND)((CFrameWnd*)AfxGetApp()->m_pMainWnd->m_hWnd), IDC_EDIT3, clientHistory);
	}
	closesocket(client);
	WSACleanup();
}