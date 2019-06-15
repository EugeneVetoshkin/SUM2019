/* FILE NAME   : RNDSHD.C
 * PURPOSE     : WinAPI animation system.
 *               Rendering system implementation module.
 *               Base functions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 12.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include <stdio.h>
#include <string.h>

#include "rnd.h"

/* Load text from file function.
 * ARGUMENTS:
 *   - file name to be load from:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text (allocated through malloc).
 */
static CHAR * EV5_RndShdLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  CHAR *txt;
  INT flen;

  /* Open file */
  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  /* Allocate memory for file text */
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }

  /* Load text from file to memory */
  memset(txt, 0, flen + 1);
  fread(txt, 1, flen, F);

  fclose(F);
  return txt;
} /* End of 'EV5_RndShdLoadTextFromFile' function */

/* Store log to file function.
 * ARGUMENTS:
 *   - message file prefix, shader name and text:
 *       CHAR *PartName, *Text;
 * RETURNS: None.
 */
static VOID EV5_RndShdLog( CHAR *Prefix, CHAR *Type, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("BIN/SHADERS/EV5{30}SHD.LOG", "a")) == NULL)
    return;
  fprintf(F, "%s/%s.GLSL:\n%s\n", Prefix, Type, Text);
  fclose(F);
} /* End of 'EV5_RndShdLog' function */

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader program Id.
 */
INT EV5_RndShdLoad( CHAR *ShaderFileNamePrefix )
{
  struct
  {
    CHAR *Name; /* Shader file prefix name */
    INT Type;   /* Shader OpenGL type */
    INT Id;     /* Shader Id created by OpenGL */
  } shd[] =
  {
    {"VERT", GL_VERTEX_SHADER},
    {"FRAG", GL_FRAGMENT_SHADER}
  };
  INT i, Ns = sizeof(shd) / sizeof(shd[0]), res, prg = 0;
  CHAR *txt;
  BOOL is_ok = TRUE;
  static CHAR Buf[3000];

  for (i = 0; is_ok && i < Ns; i++)
  {
    /* Load shader text from file */
    sprintf(Buf, "BIN/SHADERS/%s/%s.glsl", ShaderFileNamePrefix, shd[i].Name);
    if ((txt = EV5_RndShdLoadTextFromFile(Buf)) == NULL)
    {
      EV5_RndShdLog(ShaderFileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }
    /* Create shader */
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      EV5_RndShdLog(ShaderFileNamePrefix, shd[i].Name, "Error create shader");
      free(txt);
      is_ok = FALSE;
      break;
    }
    /* Attach shader source code to shader */
    glShaderSource(shd[i].Id, 1, &txt, NULL);
    free(txt);

    /* Compile shader */
    glCompileShader(shd[i].Id);
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      EV5_RndShdLog(ShaderFileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }

  if (is_ok)
  {
    if ((prg = glCreateProgram()) == 0)
    {
      is_ok = FALSE;
      EV5_RndShdLog(ShaderFileNamePrefix, "PROG", "Error create program");
    }
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < Ns; i++)
        if (shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      /* Link shader program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        EV5_RndShdLog(ShaderFileNamePrefix, "PROG", Buf);
        is_ok = FALSE;
      }
    }
  }

  if (!is_ok)
  {
    /* Remove all shaders */
    for (i = 0; i < Ns; i++)
      if (shd[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
    /* Remove program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  return prg;
} /* End of 'EV5_RndShdLoad' function */

/* Unload shader program from memory files function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETURNS: None.
 */
VOID EV5_RndShdDelete( INT ProgId )
{
  INT shdrs[5], n, i;

  if (ProgId == 0)
    return;
  glGetAttachedShaders(ProgId, 5, &n, shdrs);
  for (i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);
} /* End of 'EV5_RndShdDelete' function */

/***
 * Shader stock support
 ***/

/* Shaders stock */
ev5SHADER EV5_RndShaders[EV5_MAX_SHADERS]; /* Array of shaders */
INT EV5_RndShadersSize;                    /* Shadres array store size */

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader program Id.
 */
INT EV5_RndShdLoad( CHAR *ShaderFileNamePrefix );

/* Unload shader program from memory files function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETURNS: None.
 */
VOID EV5_RndShdDelete( INT ProgId );

/* Shaders support initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndShdInit( VOID )
{
  memset(EV5_RndShaders, 0, sizeof(EV5_RndShaders));
  EV5_RndShadersSize = 0;
  EV5_RndShdAdd("DEFAULT");
} /* End of 'EV5_RndShdInit' function */

/* Shaders support dinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndShdClose( VOID )
{
  INT i;

  for (i = 0; i < EV5_RndShadersSize; i++)
    EV5_RndShdDelete(EV5_RndShaders[i].ProgId);
  memset(EV5_RndShaders, 0, sizeof(EV5_RndShaders));
  EV5_RndShadersSize = 0;
} /* End of 'EV5_RndShdClose' function */

/* Load shader program and add to stock function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader stock index.
 */
INT EV5_RndShdAdd( CHAR *ShaderFileNamePrefix )
{
  INT i;

  for (i = 0; i < EV5_RndShadersSize; i++)
    if (strcmp(EV5_RndShaders[i].Name, ShaderFileNamePrefix) == 0)
    {
      EV5_RndShdDelete(EV5_RndShaders[i].ProgId);
      EV5_RndShaders[i].ProgId = EV5_RndShdLoad(ShaderFileNamePrefix);
      return i;
    }
  if (EV5_RndShadersSize >= EV5_MAX_SHADERS)
    return 0;
  strncpy(EV5_RndShaders[EV5_RndShadersSize].Name,
          ShaderFileNamePrefix, EV5_STR_MAX - 1);
  EV5_RndShaders[EV5_RndShadersSize].ProgId = EV5_RndShdLoad(ShaderFileNamePrefix);
  return EV5_RndShadersSize++;
} /* End of 'EV5_RndShdAdd' function */

/* Shaders stock update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndShdUpdate( VOID )
{
  INT i;

  for (i = 0; i < EV5_RndShadersSize; i++)
  {
    EV5_RndShdDelete(EV5_RndShaders[i].ProgId);
    EV5_RndShaders[i].ProgId = EV5_RndShdLoad(EV5_RndShaders[i].Name);
  }
} /* End of 'EV5_RndShdUpdate' function */

/* END OF 'RNDSHD.C' FILE */
