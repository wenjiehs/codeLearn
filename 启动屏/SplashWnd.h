#pragma once
#include "afxwin.h"

// CSplashWnd

class CSplashWnd :
	public CWnd
{
public:
	CSplashWnd(void);
	~CSplashWnd(void);
	CImage m_image;
	static void ShowSplashScreen(CWnd* pParentWnd = NULL);
protected:
	BOOL Create(CWnd* pParentWnd = NULL); 
	static CSplashWnd* c_pSplashWnd;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
