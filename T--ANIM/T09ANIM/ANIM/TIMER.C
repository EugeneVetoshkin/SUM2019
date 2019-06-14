/* FILE NAME   : TIMER.H
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Vetoshkin Eugene
* LAST UPDATE : 11.06.2019.
* NOTE        : Module prefix 'EV5'.
*/
#include "..\DEF.h"
#include "ANIM.h"

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID EV5_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  EV5_Anim.IsPause = FALSE;
  EV5_Anim.FPS = 30.0;
  PauseTime = 0;
}/*EV5_TimerInit func*/

VOID EV5_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  EV5_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  EV5_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (EV5_Anim.IsPause)
  {
    EV5_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    EV5_Anim.DeltaTime = EV5_Anim.GlobalDeltaTime;
    EV5_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    EV5_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /*EV5_TimerResponse func*/