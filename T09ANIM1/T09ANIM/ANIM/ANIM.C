/*  *FILENAME: ANIM.c 
    *PROGRAMMER: Vetoshkin Eugene    *DATE: 11.06.2019 
    *PURPOSE: project*/

#include "ANIM.h"

ev5ANIM EV5_Anim;

VOID EV5_AnimClose( VOID ) 
{
  INT i;

  for (i = 0; i < EV5_Anim.NumOfUnits; i++)
  {
    EV5_Anim.Units[i]->Close(EV5_Anim.Units[i], &EV5_Anim);
    free(EV5_Anim.Units[i]);
    EV5_Anim.Units[i] = NULL;
  }
  EV5_Anim.NumOfUnits = 0;
  EV5_RndClose();
}

VOID EV5_AnimRender( VOID )
{
  INT i;

  EV5_TimerResponse();
  EV5_AnimJoystickResponse();

/*  EV5_RndShdDelete();*/
  

  for (i = 0; i < EV5_Anim.NumOfUnits; i++)
    EV5_Anim.Units[i]->Response(EV5_Anim.Units[i], &EV5_Anim);

  EV5_RndStart();
  for (i = 0; i < EV5_Anim.NumOfUnits; i++)
    EV5_Anim.Units[i]->Render (EV5_Anim.Units[i], &EV5_Anim);
  EV5_RndEnd();
}

VOID EV5_AnimUnitAdd(ev5UNIT *Uni)
{
  if (EV5_Anim.NumOfUnits < EV5_MAX_UNITS)
    EV5_Anim.Units[EV5_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &EV5_Anim); 
}

VOID EV5_AnimCopyFrame(HDC hDC)
{
  EV5_RndCopyFrame();
}

VOID EV5_AnimEnd( VOID )
{

}

VOID EV5_AnimResize(INT w, INT h)
{
  EV5_RndResize(w, h);
}

VOID EV5_AnimInit (HWND hWnd)
{
  EV5_TimerInit();
  EV5_AnimJoystickInit();
  EV5_RndInit(hWnd);
}


/* End of "ANIM.c" function */