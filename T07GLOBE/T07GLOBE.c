 /*Vetoshkin Eugeni 10-5 2018*/
#include <stdio.h>

#include <time.h>
#include "GLOBE.h"
#define PI 3.14159265358979323846


#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);


VOID FlipFullScreen(HWND hWnd)
{
	static BOOL IsFullScreen = FALSE;
	static RECT SaveRC;

	if (!IsFullScreen)
	{
		RECT rc;
		HMONITOR hmon;
		MONITORINFOEX moninfo;
		
		GetWindowRect(hWnd, &SaveRC);
		hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
		moninfo.cbSize = sizeof(moninfo);
		GetMonitorInfo(hmon, (MONITORINFO *) &moninfo);
		rc = moninfo.rcMonitor;
		AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
		
		/*Fullscreen*/
		SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top + 15000, SWP_NOOWNERZORDER);
		IsFullScreen = TRUE;
	}
	else
	{
		SetWindowPos(hWnd, HWND_TOP, SaveRC.left, SaveRC.top, SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top, SWP_NOOWNERZORDER);
		IsFullScreen = FALSE;
	}


}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = MyWindowFunc;
	wc.lpszClassName = WND_CLASS_NAME;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
		return 0;

	}

	hWnd =
		CreateWindow(WND_CLASS_NAME, "title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return msg.wParam;
}

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	HDC hDC;
	//double t;
	
	static HDC hMemDC, hMemDCClock;
	static INT h, w;
	static HBITMAP hBm, hBmClock, hBmSnakeADD, hBmSnakeOR;
	HBRUSH hBr, hOldBr;
	/*BITMAP bm;
	SYSTEMTIME st;*/
   

	switch (Msg)
	{
	case WM_CREATE:
		
		SetTimer(hWnd, 1, 30, NULL);
		hDC = GetDC(hWnd);
		hMemDC = CreateCompatibleDC(hDC);
		hMemDCClock = CreateCompatibleDC(hDC);


		ReleaseDC(hWnd, hDC);
            	hBmClock = LoadImage(NULL, "ClockFace.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SelectObject(hMemDCClock, hBmClock);
		return 0;
		/*********************************************************************************/
	case WM_SIZE:

		w = LOWORD(lParam);
		h = HIWORD(lParam);

		if (hBm != NULL)
			DeleteObject(hBm);
		hDC = GetDC(hWnd);
		hBm = CreateCompatibleBitmap(hDC, w, h);
		SelectObject(hMemDC, hBm);
		ReleaseDC(hWnd, hDC);
		SendMessage(hWnd, WM_TIMER, wParam, lParam);
		return 0;
		/**********************************************************************************/
	
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			if (MessageBox(NULL, "Do you really want to close?", "CLOSING", MB_YESNO) == IDYES)
				SendMessage(hWnd, WM_DESTROY, wParam, lParam);
		if (wParam == VK_INSERT)
			FlipFullScreen(hWnd);
		return 0;
		/**********************************************************************************/
	case WM_CLOSE:
		if (MessageBox(NULL, "Do you really want to close?", "CLOSING", MB_YESNO) == IDYES)
			SendMessage(hWnd, WM_DESTROY, wParam, lParam);
		return 0;
		/**********************************************************************************/
	case WM_TIMER:
		hDC = GetDC(hWnd);
                		
		hBr = CreateSolidBrush(RGB(248, 248, 248));
		hOldBr = SelectObject(hMemDC, hBr);
		GetStockObject(NULL_PEN);
		Rectangle(hMemDC, 0, 0, w, h);

               ///  hBr = CreateSolidBrush(RGB(0, 0, 0));
		DrawGlobe(hMemDC, 20, w, h);

		BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
		DeleteObject(hBr);
		ReleaseDC(hWnd, hDC);
		return 0;
		/**********************************************************************************/
	case WM_DESTROY:
		
		DeleteObject(hBm);
		DeleteDC(hMemDC);
		DeleteDC(hMemDCClock);
		KillTimer(hWnd, 1);
		MessageBox(NULL, "All Processes have been stopped", "CLOSING", MB_OK);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

