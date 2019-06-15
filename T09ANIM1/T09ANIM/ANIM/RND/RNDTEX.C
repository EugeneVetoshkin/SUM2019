/* FILE NAME   : RNDTEX.C
 * PURPOSE     : WinAPI animation system.
 *               Rendering system implementation module.
 *               Resourses functions.
 *               Texture support.
 * PROGRAMMER  : ÿ.
 * LAST UPDATE : 12.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include <string.h>

#include "rnd.h"

/* Textures stock */
ev5TEXTURE EV5_RndTextures[EV5_MAX_TEXTURES]; /* Array of textures */
INT EV5_RndTexturesSize;                      /* Textures array store size */

/* Textures support initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndTexInit( VOID )
{
  memset(EV5_RndTextures, 0, sizeof(EV5_RndTextures));
  EV5_RndTexturesSize = 0;
} /* End of 'EV5_RndTexInit' function */

/* Textures support deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < EV5_RndTexturesSize; i++)
    glDeleteTextures(1, &EV5_RndTextures[i].TexId);
  memset(EV5_RndTextures, 0, sizeof(EV5_RndTextures));
  EV5_RndTexturesSize = 0;
} /* End of 'EV5_RndTexClose' function */

/* Add texture image to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - number of texture image components (3 or 4):
 *       INT C;
 *   - pointer to image pixel colors:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) add texture stock index.
 */
INT EV5_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  if (EV5_RndTexturesSize >= EV5_MAX_TEXTURES)
    return -1;

  /* Allocate texture space */
  glGenTextures(1, &EV5_RndTextures[EV5_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, EV5_RndTextures[EV5_RndTexturesSize].TexId);


  /* Upload texture */
  if (C == 4)
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
  else
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, W, H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Bits);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  strncpy(EV5_RndTextures[EV5_RndTexturesSize].Name, Name, EV5_STR_MAX - 1);
  EV5_RndTextures[EV5_RndTexturesSize].W = W;
  EV5_RndTextures[EV5_RndTexturesSize].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);

  return EV5_RndTexturesSize++;
} /* End of 'EV5_RndTexAddImg' function */

/* END OF 'RNDTEX.C' FILE */
