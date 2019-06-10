  /*PROGRAMMER: Vetoshkin Eugene
  IFK: EV5
  CLASS: 10-5
  DATE: 1.06.2019
  FILE: "RNDDATA.C"
  */

#include "..\DEF.H"
HWND EV5_hWndRnd;
HDC EV5_hDCRndFrame;
HBITMAP EV5_hBmRndFrame;
INT EV5_RndFrameW, EV5_RndFrameH;

DBL
  EV5_RndProjSize = 0.1,   /* Project plane fit square */
  EV5_RndProjDist = 0.1,    /* Distance to project plane from viewer (near) */
  EV5_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  EV5_RndMatrView, /* View coordinate system matrix */
  EV5_RndMatrProj, /* Projection coordinate system matrix */
  EV5_RndMatrVP;   /* Stored (View * Proj) matrix */
/// MatrView(Loc, At, Up1);
/* END OF "RNDDATA.C" FILE */