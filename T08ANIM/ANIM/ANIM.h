/*  *FILENAME: ANIM.h 
    *PROGRAMMER: Vetoshkin Eugene
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#ifndef __ANIM_H_
#define __ANIM_H_
#include "..\DEF.h"
#include <time.h>

#define EV5_MAX_UNITS 3000
//#define UNIT_BASE_FIELDS \
//  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
//  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
//  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
//  VOID (*Render)( UNIT *Uni, ANIM *Ani )


typedef struct tagEV5_UNIT EV5_UNIT;
typedef struct tagEV5_ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;
  EV5_UNIT *Units[EV5_MAX_UNITS];
  INT NumOfUnits;
} EV5_ANIM;

typedef struct tagEV5_UNIT
{
  VOID (*Init)( EV5_UNIT *Uni, EV5_ANIM *Ani );     
  VOID (*Close)( EV5_UNIT *Uni, EV5_ANIM *Ani );     
  VOID (*Response)( EV5_UNIT *Uni, EV5_ANIM *Ani );  
  VOID (*Render)( EV5_UNIT *Uni, EV5_ANIM *Ani );
};

DBL
  GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  Time, DeltaTime,             /* Time with pause and interframe interval */
  FPS;                         /* Frames per second value */
BOOL 
  IsPause;                     /* Pause flag */

///EV5_ANIM EV5_Anim;

#endif
/* End of "ANIM.h" function */