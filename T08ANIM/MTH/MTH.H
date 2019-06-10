/*PROGRAMMER: Vetoshkin Eugene
  IFK: EV5
  CLASS: 10-5
  DATE: 1.06.2019
  FILE: "MTH.H"
  */

#ifndef __MTH_H_
#define __MTH_H_
#include "..\DEF.H"
#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define R2D(A) ((A) * (180.0 / PI))
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#define MatrMulMatr3(a, b, c) MatrMulMatr(MatrMulMatr(a, b), c)

typedef double DBL;

typedef struct tagVEC
{
    DBL X, Y, Z; 
} VEC;


typedef struct tagMATR
{
    DBL A[4][4];
} MATR;

static MATR UniteMatr =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

__inline VEC VecSet(DBL X, DBL Y, DBL Z)
{
    VEC v;

    v.X = X;
    v.Y = Y;
    v.Z = Z;
    return v;
}

__inline VEC VecAddVec(VEC V1, VEC V2)
{
    return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} 

__inline VEC VecSubVec(VEC V1, VEC V2)
{
    return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} 

__inline VEC VecMulNum(VEC V, DBL N)
{
    return VecSet(V.X * N, V.Y * N, V.Z * N);
} 

__inline VEC VecDivNum(VEC V1, DBL N)
{
    return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} 

__inline VEC VecNeg(VEC V)
{
    return VecSet(-V.X, -V.Y, -V.Z);
} 

__inline DBL VecDotVec(VEC V1, VEC V2)
{
    return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

__inline VEC VecCrossVec(VEC V1, VEC V2)
{
  /*
  MATR m;

  m.A[0][0] = 1;
  m.A[0][1] = 1;
  m.A[0][2] = 1;

  m.A[1][0] = V1.X;
  m.A[1][1] = V1.Y;
  m.A[1][2] = V1.Z;

  m.A[2][0] = V2.X;
  m.A[2][1] = V2.Y;
  m.A[2][2] = V2.Z;
  */
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}
__inline DBL VecLen2(VEC V)
{
    return V.X * V.X + V.Y * V.Y + V.Z * V.Z;
}

__inline DBL VecLen(VEC V)
{
   DBL len = V.X * V.X + V.Y * V.Y + V.Z * V.Z;

   if (len != 0 && len != 1)
       return sqrt(len);
   return len;
}

__inline VEC VecMulMatr( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.X * M.A[0][1] + V.X * M.A[0][2],
                V.Y * M.A[1][0] + V.Y * M.A[1][1] + V.Y * M.A[1][2],
                V.Z * M.A[2][0] + V.Z * M.A[2][1] + V.Z * M.A[2][2]);
}

__inline MATR MatrIdentity(VOID)
{
    MATR m = UniteMatr;

    return m;
}
__inline MATR MatrTranslate(VEC Dv)
{
    MATR m =
    {
      {
        {   1,    0,    0,  0},
        {   0,    1,    0,  0},
        {   0,    0,    1,  0},
        {Dv.X, Dv.Y, Dv.Z,  1}
      }
    };

    return m;
}
__inline MATR MatrScale(VEC Sv)
{
    MATR m =
    {
      {
        {Sv.X,    0,    0,  0},
        {   0, Sv.Y,    0,  0},
        {   0,    0, Sv.Z,  0},
        {   0,    0,    0,  1}
      }
    };

    return m;
}

__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}

__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.X * M.A[0][1] + V.X * M.A[0][2],
                V.Y * M.A[1][0] + V.Y * M.A[1][1] + V.Y * M.A[1][2],
                V.Z * M.A[2][0] + V.Z * M.A[2][1] + V.Z * M.A[2][2]);
}

