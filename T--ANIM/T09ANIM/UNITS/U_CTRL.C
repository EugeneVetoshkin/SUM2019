/* FILE NAME   : U_Text.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */
#include <stdio.h>
#include "units.h"

/* Text unit type */
typedef struct
{
  EV5_UNIT_BASE_FIELDS;
} ev5UNIT_Text;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Text *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitInit( ev5UNIT_Text *Uni, ev5ANIM *Ani )
{
  HFONT hFnt, hOldFnt;

  hFnt = CreateFont(30, 0, 0, 0, FW_BOLD, TRUE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_SCRIPT, "Bookman Old Style");
  hOldFnt = SelectObject(EV5_Anim.hDC, hFnt);
  wglUseFontBitmaps(EV5_Anim.hDC, 0, 256, 102);
  hOldFnt = SelectObject(EV5_Anim.hDC, hOldFnt);
  DeleteObject(hFnt);
} /* End of 'EV5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Text *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitClose( ev5UNIT_Text *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Text *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitResponse( ev5UNIT_Text *Uni, ev5ANIM *Ani )
{
} /* End of 'EV5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Text *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitRender(ev5UNIT_Text *Uni, ev5ANIM *Ani )
{ 
  char Buf[100];
  int len;

  glLoadIdentity();
  glColor3d(1, 1, 1);
  glRasterPos2d(-0.9, 0.9);
  glListBase(102);
  len = sprintf(Buf, "FPS: %.3f, primitives: %i, triangles: %i", Ani->FPS, EV5_RndCounterPrims, EV5_triangles);
  glCallLists(len, GL_UNSIGNED_BYTE, Buf);
} /* End of 'EV5_UnitRender' function */

/* Text unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ev5UNIT *) pointer to created unit.
 */
ev5UNIT * EV5_UnitTextCreate( VOID )
{
  ev5UNIT *Uni;

  /* Memory allocation */
  if ((Uni = EV5_AnimUnitCreate(sizeof(ev5UNIT_Text))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EV5_UnitInit;
  Uni->Close = (VOID *)EV5_UnitClose;
  Uni->Response = (VOID *)EV5_UnitResponse;
  Uni->Render = (VOID *)EV5_UnitRender;
  return Uni;
} /* End of 'EV5_AnimUnitCreate' function */
