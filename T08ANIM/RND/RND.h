 /* FILE NAME  : RND.H
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Eugene A. Vetoshkin
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */
#ifndef __RND_H_
#define __RND_H_

#include "..\DEF.H"
VOID EV5_RndInit( HWND hWnd );
VOID EV5_RndClose( VOID );
VOID EV5_RndResize( INT W, INT H );
VOID EV5_RndStart( VOID );
VOID EV5_RndEnd( VOID );
VOID EV5_RndCopyFrame( HDC hDC );
VOID EV5_RndProjSet( VOID );
VOID EV5_RndCamSet( VEC Loc, VEC At, VEC Up1 );

extern DBL
  EV5_RndProjSize,   
  EV5_RndProjDist,   
  EV5_RndProjFarClip;

extern HWND EV5_hWndRnd;
extern HDC EV5_hDCRndFrame;
extern HBITMAP EV5_hBmRndFrame;
extern INT EV5_RndFrameW, EV5_RndFrameH;
 
extern MATR
  EV5_RndMatrView, /* View coordinate system matrix */
  EV5_RndMatrProj, /* Projection coordinate system matrix */
  EV5_RndMatrVP;   /* Stored (View * Proj) matrix */
///---------------------------------

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

 BOOL Create( ev5PRIM *Pr, INT NoofV, INT NoofI );
  VOID Free( ev5PRIM *Pr );
  VOID Draw( ev5PRIM *Pr, MATR World );
  BOOL Load( ev5PRIM *Pr, CHAR *FileName );

#endif /* __RND_H_ */
/* END OF "RND.h" FILE */