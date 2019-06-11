#include "DEF.h"
#include "RND.H"


DBL
EV5_RndProjSize = 0.1,  /* Project plane fit square */
EV5_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
EV5_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
EV5_RndMatrView, /* View coordinate system matrix */
EV5_RndMatrProj, /* Projection coordinate system matrix */
EV5_RndMatrVP;   /* Stored (View * Proj) matrix */

HWND EV5_hWndRnd;
HDC EV5_hDCRndFrame;
HBITMAP EV5_hBmRndFrame;
INT EV5_RndFrameW, EV5_RndFrameH;