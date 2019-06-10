  /*PROGRAMMER: Vetoshkin Eugene
  IFK: EV5
  CLASS: 10-5
  DATE: 1.06.2019
  FILE: "MAIN.C"
  */
#include "..\DEF.H"
///#include "RNDDATA.c"
#include "RND.h"
///#include "RNDDATA.C"




VOID EV5_RndInit( HWND hWnd )
{

}
VOID EV5_RndClose( VOID )
{

}
VOID EV5_RndResize( INT W, INT H )
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

VOID EV5_RndStart( VOID )
{

}
VOID EV5_RndEnd( VOID )
{

}

VOID EV5_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, EV5_RndFrameW, EV5_RndFrameH,
    EV5_hDCRndFrame, 0, 0, SRCCOPY);
}





VOID EV5_RndProjSet( VOID )
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

VOID EV5_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  EV5_RndMatrView = MatrView(Loc, At, Up1);
  EV5_RndMatrVP = MatrMulMatr(EV5_RndMatrView, EV5_RndMatrProj);
}

/*
VOID ...Draw...( ... , MATR World )
{
  . . .
  MATR M = MatrMulMatr(World, EV5_RndMatrVP);
  POINT *Proj;
  . . .
  if ((Proj = malloc(sizeof(POINT) * Prim.NumOfV)) == NULL)
    return;
  . . .
    VEC p = VecMulMatr(Prim.V[i], M);

    Proj[i].x = (p.X + 1) * EV5_RndFrameW / 2;
    Proj[i].y = (-p.Y + 1) * EV5_RndFrameH / 2;
  . . .
  free(Proj);
}*/

/*
-------------
V VectorTransform(V, M) -> (x',y',z',0) =(x,y,z,0) * M --> (x',y',z')
V PointTransform(V, M)  -> (x',y',z',1) =(x,y,z,1) * M --> (x',y',z')
V VecMulMatr(V, M)      -> (x',y',z',w')=(x,y,z,1) * M --> (x'/w',y'/w',z'/w')
-------------
*/


/* END OF "MTH.H" FILE */