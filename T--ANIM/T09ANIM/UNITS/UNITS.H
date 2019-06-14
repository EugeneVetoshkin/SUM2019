/* FILE NAME   : UNITS.H
* PURPOSE     : WinAPI animation system.
*               Base definitions.
* PROGRAMMER  : Vetoshkin Eugene
* LAST UPDATE : 10.06.2019.
* NOTE        : Module prefix 'EV5'.
*/
#ifndef __UNITS_H_
#define __UNITS_H_

#include "../anim/anim.h"

/* Giorno_Giovanna unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ev5UNIT *) pointer to created unit.
 */
ev5UNIT * EV5_UnitGiorno_GiovannaCreate( VOID );
ev5UNIT * EV5_UnitTextCreate( VOID );
ev5UNIT * EV5_UnitCowCreate( VOID );

#endif 