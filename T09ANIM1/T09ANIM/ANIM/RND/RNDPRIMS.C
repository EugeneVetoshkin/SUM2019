/* FILE NAME   : RNDPRIMS.C
 * PURPOSE     : WinAPI animation system.
 *               Rendering system implementation module.
 *               Primitive collection support.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 15.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include <stdio.h>

#include "../anim.h"

/* Create array of primitives function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       ev5PRIMS *Prs;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL EV5_RndPrimsCreate( ev5PRIMS *Prs, INT NoofP )
{
  memset(Prs, 0, sizeof(ev5PRIMS));
  if ((Prs->Prims = malloc(sizeof(ev5PRIM) * NoofP)) == NULL)
    return FALSE;
  memset(Prs->Prims, 0, sizeof(ev5PRIM) * NoofP);
  Prs->NumOfPrims = NoofP;
  Prs->Trans = MatrIdentity();
  return TRUE;
} /* End of 'EV5_RndPrimsCreate' function */

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       ev5PRIMS *Prs;
 * RETURNS: None.
 */
VOID EV5_RndPrimsFree( ev5PRIMS *Prs )
{
  INT i;

  for (i = 0; i < Prs->NumOfPrims; i++)
    EV5_RndPrimFree(&Prs->Prims[i]);
  free(Prs->Prims);
  memset(Prs, 0, sizeof(ev5PRIMS));
} /* End of 'EV5_RndPrimsFree' function */

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       ev5PRIMS *Prs;
 * RETURNS: None.
 */
VOID EV5_RndPrimsDraw( ev5PRIMS *Prs, MATR World )
{
  INT i;

  World = MatrMulMatr(Prs->Trans, World);
  for (i = 0; i < Prs->NumOfPrims; i++)
    EV5_RndPrimDraw(&Prs->Prims[i], World);
} /* End of 'EV5_RndPrimsDraw' function */

/* Load array of primitives from G3DM file function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       ev5PRIMS *Prs;
 *   - file name to load from:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL EV5_RndPrimsLoad( ev5PRIMS *Prs, CHAR *FileName )
{
  FILE *F;
  INT flen, i;
  BYTE *mem, *ptr;
  DWORD Sign;
  INT NumOfPrims, NumOfMtls, NumOfTexs;
  struct tagMTLS
  {
    /* Load material name */
    CHAR Name[300];
    /* Illumination coefficients */    
    VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
    FLT Ph;                   /* Phong power coefficient */
    FLT Trans;                /* Transparency factor */
    INT Tex[8];               /* Texture references from texture table */
    /* Shader string */
    CHAR ShaderStr[300];
    INT ShaderNo;             /* Shader reference in shader table */
  } *mtls;

  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }

  rewind(F);
  ptr = mem;
  fread(mem, 1, flen, F);

  Sign = *(DWORD *)ptr, ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    fclose(F);
    return FALSE;
  }
  NumOfPrims = *(INT *)ptr, ptr += 4;
  NumOfMtls = *(INT *)ptr, ptr += 4;
  NumOfTexs = *(INT *)ptr, ptr += 4;

  if (!EV5_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    fclose(F);
    return FALSE;
  }
  /* Primitives */
  for (i = 0; i < NumOfPrims; i++)
  {
    INT nv, ni, mtlno;
    ev5VERTEX *V;
    INT *Ind;

    nv = *(INT *)ptr, ptr += 4;
    ni = *(INT *)ptr, ptr += 4;
    mtlno = *(INT *)ptr, ptr += 4;
    V = (ev5VERTEX *)ptr, ptr += sizeof(ev5VERTEX) * nv;
    Ind = (INT *)ptr, ptr += sizeof(INT) * ni;
    EV5_RndPrimCreate(&Prs->Prims[i], EV5_RND_PRIM_TRIMESH, V, nv, Ind, ni);
    Prs->Prims[i].MtLNo = mtlno + EV5_RndMaterialsSize;
  }

  /* Materials */
  mtls = (struct tagMTLS *)ptr, ptr += sizeof(struct tagMTLS) * NumOfMtls;
  for (i = 0; i < NumOfMtls; i++)
  {
    INT j;
    ev5MATERIAL mtl = {{0}};

    strcpy(mtl.Name, mtls[i].Name);
    mtl.Ka = mtls[i].Ka;
    mtl.Kd = mtls[i].Kd;
    mtl.Ks = mtls[i].Ks;
    mtl.Ph = mtls[i].Ph;
    mtl.Trans = mtls[i].Trans;
    for (j = 0; j < 8; j++)
    {
      if (mtls[i].Tex[j] != -1)
        mtls[i].Tex[j] += EV5_RndTexturesSize;
      mtl.Tex[j] = mtls[i].Tex[j];
    }
    EV5_RndMtlAdd(&mtl);
  }


  /* Textures */
  for (i = 0; i < NumOfTexs; i++)
  {
    CHAR *Name = (CHAR *)ptr;
    INT
      W = *(INT *)(ptr + 300), 
      H = *(INT *)(ptr + 300 + 4), 
      BPP = *(INT *)(ptr + 300 + 4 + 4);

    ptr += 312;
    EV5_RndTexAddImg(Name, W, H, BPP, ptr);
    ptr += W * H * BPP;
  }

  free(mem);
  fclose(F);
#if 0
  Массив текстур:
    На каждый текстуру:
      Имя текстуры [300 символов]
      W, H, количество байт на точку
      W * H * кбнт байт цветов точек
#endif /* 0 */

  return TRUE;
} /* End of 'EV5_RndPrimsLoad' function */

/* END OF 'RNDPRIMS.C' FILE */
