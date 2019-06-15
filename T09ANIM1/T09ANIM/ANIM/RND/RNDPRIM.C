/* FILE NAME   : RNDPRIM.H
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Vetoshkin Eugene.
* LAST UPDATE : 10.06.2019.
* NOTE        : Module prefix 'EV5'.
*/


#include <string.h>
#include <stdio.h>

#include "..\anim.h"

BOOL EV5_RndPrimCreate( ev5PRIM *Pr, ev5PRIM_TYPE Type, ev5VERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  /*INT size;*/
  
  glGenBuffers(1, &Pr->VBuf);
  glGenVertexArrays(1, &Pr->VA);
  glGenBuffers(1, &Pr->IBuf);

  glBindVertexArray(Pr->VA);

  glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);

  glBufferData(GL_ARRAY_BUFFER, sizeof(ev5VERTEX) * NoofV, V, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(ev5VERTEX), (VOID *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  Pr->Trans = MatrIdentity();

  return TRUE;
}
VOID EV5_RndPrimFree( ev5PRIM *Pr )
{
  glBindVertexArray(Pr->VA);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(ev5PRIM));
} /* End of 'EV5_RndPrimFree' function */


VOID EV5_RndPrimDraw( ev5PRIM *Pr, MATR World )
{
  INT loc;
  /*INT i;*/
  /* POINT *pnts;  vertex projections */
  MATR M = MatrMulMatr3(Pr->Trans, World, EV5_RndMatrVP);
/*
  glUseProgram();

  if ((loc = glGetUniformLocation(, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, M.A[0]);
  if ((loc = glGetUniformLocation(, "Time")) != -1)
    glUniform1f(loc, EV5_Anim.Time );


*/
  EV5_RndCounterPrims++;
  EV5_triangles +=  Pr->NumOfElements / 3;
  /* Draw all triangles */
  glLoadMatrixf(M.A[0]);

  /* Draw all triangles */
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  glBindVertexArray(Pr->VA);
  if (Pr->IBuf == 0)
    glDrawArrays(GL_TRIANGLES, 0, Pr->NumOfElements);
  else 
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(GL_TRIANGLES, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
  }
}/* End of 'EV5_RndPrimDraw' function */

BOOL EV5_RndPrimLoad( ev5PRIM *Pr, CHAR *FileName )
{
  INT nv, nf/*, size*/;
  INT *I;
  ev5VERTEX *V;
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

  /* Allocate memory */
   
  V = malloc(nv * sizeof(ev5VERTEX));
  if (V == NULL)
    return FALSE;

  /* Set index array pointer */
  I = malloc(3 * nf * sizeof(INT));
  if (I == NULL)
  {
    free(V);
    fclose(F);
    return FALSE;
  }

  /* Fill all allocated memory by 0 */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d%//%*d %d%//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      I[nf++] = n1 - 1;
      I[nf++] = n2 - 1;
      I[nf++] = n3 - 1;
    }
  fclose(F);
  if (nf == 0)
    Pr->NumOfElements = nv;
  else
    Pr->NumOfElements = nf;
  EV5_RndPrimCreate(Pr, EV5_RND_PRIM_TRIMESH, V, nv, I, nf);
  return TRUE;
} /* End of 'EV5_RndPrimLoad' function */

/*End of 'RNDPRIM.C'*/