/* This file is part of VERTIGO.
 *
 * (C) Copyright 2013, Siege Technologies <http://www.siegetechnologies.com>
 * (C) Copyright 2013, Kirk Swidowski <http://www.swidowski.com>
 *
 * VERTIGO is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * VERTIGO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VERTIGO. If not, see <http://www.gnu.org/licenses/>.
 *
 * Written by Kirk Swidowski <kirk@swidowski.com>
 */

#include <defines.h>

#ifndef __SDWMOD_MAIN_H__
#define __SDWMOD_MAIN_H__

#ifdef __C__

result_t init_c(void);
result_t fini_c(void);

#endif //__C__

#ifdef __ASSEMBLY__

IMPORT init_asm
IMPORT fini_asm

IMPORT init_c
IMPORT fini_c

#endif //__ASSEMBLY__

#endif //__SDWMOD_MAIN_H__
