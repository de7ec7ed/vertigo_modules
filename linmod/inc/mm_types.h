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

#ifndef __LIN_MM_TYPES_H__
#define __LIN_MM_TYPES_H__

#include <defines.h>

#define VM_READ         0x00000001      /* currently active flags */
#define VM_WRITE        0x00000002
#define VM_EXEC         0x00000004
#define VM_SHARED       0x00000008

#ifdef __C__

typedef unsigned long pteval_t;

typedef struct { pteval_t pte; } pte_t;

typedef struct { unsigned long pgprot; } pgprot_t;

struct list_head {
	struct list_head *next, *prev;
} PACKED;

struct raw_prio_tree_node {
	void /*struct prio_tree_node*/ *left;
	void /*struct prio_tree_node*/ *right;
	void /*struct prio_tree_node*/ *parent;
} PACKED;

struct rb_node {
	unsigned long  rb_parent_color;
	#define RB_RED          0
	#define RB_BLACK        1
	struct rb_node *rb_right;
	struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long)))) PACKED;

struct vm_area_struct {
	void /*struct mm_struct*/ * vm_mm;       /* The address space we belong to. */
	unsigned long vm_start;         /* Our start address within vm_mm. */
	unsigned long vm_end;           /* The first byte after our end address within vm_mm. */
	struct vm_area_struct *vm_next, *vm_prev; /* linked list of VM areas per task, sorted by address */
	pgprot_t vm_page_prot;          /* Access permissions of this VMA. */
	unsigned long vm_flags;         /* Flags, see mm.h. */
	struct rb_node vm_rb;
	union {
		struct {
			struct list_head list;
    		void *parent;   /* aligns with prio_tree_node parent */
    		struct vm_area_struct *head;
    	} vm_set;
    	struct raw_prio_tree_node prio_tree_node;
	} shared;
	struct list_head anon_vma_chain; /* Serialized by mmap_sem & * page_table_lock */
	void /*struct anon_vma*/ *anon_vma;      /* Serialized by page_table_lock */
	struct vm_operations_struct *vm_ops; /* Function pointers to deal with this struct. */
	unsigned long vm_pgoff;         /* Offset (within vm_file) in PAGE_SIZE units, *not* PAGE_CACHE_SIZE */
	void /*struct file*/ * vm_file;          /* File we map to (can be NULL). */
	void * vm_private_data;         /* was vm_pte (shared mem) */
} PACKED;

struct vm_operations_struct {
	void (*open)(struct vm_area_struct * area);
	void (*close)(struct vm_area_struct * area);
	void (*unmap)(struct vm_area_struct *area, unsigned long, size_t);
	void (*protect)(struct vm_area_struct *area, unsigned long, size_t, unsigned int newprot);
	int (*sync)(struct vm_area_struct *area, unsigned long, size_t, unsigned int flags);
	void (*advise)(struct vm_area_struct *area, unsigned long, size_t, unsigned int advise);
	unsigned long (*nopage)(struct vm_area_struct * area, unsigned long address, int write_access);
	unsigned long (*wppage)(struct vm_area_struct * area, unsigned long address, unsigned long page);
	int (*swapout)(struct vm_area_struct *,  unsigned long, pte_t *);
	pte_t (*swapin)(struct vm_area_struct *, unsigned long, unsigned long);
} PACKED;

#endif //__C__

#endif //__LIN_MM_TYPES_H__
