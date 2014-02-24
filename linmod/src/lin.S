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
#include <linmod/lin.h>


LIN_ASM_FUNCTION printk, 0x804f7980
LIN_ASM_FUNCTION call_usermodehelper_setup, 0x80042f60
LIN_ASM_FUNCTION call_usermodehelper_exec, 0x800432c0
LIN_ASM_FUNCTION schedule, 0x804fdff4
LIN_ASM_FUNCTION create_proc_entry, 0x80141f20
LIN_ASM_FUNCTION remove_proc_entry, 0x80142200
LIN_ASM_FUNCTION remap_pfn_range, 0x800d6560
LIN_ASM_FUNCTION kmalloc, 0x7f0fb17c
LIN_ASM_FUNCTION kfree, 0x800ed52c
