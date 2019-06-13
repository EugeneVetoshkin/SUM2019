/* FILE NAME   : RNDBASE.H
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */


#include "..\anim.h"



VOID EV5_RndStart(VOID)
{
  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
VOID EV5_RndEnd(VOID)
{
  glFinish();
}

VOID EV5_RndCamSet(VEC Loc, VEC At, VEC Up1)
{
  EV5_RndMatrView = MatrView(Loc, At, Up1);
  EV5_RndMatrVP = MatrMulMatr(EV5_RndMatrView, EV5_RndMatrProj);
}

VOID EV5_RndInit(HWND hWnd)
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* Store window and context handles */
  EV5_Anim.hWnd = hWnd;
  EV5_Anim.hDC = GetDC(EV5_Anim.hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(EV5_Anim.hDC, &pfd);
  DescribePixelFormat(EV5_Anim.hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(EV5_Anim.hDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  EV5_Anim.hRC = wglCreateContext(EV5_Anim.hDC);
  wglMakeCurrent(EV5_Anim.hDC, EV5_Anim.hRC);

  /* Initialize GLEW library */
  if (glewInit() != GLEW_OK)
    return;
  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    return;

  /* Set default render parameters */
  glClearColor(0.30, 0.50, 0.8, 1);
  glEnable(GL_DEPTH_TEST);
}

VOID EV5_RndClose(VOID)
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(EV5_Anim.hRC);
  ReleaseDC(EV5_Anim.hWnd, EV5_Anim.hDC);
}

VOID EV5_RndCopyFrame( VOID )
{
  SwapBuffers( EV5_Anim.hDC );
}


VOID EV5_RndResize(INT W, INT H)
{
  glViewport(0, 0, W, H);

}
VOID EV5_RndProjSet(VOID)
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = EV5_RndProjSize / 2;
  if (EV5_Anim.W >= EV5_Anim.H)
    ratio_x *= (DBL)EV5_Anim.W / EV5_Anim.H;
  else
    ratio_y *= (DBL)EV5_Anim.H / EV5_Anim.W;
  EV5_RndMatrProj = MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
    EV5_RndProjDist, EV5_RndProjFarClip);
  EV5_RndMatrVP = MatrMulMatr(EV5_RndMatrView, EV5_RndMatrProj);
}

/*End of RNDBASE.C*/