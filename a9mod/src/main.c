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

#include <a9mod/main.h>
#include <a9mod/gen.h>
#include <a9mod/vmsa/gen.h>

#include <armv7lib/vmsa/tt.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_3);

result_t init_c(void) {

	gen_auxiliary_control_register_t actlr;
	gen_non_secure_access_control_register_t nsacr;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	actlr = gen_get_actlr();
	DBG_LOG_STATEMENT("actlr", actlr.all, main_dbg, DBG_LEVEL_3);

	nsacr = gen_get_nsacr();
	DBG_LOG_STATEMENT("nsacr", nsacr.all, main_dbg, DBG_LEVEL_3);

	return SUCCESS;
}

result_t fini_c(void) {

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	return SUCCESS;
}
