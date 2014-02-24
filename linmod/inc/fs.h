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

#ifndef __LIN_FS_H__
#define __LIN_FS_H__

#include <defines.h>
#include <linmod/mm_types.h>

typedef long int loff_t;
typedef size_t ssize_t;

struct file_operations {
	void *owner;
	loff_t (*llseek) (void /*struct file*/ *, loff_t, int);
	ssize_t (*read) (void /*struct file*/ *, char *, size_t, loff_t *);
	ssize_t (*write) (void /*struct file*/ *, const char *, size_t, loff_t *);
	ssize_t (*aio_read) (void /*struct kiocb*/ *, void /*const struct iovec*/ *, unsigned long, loff_t);
	ssize_t (*aio_write) (void /*struct kiocb*/ *, void /*const struct iovec*/ *, unsigned long, loff_t);
	int (*readdir) (void /*struct file*/ *, void *, void */*filldir_t*/);
	unsigned int (*poll) (void /*struct file*/ *, void /*struct poll_table_struct*/ *);
	long (*unlocked_ioctl) (void /*struct file*/ *, unsigned int, unsigned long);
	long (*compat_ioctl) (void /*struct file*/ *, unsigned int, unsigned long);
	int (*mmap) (void /*struct file*/ *, struct vm_area_struct *);
	int (*open) (void /*struct inode*/ *, void /*struct file*/ *);
	int (*flush) (void /*struct file*/ *, fl_owner_t id);
	int (*release) (void /*struct inode*/ *, void /*struct file*/ *);
	int (*fsync) (void /*struct file*/ *, int datasync);
	int (*aio_fsync) (void /*struct kiocb*/ *, int datasync);
	int (*fasync) (int, void /*struct file*/ *, int);
	int (*lock) (void /*struct file*/ *, int, void /*struct file_lock*/ *);
	ssize_t (*sendpage) (void /*struct file*/ *, void /*struct page*/ *, int, size_t, loff_t *, int);
	unsigned long (*get_unmapped_area)(void /*struct file*/ *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (void /*struct file*/ *, int, void /*struct file_lock*/ *);
	ssize_t (*splice_write)(void /*struct pipe_inode_info*/ *, void /*struct file*/ *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(void /*struct file*/ *, loff_t *, void /*struct pipe_inode_info*/ *, size_t, unsigned int);
	int (*setlease)(void /*struct file*/ *, long, void /*struct file_lock*/ **);
	long (*fallocate)(void /*struct file*/ *file, int mode, loff_t offset, loff_t len);
} PACKED;

#endif //__LIN_FS_H__
