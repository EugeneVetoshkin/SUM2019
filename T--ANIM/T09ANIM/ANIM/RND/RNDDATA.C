/* FILE NAME   : DATA.C
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Vetoshkin Eugene.
* LAST UPDATE : 10.06.2019.
* NOTE        : Module prefix 'EV5'.
*/

#include "../../DEF.H"

#define GLEW_STATIC
#include <glew.h>
#pragma comment(lib, "glew32")
#pragma comment(lib, "glew32s")
#pragma comment(lib, "opengl32")

INT EV5_RndCounterPrims, EV5_triangles;
DBL
EV5_RndProjSize = 0.1,  /* Project plane fit square */
EV5_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
EV5_RndProjFarClip = 1000;  /* Distance to project far clip plane (far) */

MATR
EV5_RndMatrView, /* View coordinate system matrix */
EV5_RndMatrProj, /* Projection coordinate system matrix */
EV5_RndMatrVP;   /* Stored (View * Proj) matrix */

/*End of RNDDATA.C*/