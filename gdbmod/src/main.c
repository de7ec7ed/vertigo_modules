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

#include <fxplib/gen.h>

#include <dbglib/gen.h>

#include <stdlib/check.h>

#include <kernel/mas.h>
#include <kernel/vec.h>

#include <socmod/wdt.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_3);

result_t init_c(void) {

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	// disable the watchdog timer as we are going to be waiting
	// for the gdb server to communicate a bunch

	CHECK_SUCCESS(gdb_init(), "unable to initialize gdb", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END


	// first things first

	// we need to register for breakpoints and watchpoints
	// but this is done as they are set. we need to set one here
	// i think it can be anywhere in the kernel is fine or just wait for a command
	// not sure gdb assumes a breakpoint,

	// maybe just register for interrupts and filter for the uart rx interrupt

	// yeah just register for the rx interrupt and then resume the system.

	//the rx interrupt handler will implement the command logic / parser

	// the remote debugger will be responsible for sending the first command to set a
	// breakpoint

	// we need a generic way to access the rx interrupt and register for it SoC independence

	// SoC should have all the logic for the UART and the ability to check for the interrupt
	// the SoC may need the GIC to access the mmio effectively

	// so module requirements:
	//  -- SoC (don't think the GIC is required as the UART contains all the bits to do the things :)
	//  -- Breakpoint module
	// -- (maybe) Shadow Paging module (future to trap on memory access or modification

	// what device should be done first the SIII or iPhone 4.
	// -- iOS is maybe more impressive, because debuggers are rather limited, but its an older device
	// -- SIII because it could be used as a trustzone debugger once, access is gained. but in general
	// -- Android is Open Souced and better understood, especially if you can just flash you own kernel
	// with KDB in it.

	return SUCCESS;
}

result_t fini_c(void) {

	return SUCCESS;
}

