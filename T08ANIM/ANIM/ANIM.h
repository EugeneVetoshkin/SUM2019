/* FILENAME: ANIM.h 
 * PROGRAMMER: Vetoshkin Eugene
 * DATE: 11.06.2019 
 * PURPOSE: project
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "RND/RND.h"

#define EV5_MAX_UNITS 3000

#define EV5_UNIT_BASE_FIELDS \
  VOID (*Init)( ev5UNIT *Uni, ev5ANIM *Ani );      \
  VOID (*Close)( ev5UNIT *Uni, ev5ANIM *Ani );     \
  VOID (*Response)( ev5UNIT *Uni, ev5ANIM *Ani );  \
  VOID (*Render)( ev5UNIT *Uni, ev5ANIM *Ani )


typedef struct tagev5UNIT ev5UNIT;
typedef struct tagev5ANIM
{ 
  HWND hWnd;
  HDC hDC;
  INT W, H;
  ev5UNIT *Units[EV5_MAX_UNITS];
  INT NumOfUnits;

  /* Timer data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL 
    IsPause;                     /* Pause flag */
  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                       /* Joystick axes */

} ev5ANIM;

typedef struct tagev5UNIT
{
  VOID (*Init)( ev5UNIT *Uni, ev5ANIM *Ani );     
  VOID (*Close)( ev5UNIT *Uni, ev5ANIM *Ani );     
  VOID (*Response)( ev5UNIT *Uni, ev5ANIM *Ani );  
  VOID (*Render)( ev5UNIT *Uni, ev5ANIM *Ani );
};

extern ev5ANIM EV5_Anim;

VOID EV5_AnimInit( HWND hWnd );
VOID EV5_AnimClose( VOID );

VOID EV5_AnimResize(INT w, INT h);

VOID EV5_AnimRender( VOID );
VOID EV5_AnimCopyFrame(HDC hDC);
VOID EV5_AnimUnitAdd(ev5UNIT *Uni);

ev5UNIT * EV5_AnimUnitCreate( INT size);

VOID EV5_TimerInit( VOID );
VOID EV5_TimerResponse( VOID );

VOID EV5_AnimJoystickInit( VOID );
VOID EV5_AnimJoystickResponse( VOID );

#endif
/* End of "ANIM.h" function */