/* FILE NAME   : U_City.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include "units.h"

/* City unit type */
typedef struct
{
  EV5_UNIT_BASE_FIELDS;
  ev5PRIM City;
} ev5UNIT_City;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_City *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitInit( ev5UNIT_City *Uni, ev5ANIM *Ani )
{
  EV5_AnimJoystickInit();
  EV5_RndPrimLoad(&Uni->City, "low poly buildings.obj");
} /* End of 'EV5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_City *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitClose( ev5UNIT_City *Uni, ev5ANIM *Ani )
{
  EV5_RndPrimFree(&Uni->City);
} /* End of 'EV5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_City *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitResponse( ev5UNIT_City *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_City *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitRender( ev5UNIT_City *Uni, ev5ANIM *Ani )
{
  MATR m;
  EV5_AnimJoystickResponse();

  m = MatrMulMatr3(MatrScale(VecSet(0.1, 0.1, 0.1)),
                   MatrTranslate(VecSet(10, - 40, -10)),
                   MatrRotateY(180));

  EV5_RndPrimDraw(&Uni->City, m);
} /* End of 'EV5_UnitRender' function */

/* City unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ev5UNIT *) pointer to created unit.
 */
ev5UNIT * EV5_UnitCityCreate( VOID )
{
  ev5UNIT *Uni;

  /* Memory allocation */
  if ((Uni = EV5_AnimUnitCreate(sizeof(ev5UNIT_City))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EV5_UnitInit;
  Uni->Close = (VOID *)EV5_UnitClose;
  Uni->Response = (VOID *)EV5_UnitResponse;
  Uni->Render = (VOID *)EV5_UnitRender;
  return Uni;
} /* End of 'EV5_AnimUnitCreate' function */
