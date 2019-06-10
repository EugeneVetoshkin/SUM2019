  /*PROGRAMMER: Vetoshkin Eugene
  IFK: EV5
  CLASS: 10-5
  DATE: 1.06.2019
  FILE: "MAIN.C"
  */
#include "DEF.H"

#include <windows.h>
#define WND_CLASS_NAME "My window class"
#include <math.h>
#include <stdlib.h>



//extern VEC G[L][P];

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
        GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

        rc = moninfo.rcMonitor;

        AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

        SetWindowPos(hWnd, HWND_TOP,
            rc.left, rc.top,
            rc.right - rc.left, rc.bottom - rc.top + 201,
            SWP_NOOWNERZORDER);
        IsFullScreen = TRUE;
    }
    else
    {
        SetWindowPos(hWnd, HWND_TOP,
            SaveRC.left, SaveRC.top,
            SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
            SWP_NOOWNERZORDER);
        IsFullScreen = FALSE;
    }
} /* End of 'FlipFullScreen' function */

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShawCmd)
{
    WNDCLASS wc;
    HWND hWnd;
    MSG msg;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDI_ERROR);
    wc.hIcon = LoadIcon(hInstance, IDI_ERROR);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = MyWindowFunc;
    wc.lpszClassName = WND_CLASS_NAME;
    wc.lpszMenuName = NULL;
    wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Oh no", "ERROR", MB_OK);
        return 0;
    }
    hWnd = CreateWindow(WND_CLASS_NAME, "OKNO", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    while (TRUE)
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            DispatchMessage(&msg);
        }
        else
            SendMessage(hWnd, WM_TIMER, 47, 0);
}


LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hDC;
    static int w, h;
    static HDC hMemDC;
    static HBITMAP hBm;
    SYSTEMTIME st;
    PAINTSTRUCT ps;

    switch (Msg)
    {
    case WM_LBUTTONDOWN:
       // GLB_IsPause = !GLB_IsPause;
        return 0;
    case WM_LBUTTONUP:
       //GLB_IsPause = !GLB_IsPause;
        return 0;
    case WM_CREATE:
      EV5_RndInit(hWnd);
      SetTimer(hWnd, 47, 2, NULL);
      return 0;
    case WM_SIZE:
      EV5_RndResize(LOWORD(lParam), HIWORD(lParam));
      SendMessage(hWnd, WM_TIMER, 47, 0);
      return 0;
    case WM_CLOSE:
    if (MessageBox(NULL, "Do you really want to close?", "CLOSING", MB_YESNO) == IDYES)
      SendMessage(hWnd, WM_DESTROY, wParam, lParam);
    return 0;

    case WM_TIMER:
      EV5_RndStart();
      /*DRAW*/
      EV5_RndEnd();
      hDC = GetDC(hWnd);  /*    -- или -- InvalidateRect(hWnd, NULL, FALSE);*/
      EV5_RndCopyFrame(hDC);
      ReleaseDC(hWnd, hDC);
      return 0;
    case WM_ERASEBKGND:
      return 1;
    case WM_PAINT:
      hDC = BeginPaint(hWnd, &ps);
      EV5_RndCopyFrame(hDC);
      EndPaint(hWnd, &ps);
      return 0;
    case WM_DESTROY:
      EV5_RndClose();
      KillTimer(hWnd, 47);
      return 0;
      
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
/* END OF "MAIN.C" FILE */