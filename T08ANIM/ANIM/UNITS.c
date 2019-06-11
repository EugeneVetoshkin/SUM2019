
#include "..\DEF.h"
#include "ANIM.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       EV5_UNIT *Uni;
 *   - animation context:
 *       EV5_ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitInit( EV5_UNIT *Uni, EV5_ANIM *Ani )
{
} /* End of 'EV5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       EV5_UNIT *Uni;
 *   - animation context:
 *       EV5_ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitClose( EV5_UNIT *Uni, EV5_ANIM *Ani )
{
} /* End of 'EV5_UnitClose' function */
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       EV5_UNIT *Uni;
 *   - animation context:
 *       EV5_ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitResponse( EV5_UNIT *Uni, EV5_ANIM *Ani )
{
} /* End of 'EV5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       EV5_UNIT *Uni;
 *   - animation context:
 *       EV5_ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitRender( EV5_UNIT *Uni, EV5_ANIM *Ani )
{
} /* End of 'EV5_UnitRender' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (EV5_UNIT *) pointer to created unit.
 */
EV5_UNIT * EV5_AnimUnitCreate( INT Size )
{
  EV5_UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(EV5_UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = EV5_UnitInit;
  Uni->Close = EV5_UnitClose;
  Uni->Response = EV5_UnitResponse;
  Uni->Render = EV5_UnitRender;
  return Uni;
} /* End of 'EV5_AnimUnitCreate' function */



/*   
static VOID EV5_UnitInit( IK3UNIT_BALL *Uni, IK3ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
} 
static VOID EV5_UnitResponse( IK3UNIT_BALL *Uni, IK3ANIM *Ani );
{
  Uni->Pos += Ani->DeltaTime * 2.4;
}  */


/* End of "UNITS.c" function */