__inline MATR MatrMulMatr(MATR M1, MATR M2)
{
    MATR r;

    r.A[0][0] = M1.A[0][0] * M2.A[0][0] + M1.A[0][1] * M2.A[1][0] + M1.A[0][2] * M2.A[2][0] + M1.A[0][3] * M2.A[3][0];
    r.A[0][1] = M1.A[0][0] * M2.A[0][1] + M1.A[0][1] * M2.A[1][1] + M1.A[0][2] * M2.A[2][1] + M1.A[0][3] * M2.A[3][1];
    r.A[0][2] = M1.A[0][0] * M2.A[0][2] + M1.A[0][1] * M2.A[1][2] + M1.A[0][2] * M2.A[2][2] + M1.A[0][3] * M2.A[3][2];
    r.A[0][3] = M1.A[0][0] * M2.A[0][3] + M1.A[0][1] * M2.A[1][3] + M1.A[0][2] * M2.A[2][3] + M1.A[0][3] * M2.A[3][3];

    r.A[1][0] = M1.A[1][0] * M2.A[0][0] + M1.A[1][1] * M2.A[1][0] + M1.A[1][2] * M2.A[2][0] + M1.A[1][3] * M2.A[3][0];
    r.A[1][1] = M1.A[1][0] * M2.A[0][1] + M1.A[1][1] * M2.A[1][1] + M1.A[1][2] * M2.A[2][1] + M1.A[1][3] * M2.A[3][1];
    r.A[1][2] = M1.A[1][0] * M2.A[0][2] + M1.A[1][1] * M2.A[1][2] + M1.A[1][2] * M2.A[2][2] + M1.A[1][3] * M2.A[3][2];
    r.A[1][3] = M1.A[1][0] * M2.A[0][3] + M1.A[1][1] * M2.A[1][3] + M1.A[1][2] * M2.A[2][3] + M1.A[1][3] * M2.A[3][3];

    r.A[2][0] = M1.A[2][0] * M2.A[0][0] + M1.A[2][1] * M2.A[1][0] + M1.A[2][2] * M2.A[2][0] + M1.A[2][3] * M2.A[3][0];
    r.A[2][1] = M1.A[2][0] * M2.A[0][1] + M1.A[2][1] * M2.A[1][1] + M1.A[2][2] * M2.A[2][1] + M1.A[2][3] * M2.A[3][1];
    r.A[2][2] = M1.A[2][0] * M2.A[0][2] + M1.A[2][1] * M2.A[1][2] + M1.A[2][2] * M2.A[2][2] + M1.A[2][3] * M2.A[3][2];
    r.A[2][3] = M1.A[2][0] * M2.A[0][3] + M1.A[2][1] * M2.A[1][3] + M1.A[2][2] * M2.A[2][3] + M1.A[2][3] * M2.A[3][3];

    r.A[3][0] = M1.A[3][0] * M2.A[0][0] + M1.A[3][1] * M2.A[1][0] + M1.A[3][2] * M2.A[2][0] + M1.A[3][3] * M2.A[3][0];
    r.A[3][1] = M1.A[3][0] * M2.A[0][1] + M1.A[3][1] * M2.A[1][1] + M1.A[3][2] * M2.A[2][1] + M1.A[3][3] * M2.A[3][1];
    r.A[3][2] = M1.A[3][0] * M2.A[0][2] + M1.A[3][1] * M2.A[1][2] + M1.A[3][2] * M2.A[2][2] + M1.A[3][3] * M2.A[3][2];
    r.A[3][3] = M1.A[3][0] * M2.A[0][3] + M1.A[3][1] * M2.A[1][3] + M1.A[3][2] * M2.A[2][3] + M1.A[3][3] * M2.A[3][3];

    return r;
} 

__inline MATR MatrTranspose( MATR M )
{
  MATR M1;

  M1.A[0][0] = M.A[0][0];
  M1.A[0][1] = M.A[1][0];
  M1.A[0][2] = M.A[2][0];
  M1.A[0][3] = M.A[3][0];
  M1.A[1][0] = M.A[0][1];
  M1.A[1][1] = M.A[1][1];
  M1.A[1][2] = M.A[2][1];
  M1.A[1][3] = M.A[3][1];
  M1.A[2][0] = M.A[0][2];
  M1.A[2][1] = M.A[1][2];
  M1.A[2][2] = M.A[2][2];
  M1.A[2][3] = M.A[3][2];
  M1.A[3][0] = M.A[0][3];
  M1.A[3][1] = M.A[1][3];                                                       
  M1.A[3][2] = M.A[2][3];
  M1.A[3][3] = M.A[3][3];
  return M1;
}


