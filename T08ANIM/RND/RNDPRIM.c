/*PROGRAMMER: Vetoshkin Eugene
  IFK: EV5
  CLASS: 10-5
  DATE: 1.06.2019
  FILE: "MAIN.C"
  */
#include "..\DEF.H"
#include <string.h>
#include <stdio.h>
#include "RND.H"
#include <stdlib.h> -- (def.h)



BOOL EV5_RndPrimCreate( ev5PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(ev5PRIM));


  /* Calculate memory size for primitive data */
  size = sizeof(ev5VERTEX) * NoofV + sizeof(INT) * NoofI;

  /* Allocate memory */
  Pr->V = malloc(size);
  if (Pr->V == NULL)
    return FALSE;

  /* Set index array pointer */
  Pr->I = (INT *)(Pr->V + NoofV);

  /* Fill all allocated memory by 0 */
  memset(Pr->V, 0, size);

  /* Store data sizes */
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;

  /* Set default transform (identity) */
  Pr->Trans = MatrIdentity();

  return TRUE;
} /* End of 'EV5_RndPrimCreate' function */

VOID EV5_RndPrimFree( ev5PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(ev5PRIM));
} /* End of 'EV5_RndPrimFree' function */

VOID EV5_RndPrimDraw( ev5PRIM *Pr, MATR World )
{
  INT i;
  POINT *pnts; /* vertex projections */
  MATR M = MatrMulMatr3(Pr->Trans, World, EV5_RndMatrVP);

  /* Allocate memory for projections */
  pnts = malloc(sizeof(POINT) * Pr->NumOfV);
  if (pnts == NULL)
    return;

  /* Project all vertices */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    /* Convert from World to NDC */
    VEC p = VecMulMatr(Pr->V[i].P, M);

    /* Convert NDC to frame (viewport) */
    pnts[i].x = (p.X + 1) * EV5_RndFrameW / 2;
    pnts[i].y = (-p.Y + 1) * EV5_RndFrameH / 2;
  }

  /* Draw all triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    POINT p[3];

    p[0] = pnts[Pr->I[i]];
    p[1] = pnts[Pr->I[i + 1]];
    p[2] = pnts[Pr->I[i + 2]];
    Polygon(EV5_hDCRndFrame, p, 3);
  }
  free(pnts);
} /* End of 'EV5_RndPrimDraw' function */


BOOL EV5_RndPrimLoad( ev5PRIM *Pr, CHAR *FileName )
{
  INT nv, nf;
  FILE *F;
  CHAR Buf[1000];

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(ev5PRIM));

  /* Open file */
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and facet quantity */
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf++;

  /* Create primitive */
  if (!EV5_RndPrimCreate(Pr, nv, nf * 3))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d%//%*d %d%//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      Pr->I[nf++] = n1 - 1;
      Pr->I[nf++] = n2 - 1;
      Pr->I[nf++] = n3 - 1;
    }
  fclose(F);
  return TRUE;
} /* End of 'EV5_RndPrimLoad' function */

/* END OF "MTH.H" FILE */