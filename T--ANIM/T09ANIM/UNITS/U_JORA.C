/* FILE NAME   : U_Giorno_Giovanna.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include "units.h"

/* Giorno_Giovanna unit type */
typedef struct
{
  EV5_UNIT_BASE_FIELDS;
  ev5PRIM Giorno_Giovanna;
} ev5UNIT_Giorno_Giovanna;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Giorno_Giovanna *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitInit( ev5UNIT_Giorno_Giovanna *Uni, ev5ANIM *Ani )
{
  EV5_AnimJoystickInit();
  EV5_RndPrimLoad(&Uni->Giorno_Giovanna, "Giorno_Giovanna.obj");
} /* End of 'EV5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Giorno_Giovanna *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitClose( ev5UNIT_Giorno_Giovanna *Uni, ev5ANIM *Ani )
{
  EV5_RndPrimFree(&Uni->Giorno_Giovanna);
} /* End of 'EV5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Giorno_Giovanna *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitResponse( ev5UNIT_Giorno_Giovanna *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Giorno_Giovanna *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitRender( ev5UNIT_Giorno_Giovanna *Uni, ev5ANIM *Ani )
{
  MATR m;
  EV5_AnimJoystickResponse();

  m = MatrMulMatr3(MatrScale(VecSet(0.3, 0.3, 0.3)),
                   MatrTranslate(VecSet(8 * EV5_Anim.JX, -40 -8 * EV5_Anim.JY, -8 * EV5_Anim.JZ)),
                   MatrRotateY(-90 + 90 * EV5_Anim.JR));
  EV5_RndPrimDraw(&Uni->Giorno_Giovanna, m);
} /* End of 'EV5_UnitRender' function */

/* Giorno_Giovanna unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ev5UNIT *) pointer to created unit.
 */
ev5UNIT * EV5_UnitGiorno_GiovannaCreate( VOID )
{
  ev5UNIT *Uni;

  /* Memory allocation */
  if ((Uni = EV5_AnimUnitCreate(sizeof(ev5UNIT_Giorno_Giovanna))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EV5_UnitInit;
  Uni->Close = (VOID *)EV5_UnitClose;
  Uni->Response = (VOID *)EV5_UnitResponse;
  Uni->Render = (VOID *)EV5_UnitRender;
  return Uni;
} /* End of 'EV5_AnimUnitCreate' function */
