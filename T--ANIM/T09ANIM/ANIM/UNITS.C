/*  *FILENAME: UNITS.c 
    *PROGRAMMER: Vetoshkin Eugene
    *DATE: 11.06.2019 
    *PURPOSE: project*/

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitInit( ev5UNIT *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitClose( ev5UNIT *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitClose' function */
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitResponse( ev5UNIT *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitRender( ev5UNIT *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitRender' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ev5UNIT *) pointer to created unit.
 */
ev5UNIT * EV5_AnimUnitCreate( INT Size )
{
  ev5UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(ev5UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = EV5_UnitInit;
  Uni->Close = EV5_UnitClose;
  Uni->Response = EV5_UnitResponse;
  Uni->Render = EV5_UnitRender;
  return Uni;
} /* End of 'EV5_AnimUnitCreate' function */

/* End of "UNITS.c" function */