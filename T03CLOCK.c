 /*Vetoshkin Eugeni 10-5 2018*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define PI 3.14159265358979323846


#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);



INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
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

  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
   
  }
  return msg.wParam; 
} 

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{

  HDC hDC;
 // double t;
  static HDC hMemDC, hMemDCClock;
  static INT h , w;
  static HBITMAP hBm, hBmClock;
  BITMAP bm;
  SYSTEMTIME st;
  HPEN hPenSeconds, hPenMinutes, hPenHours;
  
  POINT pnts1[4]; 
  POINT pnts2[4]; 
  POINT pnts3[4]; 

  switch(Msg)
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
        
      return 0;
    /**********************************************************************************/
    case WM_KEYDOWN:
      if(wParam == VK_ESCAPE || VK_EXECUTE)
        DestroyWindow(hWnd);
      return 0;
    /**********************************************************************************/  
    case WM_TIMER:
      GetLocalTime(&st);
       
      hDC = GetDC(hWnd);
      hPenSeconds = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
      hPenMinutes = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
      hPenHours = CreatePen(PS_SOLID, 15, RGB(0, 0, 0));
            
      Rectangle(hMemDC, 0, 0, w, h);
      GetObject(hBmClock, sizeof(bm), &bm);
       
      
      BitBlt(hMemDC, (w - bm.bmWidth) / 2 , (h - bm.bmHeight) / 2, bm.bmHeight, bm.bmWidth, hMemDCClock, 0, 0, SRCCOPY );
      
    pnts1[0].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) + (PI / 2)) * 10 + sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) - (PI / 2)) * 0 + (w / 2);
    pnts1[1].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) + (PI / 2)) * 0 + sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) - (PI / 2)) * 10 + (w / 2);
    pnts1[2].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) - (PI / 2)) * (bm.bmWidth / 2.5) + w / 2;
    pnts1[3].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) + (PI / 2)) * 0 + sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) - (PI / 2)) * -10 + (w / 2);
  
    pnts1[0].y = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) + (PI / 2)) * 0 - sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) - (PI / 2)) * 10 + (h / 2);
    pnts1[1].y = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) + (PI / 2)) * 10 - sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) - (PI / 2)) * 0 + (h / 2);
    pnts1[2].y = sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) - (PI / 2)) * (bm.bmHeight / 2.5) + h / 2;
    pnts1[3].y = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) + (PI / 2)) * -10 - sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0) * 1 ) - (PI / 2)) * 0 + (h / 2);                                        


    pnts2[0].x = cos((((2 * PI) / 60) * (st.wMinute  + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) + (PI / 2)) * 15 + sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) - (PI / 2)) * 0 + (w / 2);
    pnts2[1].x = cos((((2 * PI) / 60) * (st.wMinute  + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) + (PI / 2)) * 0 + sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) - (PI / 2)) * 15 + (w / 2);
    pnts2[2].x = cos((((2 * PI) / 60) * (st.wMinute  + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) - (PI / 2)) * (bm.bmWidth / 2.7) + w / 2;
    pnts2[3].x = cos((((2 * PI) / 60) * (st.wMinute  + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) + (PI / 2)) * 0 + sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) - (PI / 2)) * -15 + (w / 2);
  
    pnts2[0].y = cos((((2 * PI) / 60) * (st.wMinute  + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) + (PI / 2)) * 0 - sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) - (PI / 2)) * 15 + (h / 2);
    pnts2[1].y = cos((((2 * PI) / 60) * (st.wMinute  + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) + (PI / 2)) * 15 - sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) - (PI / 2)) * 0 + (h / 2);
    pnts2[2].y = sin((((2 * PI) / 60) * (st.wMinute  + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) - (PI / 2)) * (bm.bmHeight / 2.7) + h / 2;
    pnts2[3].y = cos((((2 * PI) / 60) * (st.wMinute  + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) + (PI / 2)) * -15 - sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) * 1 ) - (PI / 2)) * 0 + (h / 2);                                        


    pnts3[0].x = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) + (PI / 2)) * 20 + sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) - (PI / 2)) * 0 + (w / 2);
    pnts3[1].x = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) + (PI / 2)) * 0 + sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) - (PI / 2)) * 20 + (w / 2);
    pnts3[2].x = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) - (PI / 2)) * (bm.bmWidth / 3) + w / 2;
    pnts3[3].x = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) + (PI / 2)) * 0 + sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) - (PI / 2)) * -20 + (w / 2);
  
    pnts3[0].y = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) + (PI / 2)) * 0 - sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) - (PI / 2)) * 20 + (h / 2);
    pnts3[1].y = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) + (PI / 2)) * 20 - sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) - (PI / 2)) * 0 + (h / 2);
    pnts3[2].y = sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) - (PI / 2)) * (bm.bmHeight / 3) + h / 2;
    pnts3[3].y = cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) + (PI / 2)) * -20 - sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0 + st.wSecond / 1440.0 + st.wMilliseconds / 1440000.0) * 1 ) - (PI / 2)) * 0 + (h / 2);                                        

    
    Polygon(hMemDC, pnts1, 4);
    Polygon(hMemDC, pnts2, 4);
    Polygon(hMemDC, pnts3, 4);


      BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
      DeleteObject(hPenSeconds);
      DeleteObject(hPenMinutes);
      DeleteObject(hPenHours);
      ReleaseDC(hWnd, hDC);
      return 0;  
    /**********************************************************************************/
    case WM_DESTROY:
      MessageBox(NULL, "You have closed your programm and now you have no choise", "CLOSING", MB_OK);
      DeleteObject(hBm);
      DeleteDC(hMemDC);
      DeleteDC(hMemDCClock);
      KillTimer(hWnd, 1);
      PostQuitMessage(0);
      return 0;

  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

