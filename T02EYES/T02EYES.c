/*Vetoshkin Eugeni 10-5 2018*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>



#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

VOID DrawEye(HDC hDC, int x, int y, int r1, int r2, int mx, int my )
{
  double t;
  int dx, dy;

  t = (r1 - r2) / (sqrt((mx - x) * (mx - x) + (my - y)*(my - y))); 
  dx = (int)((mx - x) * t);
  dy = (int)((my - y) * t);


  SelectObject(hDC, GetStockObject(WHITE_BRUSH));
  Ellipse(hDC, x - r1, y - r1, x + r1, y + r1);
 
  if ( sqrt((mx - x) * (mx - x) + (my - y)*(my - y)) + r2  < r1 )
  {
    SelectObject(hDC, GetStockObject(BLACK_BRUSH));
    Ellipse(hDC, mx - r2, my - r2, mx + r2, my + r2);
  }
  else
  {
    SelectObject(hDC, GetStockObject(BLACK_BRUSH));
    Ellipse(hDC, x + dx - r2, y + dy - r2, x + dx + r2, y + dy + r2);
  }
}

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
  POINT pt;
  double t;
  static HDC hMemDC;
  static INT h , w;
  static HBITMAP hBm;
  int i;
   

  switch(Msg)
  {
    case WM_CREATE:
     
      SetTimer(hWnd, 1, 30, NULL);
      hDC = GetDC(hWnd);
      hMemDC = CreateCompatibleDC(hDC);
      ReleaseDC(hWnd, hDC);
      return 0;
    
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

    case WM_KEYDOWN:
      if(wParam == VK_ESCAPE)
        DestroyWindow(hWnd);
      return 0;
      
    case WM_TIMER:
      hDC = GetDC(hWnd);
      srand(1000);
      t = clock() / 1500.0;
     
      /*background*/
      SelectObject(hMemDC, hBm);
      SelectObject(hMemDC, GetStockObject(GRAY_BRUSH));
      Rectangle(hMemDC, 0, 0, w, h);
      /*coursor pos*/
      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);
      /*Drawing eyes */
      for(i = 0; i < 1000; i++)
      {
        DrawEye(hMemDC, rand() % 1920 + sin(t + i) * 200 + i, rand() % 1080 + sin((t + i) * 2 ) * 200, 50, 15,  pt.x, pt.y);
      } 
      BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
      ReleaseDC(hWnd, hDC);
      return 0;  
    
    case WM_DESTROY:
      MessageBox(NULL, "You have closed your programm and now you have no choise", "CLOSING", MB_OK);
      DeleteObject(hBm);
      DeleteDC(hMemDC);
      KillTimer(hWnd, 1);
      PostQuitMessage(0);
      return 0;

  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

