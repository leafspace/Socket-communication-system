
// ˫����ʱͨѶϵͳ������棩.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C˫����ʱͨѶϵͳ������棩App: 
// �йش����ʵ�֣������ ˫����ʱͨѶϵͳ������棩.cpp
//

class C˫����ʱͨѶϵͳ������棩App : public CWinApp
{
public:
	C˫����ʱͨѶϵͳ������棩App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C˫����ʱͨѶϵͳ������棩App theApp;