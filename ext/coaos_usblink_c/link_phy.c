/*
 * link_phy_posix.c
 *
 *  Created on: Oct 6, 2012
 *      Author: tgil
 */


//#include "config.h"

#ifndef __macosx
#include "win32/link_phy_win32.c"
#else
#include "posix/link_phy_posix.c"
#endif


