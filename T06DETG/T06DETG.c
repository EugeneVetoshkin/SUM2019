   
#include <stdio.h>
#include <windows.h>
#include <math.h>
#define MAX 10

INT P[MAX];
BOOL isParity = 1;
DOUBLE A[MAX][MAX];
INT N;
DOUBLE det;
FILE *f;


VOID swap (INT *a, INT *b)
{                                                       
    INT tmp = *a;

    *a = *b;
    *b = tmp;
}

VOID GAUS( VOID )
{
  
  int i, max_row, max_col, y, x;
  det = 1;
  
  for (i = 0; i < N; i++)
  {
    max_row = max_col = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
          max_col = x, max_row = y;
      if(A[max_row][max_col] == 0)
      {
        det = 0;
        break;
      }
      if (max_raw != i)
      {
        for (x = i; x < N; x++)
          Swap(&A[i][x], &A[max_raw][x]);
        det = -det;
      } 
      if (max_col != i)
      {
        for (y = i; y < N; y++)
          Swap(&A[i][y], &A[max_col][y]);
        det = -det;
      }
      coef = A[i + 1][i] / A[i][i];
      A[i][i] = 0;
  }
}

BOOL LOADMRTX (CHAR *fname)
{
  int i, j;
  N = 0;

  f = fopen (fname, "r");

  if (f == NULL)
    return FALSE;
  fscanf(f, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(f, "%lf", &A[i][j]);
  fclose(f);
  return TRUE;
}

INT Store( VOID )
{
  int i;
  double prod;

  for (i = 0, prod = 1; i < N; i++)
    prod *= A[i][P[i]];
  det += (isParity ? 1 : -1) * prod;
  return 1;
}

VOID Go( int pos)
{
  int i, x;
  BOOL save_parity;


  if (pos == N)
    Store();
  else 
  {
    save_parity = isParity;
    Go(pos + 1);
    for (i = pos + 1; i < N; i++ )
    {
      swap (&P[pos], &P[i]);
      if (isParity == 0 && i != pos )
        isParity = 1;
      else if (isParity == 1 && i != pos)
        isParity = 0;
      Go(pos + 1);
    }
    x = P[pos];
    for (i = pos + 1; i < N; i++)
    P[i -1] = P[i];
    P[N - 1] = x;
    isParity = save_parity;
  }
}


VOID main( void )
{
  int i;

  for (i = 0; i < MAX; i++)
    P[i] = i;
  LOADMRTX("IN.txt");
  Go(0);
  printf("determinat is %f", det);
  getchar();
}
