/* FILE NAME   : IMPUT.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include "anim.h"
#define EV5_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)


VOID EV5_AnimJoystickInit( VOID )
{
  EV5_AnimJoystickResponse();
}/*EV5_AnimJoystickInit func*/

VOID EV5_AnimJoystickResponse( VOID )
{
  INT i;

  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          EV5_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          EV5_Anim.JButClick[i] = EV5_Anim.JBut[i] && !EV5_Anim.JButOld[i];
          EV5_Anim.JButOld[i] = EV5_Anim.JBut[i];
        }

        /* Axes */
        EV5_Anim.JX = EV5_GET_JOYSTIC_AXIS(X);
        EV5_Anim.JY = EV5_GET_JOYSTIC_AXIS(Y);
        EV5_Anim.JZ = EV5_GET_JOYSTIC_AXIS(Z);
        EV5_Anim.JR = EV5_GET_JOYSTIC_AXIS(R);
        

        /* Point of view */
        EV5_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
}   /*EV5_AnimJoystickResponse func*/