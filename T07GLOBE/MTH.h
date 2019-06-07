 /*Vetshkin Eugene*/

#ifndef _MTH_H
#include <math.h>


#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

typedef double DBL;
typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

typedef struct tagMATR
{
  DBL M[4][4];
} MATR;


DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
}


static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};


VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
}

VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}

VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;  
}

VEC VecCrossVec( VEC V1, VEC V2 )
{
  return {
    {1, 1, 1},
    {V1.X, V1.Y, V1.Z},
    {V2.X, V2.Y, V2.Y}
  };
}
DBL VecLen2( VEC V )
{
  return V.X * V.X + V.Y * V.Y + V.Z * V.Z;
}

DBL VecLen1( VEC V )
{
  return sqrt(V.X * V.X + V.Y * V.Y + V.Z * V.Z);
}


VEC VecMulMatr( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.X * M.M[0][1] + V.X * M.M[0][2],
                V.Y * M.M[1][0] + V.Y * M.M[1][1] + V.Y * M.M[1][2],
                V.Z * M.M[2][0] + V.Z * M.M[2][1] + V.Z * M.M[2][2]);
}



VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.X * M.M[0][1] + V.X * M.M[0][2],
                V.Y * M.M[1][0] + V.Y * M.M[1][1] + V.Y * M.M[1][2],
                V.Z * M.M[2][0] + V.Z * M.M[2][1] + V.Z * M.M[2][2]);
}



VEC VectorTransform( VEC V, MATR M );
{
  return VecSet(V.X * M.M[0][0] + V.X * M.M[0][1] + V.X * M.M[0][2],
                V.Y * M.M[1][0] + V.Y * M.M[1][1] + V.Y * M.M[1][2],
                V.Z * M.M[2][0] + V.Z * M.M[2][1] + V.Z * M.M[2][2]);
}


MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}
MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
}




//MATR MatrScale( VEC S );
MATR MatrRotateX( DBL AngleInDegree )
{
  return {
    {1, 0, 0, 0},
    {0, cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0},
    {0, -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0},
    {0, 0, 0, 1}
  };
}

MATR MatrRotateY( DBL AngleInDegree )
{
  return {
    {cos(D2R(AngleInDegree)), 0, -sin(D2R(AngleInDegree)), 0},
    {0, 1, 0, 0},
    {sin(D2R(AngleInDegree)), 0, cos(D2R(AngleInDegree)), 0},
    {0, 0, 0, 1}
  }
}
MATR MatrRotateZ( DBL AngleInDegree )
{
  return {
    {cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0, 0},
    {-sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
}


MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  MATR r;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.A[i][j] = 0, k = 0; k < 4; k++)
        r.A[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
}
MATR MatrTranspose( MATR M );


DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                               M.M[2][0], M.M[2][2], M.M[2][3],
                               M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) +
    -M.A[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                               M.M[2][0], M.M[2][1], M.M[2][2],
                               M.M[3][0], M.M[3][1], M.M[3][2]);
}

DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                               M.M[2][0], M.M[2][2], M.M[2][3],
                               M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) +
    -M.A[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                               M.M[2][0], M.M[2][1], M.M[2][2],
                               M.M[3][0], M.M[3][1], M.M[3][2]);
}

MATR MatrScale( VEC S  )
{
    return {
      {S.X, 0, 0, 0},
    {0, S.Y, 0, 0},
      {0, 0, S.Z, 0},
    {0, 0, 0, 1}
  };
}

MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);

  if (det == 0)
    return UnitMatrix;
    
  r.A[0][0] =
    MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[2][1], M.A[2][2], M.A[2][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][0] =
    MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[2][0], M.A[2][1], M.A[2][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]);
  
  r.A[3][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);
  r.A[0][1] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[2][1], M.A[2][2], M.A[2][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][1] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                  M.A[2][0], M.A[2][1], M.A[2][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]);
  
  r.A[3][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);
  r.A[0][2] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][2] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                  M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]);
  
  r.A[3][2] =
    -MatrDeterm3x3(M.A[1][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);
  r.A[0][3] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[2][1], M.A[2][2], M.A[2][3]);
  r.A[1][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3]);
  r.A[2][3] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                  M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[2][0], M.A[2][1], M.A[2][3]);
  
  r.A[3][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2]);
  
  r.A[0][0] /= det;
  r.A[0][1] /= det;
  r.A[0][2] /= det;
  r.A[0][3] /= det;
  r.A[1][0] /= det;
  r.A[1][1] /= det;
  r.A[1][2] /= det;
  r.A[1][3] /= det;
  r.A[2][0] /= det;
  r.A[2][1] /= det;
  r.A[2][2] /= det;
  r.A[2][3] /= det;
  r.A[3][0] /= det;
  r.A[3][1] /= det;
  r.A[3][2] /= det;
  r.A[3][3] /= det;
  return r;
}

#endif  