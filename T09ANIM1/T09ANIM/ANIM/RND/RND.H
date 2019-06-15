/* FILE NAME   : RND.H
 * PURPOSE     : WinAPI animation system.
 *               Base definitions.
 * PROGRAMMER  : Vetoshkin Eugene.
 * LAST UPDATE : 10.06.2019.
 * NOTE        : Module prefix 'EV5'.
 */

#ifndef __RND_H_
#define __RND_H_

#include "../../def.h"

#define GLEW_STATIC
#include <glew.h>

extern INT EV5_RndCounterPrims, EV5_triangles;
//extern INT EV5_RndProgId;

extern DBL
  EV5_RndProjSize,
  EV5_RndProjDist,
  EV5_RndProjFarClip;

extern MATR
  EV5_RndMatrView,
  EV5_RndMatrProj,
  EV5_RndMatrVP;



VOID EV5_RndInit( HWND hWnd );
VOID EV5_RndClose( VOID );

VOID EV5_RndStart( VOID );
VOID EV5_RndEnd( VOID );

VOID EV5_RndCopyFrame( VOID );
VOID EV5_RndResize( INT W, INT H );

VOID EV5_RndCamSet( VEC Loc, VEC At, VEC Up1 );
VOID EV5_RndProjSet( VOID );

/*** Primitives ***/

typedef struct tagev5VERTEX
{
  VEC P;  
} ev5VERTEX;

typedef enum tagev5PRIM_TYPE
{
  EV5_RND_PRIM_TRIMESH, 
  EV5_RND_PRIM_GRID 
} ev5PRIM_TYPE;


typedef struct tagev5PRIM
{
  ev5PRIM_TYPE Type;
  INT
    VA,
    VBuf,
    IBuf;
  INT NumOfElements;

  MATR Trans;
  INT MtLNo;
} ev5PRIM;

BOOL EV5_RndPrimLoad( ev5PRIM *Pr, CHAR *FileName );
VOID EV5_RndPrimDraw( ev5PRIM *Pr, MATR World );
VOID EV5_RndPrimFree( ev5PRIM *Pr );
BOOL EV5_RndPrimCreate( ev5PRIM *Pr, ev5PRIM_TYPE Type, ev5VERTEX *V, INT NoofV, INT *I, INT NoofI );
/***
 * Shader support functions
 ***/

/* Maximum resourse name size */
#define EV5_STR_MAX 300

/* Shader program store type */
typedef struct tagev5SHADER
{
  CHAR Name[EV5_STR_MAX]; /* Shader filename prefix */
  INT ProgId;             /* Shader program Id */
} ev5SHADER;

/* Shaders stock */
#define EV5_MAX_SHADERS 30                        /* Shaders stock size */
extern ev5SHADER EV5_RndShaders[EV5_MAX_SHADERS]; /* Array of shaders */
extern INT EV5_RndShadersSize;                    /* Shadres array store size */

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
VOID EV5_RndShdInit( VOID );

/* Shaders support dinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndShdClose( VOID );

/* Load shader program and add to stock function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader stock index.
 */
INT EV5_RndShdAdd( CHAR *ShaderFileNamePrefix );

/* Shaders stock update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndShdUpdate( VOID );

/***
 * Texture support functions
 ***/

/* Texture representation type */
typedef struct tagev5TEXTURE
{
  CHAR Name[EV5_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} ev5TEXTURE;

/* Textures stock */
#define EV5_MAX_TEXTURES 30                         /* Textures stock size */
extern ev5TEXTURE EV5_RndTextures[EV5_MAX_TEXTURES]; /* Array of textures */
extern INT EV5_RndTexturesSize;                     /* Textures array store size */

/* Textures support initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndTexInit( VOID );

/* Textures support deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndTexClose( VOID );

/* Add texture image to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - number of texture image components (3 or 4):
 *       INT C;
 *   - pointer to image pixel colors:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) add texture stock index.
 */
INT EV5_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );



/***
 * Material support functions
 ***/

/* Material store type */
typedef struct tagev5MATERIAL
{
  CHAR Name[EV5_STR_MAX]; /* Material name */
  INT ShdNo;              /* Shader number in shader array */

  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */
  FLT Trans;                /* Transparency factor */
  INT Tex[8];               /* Texture references from texture table */
} ev5MATERIAL;

/* Material stock */
#define EV5_MAX_MATERIALS 30                            /* Materials stock size */
extern ev5MATERIAL EV5_RndMaterials[EV5_MAX_MATERIALS]; /* Array of materials */
extern INT EV5_RndMaterialsSize;                        /* Materials array store size */

/* Materials support initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID EV5_RndMtlInit( VOID );

/* Add new material to stock function.
 * ARGUMENTS:
 *   - material description structure pointer:
 *       ev5MATERIAL *Mtl;
 * RETURNS:
 *   (INT) added material stock index.
 */
INT EV5_RndMtlAdd( ev5MATERIAL *Mtl );

/* Add new material to stock function.
 * ARGUMENTS:
 *   - material table number:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) applied material shader program Id.
 */
INT EV5_RndMtlApply( INT MtlNo );

/***
 * Primitive collections support
 ***/

/* Array of primitives representation type */
typedef struct tagev5PRIMS
{
  ev5PRIM *Prims; /* Primitive array */
  INT NumOfPrims; /* Primitive array size */
  MATR Trans;     /* All primitives transformation matrix */
} ev5PRIMS;

/* Create array of primitives function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       ev5PRIMS *Prs;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL EV5_RndPrimsCreate( ev5PRIMS *Prs, INT NoofP );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       ev5PRIMS *Prs;
 * RETURNS: None.
 */
VOID EV5_RndPrimsFree( ev5PRIMS *Prs );

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       ev5PRIMS *Prs;
 * RETURNS: None.
 */
VOID EV5_RndPrimsDraw( ev5PRIMS *Prs, MATR World );

/* Load array of primitives from G3DM file function.
 * ARGUMENTS:
 *   - primitive collection pointer:
 *       ev5PRIMS *Prs;
 *   - file name to load from:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL EV5_RndPrimsLoad( ev5PRIMS *Prs, CHAR *FileName );


#endif
/*End of RND.H*/