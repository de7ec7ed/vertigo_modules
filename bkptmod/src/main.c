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

#include <bkptmod/main.h>
#include <bkptmod/bkpt.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_3);

result_t init_c(void) {

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(bkpt_init(), "unable to initialize the breakpoint module", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t fini_c(void) {

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(bkpt_fini(), "unable to finish the breakpoint module", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}
