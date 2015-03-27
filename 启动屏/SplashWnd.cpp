// SplashWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "HelloSplash.h"
#include "SplashWnd.h"


#include "stdafx.h"
#include "SplashWnd.h"
#include "resource.h"

CSplashWnd* CSplashWnd::c_pSplashWnd;

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

CSplashWnd::CSplashWnd(void)
{
}

CSplashWnd::~CSplashWnd(void)
{
}

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd)
{
	c_pSplashWnd = new CSplashWnd;
	if (!c_pSplashWnd->Create(pParentWnd))
		delete c_pSplashWnd;
	else
		c_pSplashWnd->UpdateWindow();
}

BOOL CSplashWnd::Create(CWnd* pParentWnd)
{

	HRESULT hr = m_image.Load(L"Splash.jpg");
	if(FAILED(hr))
	{
		return FALSE;
	};
	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0,m_image.GetWidth(),m_image.GetHeight() , pParentWnd->GetSafeHwnd(), NULL);
	return 0;
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// Center the window.
	CenterWindow();

	// Set a timer to destroy the splash screen.
	SetTimer(1, 5000, NULL);    

	return 0;
}

void CSplashWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	CRect rect;
	GetClientRect(&rect);
	HDC hdc = ::GetDC(m_hWnd);
	m_image.Draw(hdc,rect);

}

void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();

	CWnd::OnTimer(nIDEvent);
}

