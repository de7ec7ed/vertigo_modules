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

#ifndef __LIN_PROC_H__
#define __LIN_PROC_H__

#include <defines.h>

#ifdef __C__

typedef unsigned int mode_t;
typedef unsigned long int nlink_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef long int loff_t;
typedef volatile int atomic_t;
typedef void * fl_owner_t;

typedef int (*read_proc_t)(char *buffer, char **location, loff_t offset, int length, int *eof, void *data);
typedef int (*write_proc_t)(void/*struct file*/ *file, const char /*__user*/ *buffer, unsigned long length, void *data);

struct proc_dir_entry {
	unsigned int low_ino;
	mode_t mode;
	nlink_t nlink;
	uid_t uid;
	gid_t gid;
	loff_t size;
	void /*const struct inode_operations*/ *proc_iops;
	struct file_operations *proc_fops;
	struct proc_dir_entry *next, *parent, *subdir;
	void *data;
	read_proc_t *read_proc;
	write_proc_t *write_proc;
	atomic_t count;		/* use count */
	//int pde_users;	/* number of callers into module in progress */
	//spinlock_t pde_unload_lock; /* proc_fops checks and pde_users bumps */
	//struct completion *pde_unload_completion;
	//struct list_head pde_openers;	/* who did ->open, but not ->release */
	//unsigned int namelen;
	//const char *name;

} PACKED;

#endif //__C__

#endif //__LIN_PROC_H__
