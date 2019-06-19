/* FILE NAME   : U_Drone.C
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#include "units.h"

/* Drone unit type */
typedef struct
{
  EV5_UNIT_BASE_FIELDS;
  ev5PRIM Drone;
  ev5PRIMS Prim;
  VEC 
    pos;
  FLT 
    Velocity,
    Acceleration,
    Head,
    HeadH;
} ev5UNIT_Drone;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Drone *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitInit( ev5UNIT_Drone *Uni, ev5ANIM *Ani )
{
  //EV5_RndPrimLoad(&Uni->Drone, "cow.object");
  EV5_RndPrimsLoad(&Uni->Prim,"Drone/Drone.g3dm");
  Uni->Velocity = 0.1;
  Uni->Acceleration = 0.05;
} /* End of 'EV5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Drone *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitClose( ev5UNIT_Drone *Uni, ev5ANIM *Ani )
{
  EV5_RndPrimsFree(&Uni->Prim);
} /* End of 'EV5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Drone *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
static VOID EV5_UnitResponse( ev5UNIT_Drone *Uni, ev5ANIM *Ani )
{
  Uni->Prim.Prims[0].Trans = MatrTranslate(VecSet( 0, sin(EV5_Anim.GlobalTime ) * 0.3, 0));
  Uni->Prim.Prims[1].Trans = MatrTranslate(VecSet( 0, sin(EV5_Anim.GlobalTime ) * 0.3, 0));
  Uni->Prim.Prims[2].Trans = MatrMulMatr(
                                         MatrRotateX(sin(EV5_Anim.GlobalTime * 5 * Uni->Velocity) * 25),
                                         MatrTranslate(VecSet( 0, sin(EV5_Anim.GlobalTime) * 0.3, 0))
                                        );
} /* End of 'EV5_UnitResponse' function */


/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ev5UNIT_Drone *Uni;
 *   - animation context:
 *       ev5ANIM *Ani;
 * RETURNS: None.
 */
/*
static VOID EV5_UnitRender( ev5UNIT_Drone *Uni, ev5ANIM *Ani )
{
MATR m;
  VEC HeadV = VecSet(0, 0, 1);
  ///VEC HeadH = VecSet(0, 1, 0);

  
  Uni->Velocity = Uni->Velocity + Uni->Acceleration * EV5_Anim.DeltaTime * -EV5_Anim.JY; 

  Uni->Head += -EV5_Anim.JX;
  
  HeadV = VecMulMatr(HeadV, MatrRotateY(Uni->Head));
  ///HeadH = VecMulMatr(HeadH, MatrRotateX(Uni->HeadH));

  
  Uni->posos = VecAddVec(Uni->posos, VecMulNum(VecMulMatr(HeadV, MatrRotateY(Uni->Head)), Uni->Velocity));
 
  /// Uni->posos = VecAddVec(Uni->posos, VecMulNum(VecMulMatr(HeadH, MatrRotateX(Uni->HeadH)), VelH));

  
  m = MatrMulMatr5(
                    MatrScale(VecSet(0.1, 0.1, 0.1)),
                    MatrRotateZ(30 * EV5_Anim.JX ),
                    MatrRotateY(Uni->Head ),
                    MatrRotateY(0 * EV5_Anim.JR),
                    MatrTranslate(Uni->posos)
                  );
  EV5_RndCamSet(VecAddVec(Uni->posos, VecSet(0,-10,0)), Uni->posos, VecSet(0, 1, 0));
  
  EV5_RndPrimsDraw(&Uni->Prim, m);
}*/  /* End of 'EV5_UnitRender' function */

/* Drone unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ev5UNIT *) pointer to created unit.
 */
static VOID EV5_UnitRender( ev5UNIT_Drone *Uni, ev5ANIM *Ani )
{
  MATR m, m1;
  VEC HeadV = VecSet(0, 0, 1);
  VEC HeadH = VecSet(0, 1, 0);

  FLT Vel = -Ani->JY / 5;
  FLT VelH = Ani->JZ / 5;

  Uni->Head += -Ani->JX / 5;
  

  
  HeadV = VecMulMatr(HeadV, MatrRotateY(Uni->Head));
  HeadH = VecMulMatr(HeadH, MatrRotateX(Uni->HeadH));

  
  Uni->pos = VecAddVec(Uni->pos, VecMulNum(VecMulMatr(HeadV, MatrRotateY(Uni->Head)), Vel));
  Uni->pos = VecAddVec(Uni->pos, VecMulNum(VecMulMatr(HeadH, MatrRotateX(Uni->HeadH)), VelH));

  
  m = MatrMulMatr4(MatrScale(VecSet(0.1, 0.1, 0.1)),
                   MatrRotateX(-EV5_Anim.JZ * 5 + -EV5_Anim.JZ / 2.0 + -EV5_Anim.JZ / 1.0),
                   MatrRotateZ(EV5_Anim.JX * 20 + EV5_Anim.JX / 20.0 + EV5_Anim.JX / 50.0),
                   MatrRotateY(2 * Uni->Head)); 
  m1 = MatrMulMatr(m, MatrTranslate(Uni->pos));

  
  EV5_RndCamSet(VecSubVec(Uni->pos, VecAddVec(
                                            VecMulMatr(VecMulNum(HeadV, 0.8 + Ani->JR), MatrRotateY(Uni->Head)),
                                            VecMulMatr(VecMulNum(HeadH, -0.1), MatrRotateX(Uni->HeadH)))),
                Uni->pos,
                VecSet(0, 1, 0));

 
  EV5_RndPrimsDraw(&Uni->Prim, m1);
}


ev5UNIT * EV5_UnitDroneCreate( VOID )
{
  ev5UNIT *Uni;

  /* Memory allocation */
  if ((Uni = EV5_AnimUnitCreate(sizeof(ev5UNIT_Drone))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)EV5_UnitInit;
  Uni->Close = (VOID *)EV5_UnitClose;
  Uni->Response = (VOID *)EV5_UnitResponse;
  Uni->Render = (VOID *)EV5_UnitRender;
  return Uni;
} /* End of 'EV5_AnimUnitCreate' function */


