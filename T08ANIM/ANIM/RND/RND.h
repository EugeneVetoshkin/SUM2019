/* FILE NAME   : DEF.H
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#ifndef __RND_H_
#define __RND_H_

#include "../../def.h"

extern DBL
  EV5_RndProjSize,
  EV5_RndProjDist,
  EV5_RndProjFarClip;

extern MATR
  EV5_RndMatrView,
  EV5_RndMatrProj,
  EV5_RndMatrVP;

extern HWND EV5_hWndRnd;
extern HDC EV5_hDCRndFrame;
extern HBITMAP EV5_hBmRndFrame;
extern INT EV5_RndFrameW, EV5_RndFrameH;


VOID EV5_RndInit( HWND hWnd );
VOID EV5_RndClose( VOID );

VOID EV5_RndStart( VOID );
VOID EV5_RndEnd( VOID );

VOID EV5_RndCopyFrame( HDC hDC );
VOID EV5_RndResize( INT W, INT H );

VOID EV5_RndCamSet(VEC Loc, VEC At, VEC Up1);
VOID EV5_RndProjSet( VOID );

/*** Primitives ***/

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

BOOL EV5_RndPrimLoad( ev5PRIM *Pr, CHAR *FileName );
VOID EV5_RndPrimDraw( ev5PRIM *Pr, MATR World );
VOID EV5_RndPrimFree( ev5PRIM *Pr );
BOOL EV5_RndPrimCreate( ev5PRIM *Pr, INT NoofV, INT NoofI );

#endif
/*End of RND.H*/