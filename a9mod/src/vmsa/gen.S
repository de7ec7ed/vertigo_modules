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

#include <config.h>
#include <defines.h>

FUNCTION(gen_get_actlr)
    mrc p15, 0, r0, c1, c0, 1 // Read CP15 Auxiliary Control Register
    mov pc, lr

FUNCTION(gen_set_actlr)
    mcr p15, 0, r0, c1, c0, 1 // Write CP15 Auxiliary Control Register
    mov pc, lr

FUNCTION(gen_get_nsacr)
    mrc p15, 0, r0, c1, c1, 2 // Read CP15 Non-secure Access Control Register
    mov pc, lr

FUNCTION(gen_set_nsacr)
    mcr p15, 0, r0, c1, c2, 2 // Write CP15 Non-secure Access Control Register
    mov pc, lr
