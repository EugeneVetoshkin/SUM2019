/* FILE NAME   : RNDMTL.C
 * PURPOSE     : WinAPI animation system.
 *               Rendering system implementation module.
 *               Resourses functions.
 *               Material support.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 12.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include <string.h>

#include "rnd.h"

/* Material stock */
ev5MATERIAL EV5_RndMaterials[EV5_MAX_MATERIALS]; /* Array of materials */
INT EV5_RndMaterialsSize;                        /* Materials array store size */

/* Materials support initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndMtlInit( VOID )
{
  ev5MATERIAL mtl =
  {
    "Default",
    0,
    {0.1, 0.1, 0.1}, {0.9, 0.9, 0.9}, {0, 0, 0},
    30,
    1,
    {-1, -1, -1, -1, -1, -1, -1, -1}
  };

  memset(EV5_RndMaterials, 0, sizeof(EV5_RndMaterials));
  EV5_RndMaterialsSize = 0;
  EV5_RndMtlAdd(&mtl);
} /* End of 'EV5_RndMtlInit' function */

/* Add new material to stock function.
 * ARGUMENTS:
 *   - material description structure pointer:
 *       ev5MATERIAL *Mtl;
 * RETURNS:
 *   (INT) added material stock index.
 */
INT EV5_RndMtlAdd( ev5MATERIAL *Mtl )
{
  /*
  INT i;

  for (i = 0; i < EV5_RndMaterialsSize; i++)
    if (strcmp(EV5_RndMaterials[i].Name, Mtl->Name) == 0)
    {
      EV5_RndMaterials[i] = *Mtl;
      return i;
    }
  */
  if (EV5_RndMaterialsSize >= EV5_MAX_MATERIALS)
    return 0;
  EV5_RndMaterials[EV5_RndMaterialsSize] = *Mtl;
  return EV5_RndMaterialsSize++;
} /* End of 'EV5_RndMtlAdd' function */

/* Add new material to stock function.
 * ARGUMENTS:
 *   - material table number:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) applied material shader program Id.
 */
INT EV5_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  ev5MATERIAL *mtl;

  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= EV5_RndMaterialsSize)
    MtlNo = 0;
  mtl = &EV5_RndMaterials[MtlNo];

  /* Set program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= EV5_RndShadersSize)
    prg = 0;
  else
    prg = EV5_RndShaders[prg].ProgId;

  glUseProgram(prg);
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Textures handle */
  for (i = 0; i < 8; i++)
  {
    CHAR is[18] = "IsTexture0";

    /* Set texture presence flag */
    is[9] = '0' + i;
    if ((loc = glGetUniformLocation(prg, is)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);

    glActiveTexture(GL_TEXTURE0 + i);
    if (mtl->Tex[i] == -1)
      glBindTexture(GL_TEXTURE_2D, 0);
    else
    {
      INT tn = mtl->Tex[i];

      if (tn < 0 || tn >= EV5_RndTexturesSize)
        tn = 0;
      else
        tn = EV5_RndTextures[tn].TexId;

      glBindTexture(GL_TEXTURE_2D, tn);
    }
  }
  return prg;
} /* End of 'EV5_RndMtlApply' function */

/* END OF 'RNDMTL.C' FILE */
