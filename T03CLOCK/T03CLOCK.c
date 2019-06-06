 /*Vetoshkin Eugeni 10-5 2018*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
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
	BITMAP bm;
	SYSTEMTIME st;
    //HPEN hPenSeconds, hPenMinutes, hPenHours;

	POINT pnts1[4];
	POINT pnts2[4];
	POINT pnts3[4];

	switch (Msg)
	{
	case WM_CREATE:
		
		SetTimer(hWnd, 1, 30, NULL);
		hDC = GetDC(hWnd);
		hMemDC = CreateCompatibleDC(hDC);
		hMemDCClock = CreateCompatibleDC(hDC);


		ReleaseDC(hWnd, hDC);
                hBmClock = LoadImage(NULL, "ClockFace.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                hBmSnake = LoadImage(NULL, "ClockFace.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
		GetLocalTime(&st);
		hDC = GetDC(hWnd);
		
		hBr = CreateSolidBrush(RGB(248, 248, 248));
		hOldBr = SelectObject(hMemDC, hBr);
		SelectObject(hMemDC, NULL_PEN);
		
		Rectangle(hMemDC, 0, 0, w, h);
		
		GetObject(hBmClock, sizeof(bm), &bm);
		

		BitBlt(hMemDC, (w - bm.bmWidth) / 2, (h - bm.bmHeight) / 2, bm.bmHeight, bm.bmWidth, hMemDCClock, 0, 0, SRCCOPY);

		pnts1[0].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) + (PI / 2)) * 10 + sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) - (PI / 2)) * 0 + (w / 2);
		pnts1[1].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) + (PI / 2)) * 0 + sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) - (PI / 2)) * 10 + (w / 2);
		pnts1[2].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) - (PI / 2)) * (bm.bmWidth / 2.5) + w / 2;
		pnts1[3].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) + (PI / 2)) * 0 + sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) - (PI / 2)) * -10 + (w / 2);

		pnts1[0].y = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) + (PI / 2)) * 0 - sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) - (PI / 2)) * 10 + (h / 2);
		pnts1[1].y = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) + (PI / 2)) * 10 - sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) - (PI / 2)) * 0 + (h / 2);
		pnts1[2].y = sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) - (PI / 2)) * (bm.bmHeight / 2.5) + h / 2;
		pnts1[3].y = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) + (PI / 2)) * -10 - sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1) - (PI / 2)) * 0 + (h / 2);


		pnts2[0].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) + (PI / 2)) * 15 + sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) - (PI / 2)) * 0 + (w / 2);
		pnts2[1].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) + (PI / 2)) * 0 + sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) - (PI / 2)) * 15 + (w / 2);
		pnts2[2].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) - (PI / 2)) * (bm.bmWidth / 2.7) + w / 2;
		pnts2[3].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) + (PI / 2)) * 0 + sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) - (PI / 2)) * -15 + (w / 2);

		pnts2[0].y = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) + (PI / 2)) * 0 - sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) - (PI / 2)) * 15 + (h / 2);
		pnts2[1].y = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) + (PI / 2)) * 15 - sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) - (PI / 2)) * 0 + (h / 2);
		pnts2[2].y = sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) - (PI / 2)) * (bm.bmHeight / 2.7) + h / 2;
		pnts2[3].y = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) + (PI / 2)) * -15 - sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1) - (PI / 2)) * 0 + (h / 2);


		pnts3[0].x = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) + (PI / 2)) * 20 + sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) - (PI / 2)) * 0 + (w / 2);
		pnts3[1].x = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) + (PI / 2)) * 0 + sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) - (PI / 2)) * 20 + (w / 2);
		pnts3[2].x = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) - (PI / 2)) * (bm.bmWidth / 3) + w / 2;
		pnts3[3].x = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) + (PI / 2)) * 0 + sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) - (PI / 2)) * -20 + (w / 2);

		pnts3[0].y = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) + (PI / 2)) * 0 - sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) - (PI / 2)) * 20 + (h / 2);
		pnts3[1].y = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) + (PI / 2)) * 20 - sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) - (PI / 2)) * 0 + (h / 2);
		pnts3[2].y = sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) - (PI / 2)) * (bm.bmHeight / 3) + h / 2;
		pnts3[3].y = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) + (PI / 2)) * -20 - sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1) - (PI / 2)) * 0 + (h / 2);

		hBr = CreateSolidBrush(RGB(50, 50, 50));
		hOldBr = SelectObject(hMemDC, hBr);
		SelectObject(hDC, hOldBr);
		Polygon(hMemDC, pnts1, 4);
		
		hBr = CreateSolidBrush(RGB(75, 75, 75));
		hOldBr = SelectObject(hMemDC, hBr);
		SelectObject(hDC, hOldBr);
		Polygon(hMemDC, pnts2, 4);
		
		hBr = CreateSolidBrush(RGB(100, 100, 100));
		hOldBr = SelectObject(hMemDC, hBr);
		SelectObject(hDC, hOldBr);
		Polygon(hMemDC, pnts3, 4);

                BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCAND);

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

