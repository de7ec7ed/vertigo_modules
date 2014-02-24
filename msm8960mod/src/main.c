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

#include <armv7lib/cpuid.h>

#include <dbglib/gen.h>

#include <fxplib/gen.h>

#include <stdlib/check.h>

#include <socmod/soc.h>
#include <socmod/main.h>
#include <socmod/scm.h>

#include <kernel/mmu.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_3);

result_t init_c(void) {

	cpuid_main_id_register_t midr;
	scm_boot_address_command_t bac;
	tt_virtual_address_t va;
	tt_physical_address_t pa;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_2);

	// check to make sure that this module
	// is only loaded on the correct SoC

	midr = cpuid_get_midr();

	DBG_LOG_STATEMENT("midr", midr.all, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("revision", midr.fields.revision, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("primary_part_number", midr.fields.primary_part_number, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("architecture", midr.fields.architecture, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("variant", midr.fields.variant, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("implementer", midr.fields.implementer, main_dbg, DBG_LEVEL_3);

	CHECK_EQUAL(midr.all, SOC_MIDR, "module is not compatible with this soc", midr.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	u32_t svc_cmd = (SCM_SERVICE_PIL << 10) | PAS_IS_SUPPORTED_CMD;
	u32_t ret_val = 0;
	size_t i;

	scm_exeucte_command(SCM_SERVICE_INFORMATION, SCM_IS_CALL_AVAILABLE, &svc_cmd, sizeof(svc_cmd), &ret_val, sizeof(ret_val));

	va.all = (u32_t)gen_add_base(&func);
	mmu_lookup_pa(va, &pa);
	bac.address = (void *)pa.all;
	bac.flags = (SCM_FLAG_WARMBOOT_CPU1);

	for(i = SCM_BOOT_ADDRESS_CMD; i < 0xF; i++) {
		DBG_LOG_STATEMENT("boot addr", scm_exeucte_command(SCM_SERVICE_BOOT, i, &bac, sizeof(bac), NULL, 0), main_dbg, DBG_LEVEL_3);
	}

	size_t *var;
	var = gen_add_base(&vari);

	DBG_LOG_STATEMENT("var", *var, main_dbg, DBG_LEVEL_3);

	return SUCCESS;
}

result_t fini_c(void) {

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_2);

	size_t *var;
	var = gen_add_base(&vari);

	DBG_LOG_STATEMENT("var", *var, main_dbg, DBG_LEVEL_3);


	return SUCCESS;
}
