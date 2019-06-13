/* FILE NAME   : DATA.C
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Vetoshkin Eugene.
* LAST UPDATE : 10.06.2019.
* NOTE        : Module prefix 'EV5'.
*/

#include "../../DEF.H"

HWND EV5_hWndRnd;
HDC EV5_hDCRndFrame;
HBITMAP EV5_hBmRndFrame;
INT EV5_RndFrameW, EV5_RndFrameH;

DBL
EV5_RndProjSize = 0.1,  /* Project plane fit square */
EV5_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
EV5_RndProjFarClip = 100;  /* Distance to project far clip plane (far) */

MATR
EV5_RndMatrView, /* View coordinate system matrix */
EV5_RndMatrProj, /* Projection coordinate system matrix */
EV5_RndMatrVP;   /* Stored (View * Proj) matrix */

/*End of RNDDATA.C*/