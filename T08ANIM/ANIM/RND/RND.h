#ifndef _RND_H_
#define _RND_H_
#include "DEF.H"


VOID EV5_RndInit(HWND hWnd);


typedef struct tagev5VERTEX
{
  VEC P;  /* Vertex position */
} ev5VERTEX;


typedef struct tagev5PRIM
{
  ev5VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh - by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} ev5PRIM;


extern DBL
EV5_RndProjSize,  /* Project plane fit square */
EV5_RndProjDist,  /* Distance to project plane from viewer (near) */
EV5_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
EV5_RndMatrView, /* View coordinate system matrix */
EV5_RndMatrProj, /* Projection coordinate system matrix */
EV5_RndMatrVP;   /* Stored (View * Proj) matrix */

extern HWND EV5_hWndRnd;
extern HDC EV5_hDCRndFrame;
extern HBITMAP EV5_hBmRndFrame;
extern INT EV5_RndFrameW, EV5_RndFrameH;

VOID EV5_RndProjSet(VOID);
VOID EV5_RndCamSet(VEC Loc, VEC At, VEC Up1);
VOID EV5_RndCopyFrame(HDC hDC);
VOID EV5_RndStart(VOID);
VOID EV5_RndResize(INT W, INT H);
VOID EV5_RndClose(VOID);
BOOL EV5_RndPrimLoad(ev5PRIM *Pr, CHAR *FileName);
VOID EV5_RndPrimDraw(ev5PRIM *Pr, MATR World);
VOID EV5_RndPrimFree(ev5PRIM *Pr);
BOOL EV5_RndPrimCreate(ev5PRIM *Pr, INT NoofV, INT NoofI);
#endif 