
// LLKGame.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLLKGameApp: 
// �йش����ʵ�֣������ LLKGame.cpp
//

class CLLKGameApp : public CWinApp
{
public:
	CLLKGameApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLLKGameApp theApp;