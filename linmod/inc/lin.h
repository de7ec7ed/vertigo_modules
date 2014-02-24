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

#ifndef __LIN_H__
#define __LIN_H__

#include <defines.h>
#include <linmod/proc.h>
#include <linmod/mm_types.h>

#define LIN_KERNEL_SEARCH_ADDRESS 0x7f000000
#define LIN_KERNEL_SEARCH_SIZE     0x1500000
#ifdef __C__

typedef enum {
	UMH_NO_WAIT   = 0,       /* don't wait at all */
	UMH_WAIT_EXEC = 1,       /* wait for the exec, but not the process */
	UMH_WAIT_PROC = 2,       /* wait for the process to complete */
	UMH_KILLABLE  = 4,       /* wait for EXEC/PROC killable */
} umh_wait_t;


typedef enum {
	GFP_KERNEL = 0,
	GFP_ATOMIC = 1,
} gfp_t;


#define LIN_C_FUNCTION(name)            \
	extern void *lin_address_ ## name;

result_t lin_init(void);

result_t lin_fini(void);

result_t lin_find_function(void *start, size_t size, u8_t *signature, size_t signature_size, void **address);

LIN_C_FUNCTION(printk)
extern int lin_printk(/* const char *fmt, ...*/);

LIN_C_FUNCTION(call_usermodehelper_setup)
extern void /*struct subprocess_info*/ * lin_call_usermodehelper_setup(char *path, char **argv, char **envp, gfp_t gfp_mask);

LIN_C_FUNCTION(call_usermodehelper_exec)
extern int lin_call_usermodehelper_exec(void /*struct subprocess_info */*sub_info, umh_wait_t wait);

LIN_C_FUNCTION(schedule)
extern void lin_schedule(void);

LIN_C_FUNCTION(create_proc_entry)
struct proc_dir_entry *lin_create_proc_entry(const char *name, mode_t mode, struct proc_dir_entry *parent);

LIN_C_FUNCTION(remove_proc_entry)
void lin_remove_proc_entry(const char *name, struct proc_dir_entry *parent);

LIN_C_FUNCTION(remap_pfn_range)
int lin_remap_pfn_range(struct vm_area_struct * vma, unsigned long addr, unsigned long pfn, unsigned long size, pgprot_t prot);

LIN_C_FUNCTION(kmalloc)
void * lin_kmalloc (size_t size, int flags);

LIN_C_FUNCTION(kfree)
void lin_kfree(const void * objp);

extern result_t lin_get_printk_address(void **address);
extern result_t lin_get_call_usermodehelper_setup_address(void **address);
extern result_t lin_get_call_usermodehelper_exec_address(void **address);
extern result_t lin_get_schedule_address(void **address);
extern result_t lin_get_create_proc_entry_address(void **address);
extern result_t lin_get_remove_proc_entry_address(void **address);
extern result_t lin_get_remap_pfn_range_address(void **address);
extern result_t lin_get_kmalloc_address(void **address);
extern result_t lin_get_kfree_address(void **address);



extern result_t lin_get_debug_level(size_t *level);
extern result_t lin_set_debug_level(size_t level);

#endif //__C__

#ifdef __ASSEMBLY__

#define LIN_C_FUNCTION(name)				\
	.extern lin_ ## name

.macro LIN_ASM_FUNCTION name, address

// the address of function
VARIABLE(lin_address_\name) .word \address

FUNCTION(lin_\name)
	push {r0}

	ldr r0, lin_address_\name

	// execute the function if
	// its address is not null
	cmp r0, $0

	pop {r0}

	beq 1f

	ldr pc, lin_address_\name

	// will only get here if the
	// function address is null
	1:
	mov pc, lr

.endm

LIN_C_FUNCTION(printk)
LIN_C_FUNCTION(call_usermodehelper_setup)
LIN_C_FUNCTION(call_usermodehelper_exec)
LIN_C_FUNCTION(schedule)
LIN_C_FUNCTION(create_proc_entry)
LIN_C_FUNCTION(remove_proc_entry)
LIN_C_FUNCTION(remap_pfn_range)
LIN_C_FUNCTION(kmalloc)
LIN_C_FUNCTION(kfree)

#endif //__ASSEMBLY__

#endif //__LIN_H__
