
// Lottery5.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLottery5App:
// �йش����ʵ�֣������ Lottery5.cpp
//

class CLottery5App : public CWinAppEx
{
public:
	CLottery5App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLottery5App theApp;