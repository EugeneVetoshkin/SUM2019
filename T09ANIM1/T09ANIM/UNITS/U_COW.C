/* FILE NAME   : U_Cow.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include "units.h"

/* Cow unit type */
typedef struct
{
  EV5_UNIT_BASE_FIELDS;
  ev5PRIM Cow;
} ev5UNIT_Cow;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Cow *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitInit( ev5UNIT_Cow *Uni, ev5ANIM *Ani )
{
  EV5_RndPrimLoad(&Uni->Cow, "cow.object");
} /* End of 'EV5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Cow *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitClose( ev5UNIT_Cow *Uni, ev5ANIM *Ani )
{
  EV5_RndPrimFree(&Uni->Cow);
} /* End of 'EV5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Cow *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitResponse( ev5UNIT_Cow *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Cow *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitRender( ev5UNIT_Cow *Uni, ev5ANIM *Ani )
{
  MATR m;
  
    glColor3d(255 / 255.0 , 153 / 255.0 , 51 / 255.0);
    m = MatrMulMatr3(MatrScale(VecSet(1, 1, 1)),
                     MatrMulMatr( MatrRotateZ( 45.0 * 2 * -EV5_Anim.JZ), MatrRotateY( 90.0 * 2 * -EV5_Anim.JR)),
                     MatrTranslate(VecSet(40 * -EV5_Anim.JY, 0, 40 * EV5_Anim.JX)));

   EV5_RndPrimDraw(&Uni->Cow, m);
} /* End of 'EV5_UnitRender' function */

/* Cow unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ev5UNIT *) pointer to created unit.
 */
ev5UNIT * EV5_UnitCowCreate( VOID )
{
  ev5UNIT *Uni;

  /* Memory allocation */
  if ((Uni = EV5_AnimUnitCreate(sizeof(ev5UNIT_Cow))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EV5_UnitInit;
  Uni->Close = (VOID *)EV5_UnitClose;
  Uni->Response = (VOID *)EV5_UnitResponse;
  Uni->Render = (VOID *)EV5_UnitRender;
  return Uni;
} /* End of 'EV5_AnimUnitCreate' function */
