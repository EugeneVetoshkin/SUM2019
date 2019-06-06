/*Vetoshkin Eugeni 10-5 2018*/
#include <math.h>
#include "GLOBE.h"

VOID DrawGlobe(HDC hMemDC, INT N, INT X, INT Y)
{
  int i, j, x, y, R = 300;
  DOUBLE FI, TET;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
    {
      FI = 2 * PI * i / N;
      TET = PI * j / N;

      x = (INT)(R * sin(TET) * sin(FI)) + X / 2;
      y = (INT)(R * sin(TET));

      SelectObject(hMemDC, GetStockObject(NULL_PEN));
      SelectObject(hMemDC, GetStockObject(BLACK_BRUSH));
      Ellipse(hMemDC, x - 2, y + 2, x + 2, y - 2);
    }
}