__inline DBL MatrDeterm3x3(DBL A11, DBL A12, DBL A13,
    DBL A21, DBL A22, DBL A23,
    DBL A31, DBL A32, DBL A33)
{
    return A11 * A22 * A33 -
        A11 * A23 * A32 -
        A12 * A21 * A33 +
        A12 * A23 * A31 +
        A13 * A21 * A32 -
        A13 * A22 * A31;
} 

__inline DBL MatrDeterm(MATR M)
{
    return
        M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
            M.A[2][1], M.A[2][2], M.A[2][3],
            M.A[3][1], M.A[3][2], M.A[3][3]) -
        M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
            M.A[2][0], M.A[2][2], M.A[2][3],
            M.A[3][0], M.A[3][2], M.A[3][3]) +
        M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
            M.A[2][0], M.A[2][1], M.A[2][3],
            M.A[3][0], M.A[3][1], M.A[3][3]) -
        M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
            M.A[2][0], M.A[2][1], M.A[2][2],
            M.A[3][0], M.A[3][1], M.A[3][2]);
}

__inline MATR MatrInverse(MATR M)
{
    MATR r;
    DBL det = MatrDeterm(M);

    if (det == 0)
    {
        MATR m = UniteMatr;

        return m;
    }

    r.A[0][0] =
        MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
            M.A[2][1], M.A[2][2], M.A[2][3],
            M.A[3][1], M.A[3][2], M.A[3][3]) / det;
    r.A[1][0] =
        -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
            M.A[2][0], M.A[2][2], M.A[2][3],
            M.A[3][0], M.A[3][2], M.A[3][3]) / det;
    r.A[2][0] =
        MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
            M.A[2][0], M.A[2][1], M.A[2][3],
            M.A[3][0], M.A[3][1], M.A[3][3]) / det;
    r.A[3][0] =
        -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
            M.A[2][0], M.A[2][1], M.A[2][2],
            M.A[3][0], M.A[3][1], M.A[3][2]) / det;

    r.A[0][1] =
        -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
            M.A[2][1], M.A[2][2], M.A[2][3],
            M.A[3][1], M.A[3][2], M.A[3][3]) / det;
    r.A[1][1] =
        MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
            M.A[2][0], M.A[2][2], M.A[2][3],
            M.A[3][0], M.A[3][2], M.A[3][3]) / det;
    r.A[2][1] =
        -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
            M.A[2][0], M.A[2][1], M.A[2][3],
            M.A[3][0], M.A[3][1], M.A[3][3]) / det;
    r.A[3][1] =
        MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
            M.A[2][0], M.A[2][1], M.A[2][2],
            M.A[3][0], M.A[3][1], M.A[3][2]) / det;

    r.A[0][2] =
        MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
            M.A[1][1], M.A[1][2], M.A[1][3],
            M.A[3][1], M.A[3][2], M.A[3][3]) / det;
    r.A[1][2] =
        -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
            M.A[1][0], M.A[1][2], M.A[1][3],
            M.A[3][0], M.A[3][2], M.A[3][3]) / det;
    r.A[2][2] =
        MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
            M.A[1][0], M.A[1][1], M.A[1][3],
            M.A[3][0], M.A[3][1], M.A[3][3]) / det;
    r.A[3][2] =
        -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
            M.A[1][0], M.A[1][1], M.A[1][2],
            M.A[3][0], M.A[3][1], M.A[3][2]) / det;

    r.A[0][3] =
        -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
            M.A[1][1], M.A[1][2], M.A[1][3],
            M.A[2][1], M.A[2][2], M.A[2][3]) / det;

    r.A[1][3] =
        MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
            M.A[1][0], M.A[1][2], M.A[1][3],
            M.A[2][0], M.A[2][2], M.A[2][3]) / det;
    r.A[2][3] =
        -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
            M.A[1][0], M.A[1][1], M.A[1][3],
            M.A[2][0], M.A[2][1], M.A[2][3]) / det;
    r.A[3][3] =
        MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
            M.A[1][0], M.A[1][1], M.A[1][2],
            M.A[2][0], M.A[2][1], M.A[2][2]) / det;
    return r;
} 
__inline VEC VecNormalise(VEC V)
{ 
  if (VecLen( V ) == 1 || 0)
    return V;
  else
    return VecDivNum( V, VecLen( V ));
}
/*
__inline MATR VecCrossVec(VEC V)
{ 
 MATR m =
    {
      {
        { 1, 1, 1, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 1}
      }
    };

    return m; 
} */

