#include <stdlib.h>
#include <windows.h>
#include "DEF.H"
#include "..\MTH\MTH.h"
#include "RND.H"

VOID EV5_RndInit(HWND hWnd)
{
  HDC hDC;
  SetTimer(hWnd, 47, 1000, NULL);
  hDC = GetDC(hWnd);
  EV5_hDCRndFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
}
VOID EV5_RndClose(VOID)
{
  DeleteObject(EV5_hBmRndFrame);
  DeleteDC(EV5_hDCRndFrame);
  KillTimer(EV5_hWndRnd, 47);
  PostQuitMessage(0);
  return 0;

}
VOID EV5_RndResize(INT W, INT H)
{
  HDC hDC;

  if (EV5_hBmRndFrame != NULL)
    DeleteObject(EV5_hBmRndFrame);

  hDC = GetDC(EV5_hWndRnd);
  EV5_hBmRndFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(EV5_hWndRnd, hDC);
  SelectObject(EV5_hDCRndFrame, EV5_hBmRndFrame);

  EV5_RndFrameW = W;
  EV5_RndFrameH = H;
  EV5_RndProjSet();
}

VOID EV5_RndStart(VOID)
{
  SelectObject(EV5_hDCRndFrame, EV5_hBmRndFrame);
  SelectObject(EV5_hDCRndFrame, GetStockObject(WHITE_BRUSH));
  Rectangle(EV5_hDCRndFrame, 0, 0, EV5_RndFrameW, EV5_RndFrameW);


  SelectObject(EV5_hDCRndFrame, GetStockObject(NULL_BRUSH));
  SelectObject(EV5_hDCRndFrame, GetStockObject(BLACK_PEN));
}

/*VOID EV5_RndEnd( VOID )
{

}       */

VOID EV5_RndCopyFrame(HDC hDC)
{
  BitBlt(hDC, 0, 0, EV5_RndFrameW, EV5_RndFrameH,
    EV5_hDCRndFrame, 0, 0, SRCCOPY);
}

VOID EV5_RndProjSet(VOID)
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = EV5_RndProjSize / 2;
  if (EV5_RndFrameW >= EV5_RndFrameH)
    ratio_x *= (DBL)EV5_RndFrameW / EV5_RndFrameH;
  else
    ratio_y *= (DBL)EV5_RndFrameH / EV5_RndFrameW;
  EV5_RndMatrProj = MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
    EV5_RndProjDist, EV5_RndProjFarClip);
  EV5_RndMatrVP = MatrMulMatr(EV5_RndMatrView, EV5_RndMatrProj);
}

VOID EV5_RndCamSet(VEC Loc, VEC At, VEC Up1)
{
  EV5_RndMatrView = MatrView(Loc, At, Up1);
  EV5_RndMatrVP = MatrMulMatr(EV5_RndMatrView, EV5_RndMatrProj);
}