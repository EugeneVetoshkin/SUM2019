#include "GLOBE.h"
#include <math.h>
#include <stdio.h>
#include "TIMER.h"

VEC G[N][M];

VOID GLOBE( void )
{
  INT i, j;
  DOUBLE t, p, x, y, z, R = 300;

  for (i = 0, t = 0; i < N; i++, t += PI / (N - 1))
    for (j = 0, p = 0; j < M; j++, p += 2 * PI / (M - 1))
     {
        x = R * cos(p) * sin(t);
        y = R * cos(t);
        z = R * sin(p) * sin(t);
        
        G[i][j].X = x;
        G[i][j].Y = y;
        G[i][j].Z = z;
     }
}

VOID DRAW(HDC hDC, INT w, INT h)
{
   INT i, j, Xc = w / 2, Yc = h / 2;
   DOUBLE s;
   static CHAR Buf[100];
   GLB_TimerResponse();

      /// SelectObject(hDC, GetStockObject(DC_BRUSH));
      /// SetDCBrushColor(hDC, RGB(163, 64, ));
    for (i = 0; i < N - 1; i++)
      
      for (j = 0; j < M - 1; j++)
        {
          POINT ps[4];

          ps[0].x = G[i][j].X + w / 2; ps[0].y = G[i][j].Y + h / 2;
          ps[1].x = G[i][j + 1].X + w / 2; ps[1].y = G[i][j + 1].Y + h / 2;
          ps[2].x = G[i + 1][j + 1].X + w / 2; ps[2].y = G[i + 1][j + 1].Y + h / 2;
          ps[3].x = G[i + 1][j].X + w / 2; ps[3].y = G[i + 1][j].Y + h / 2;

          s = ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
               (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
               (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
               (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y));
          if (s >= 0)
          {
            SelectObject(hDC, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hDC, RGB( (i + j) * (255 / M) * GLB_IsPause, (i * j) * GLB_IsPause * (255 / M),(i - j) * (255 / M) * GLB_Time * 2  ));
            Polygon(hDC, ps, 4);
          }
    }
        SetTextColor(hDC, RGB(2, 5, 55));
        TextOut(hDC, 8, 8, Buf, sprintf(Buf, "FPS: %.3f", GLB_FPS));
}

VEC ROT_Y(VEC p, DOUBLE angle)
{
    DOUBLE a = angle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.X = p.X * co - p.Y * si;
    r.Y = p.X * si + p.Y * co;
    r.Z = p.Z;

    return r;
}

VEC ROT_X(VEC p, DOUBLE angle)
{
    DOUBLE a = angle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.Y = p.Y  * co - p.Z * si;
    r.Z = p.Y * si + p.Z * co;
    r.X = p.X;

    return r;
}