__inline MATR MatrRotateX( DBL AngleInDegree )
  {
    MATR MatrRotateX = MatrIdentity();
    DBL A = (DBL)D2R(AngleInDegree), si = sin(A), co = cos(A);

    MatrRotateX.A[1][1] = co;
    MatrRotateX.A[1][2] = si;
    MatrRotateX.A[2][1] = -si;
    MatrRotateX.A[2][2] = co;

    return MatrRotateX;
  } 

  __inline MATR MatrRotateY( DBL AngleInDegree )
  {
    MATR MatrRotateY = MatrIdentity();
    DBL A = (DBL)D2R(AngleInDegree), si = sin(A), co = cos(A);
    MatrRotateY.A[0][0] = co;
    MatrRotateY.A[0][2] = -si;
    MatrRotateY.A[2][0] = si;
    MatrRotateY.A[2][2] = co;
    return MatrRotateY;
  } 

  __inline MATR MatrRotateZ( DBL AngleInDegree )
  {
    MATR MatrRotateZ = MatrIdentity();
    DBL A = (DBL)D2R(AngleInDegree), si = sin(A), co = cos(A);
    MatrRotateZ.A[0][0] = co;
    MatrRotateZ.A[1][0] = -si;
    MatrRotateZ.A[0][1] = si;
    MatrRotateZ.A[1][1] = co;

    return MatrRotateZ;
  } 




__inline MATR MatrRotate(DBL AngleInDegree, VEC R)
{
    DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
    VEC V = VecNormalise(R);
    MATR M =
    {
      {
        {co + V.X * V.X * (1 - co),
          V.X * V.Y * (1 - co) + V.Z * si,
            V.X * V.Z * (1 - co) - V.Y * si, 0},
        {V.Y * V.X * (1 - co) - V.Z * si,
          co + V.Y * V.Y * (1 - co),
            V.Y * V.Z * (1 - co) + V.X * si, 0},
        {V.Z * V.X * (1 - co) + V.Y * si,
          V.Z * V.Y * (1 - co) - V.Y * si,
          co + V.Z * V.Z * (1 - co), 0},
        {0, 0, 0, 1}
      }
    };
}

/* Perspective (frustum) projection matrix setup function.
 * ARGUMENTS:
 *   - frustum side facets coordinates:
 *       DBL Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrFrustum( DBL Left, DBL Right, DBL Bottom, DBL Top, DBL Near, DBL Far )
{
  MATR m =
  {
    {
      {      2 * Near / (Right - Left),                               0,                              0,  0},
      {                              0,       2 * Near / (Top - Bottom),                              0,  0},
      {(Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom),   -(Far + Near) / (Far - Near), -1},
      {                              0,                               0, -2 * Near * Far / (Far - Near),  0}
    }
  };

  return m;
} /* End of 'MatrFrustum' function */

__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalise(VecSubVec(At, Loc)),
    Right = VecNormalise(VecCrossVec(Dir, Up1)),
    Up = VecCrossVec(Right, Dir);
  MATR m = 
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };
  return m;
}


#endif

/* END OF "MTH.H" FILE */