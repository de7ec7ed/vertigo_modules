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

#include <armv7lib/cmsa/cac.h>
#include <armv7lib/vmsa/tt.h>

#include <dbglib/gen.h>

#include <fxplib/gen.h>

#include <stdlib/check.h>
#include <stdlib/string.h>

#include <kernel/mas.h>
#include <kernel/mmu.h>

#include <socmod/scm.h>


DBG_DEFINE_VARIABLE(scm_dbg, DBG_LEVEL_3);

result_t scm_exeucte_command(u32_t svc_id, u32_t cmd_id, const void *cmd_buf, size_t cmd_len, void *resp_buf, size_t resp_len) {

	scm_command_t *cmd;
	scm_response_t *resp;
	void *tmp;

	CHECK_SUCCESS(scm_command_init(cmd_len, resp_len, &cmd), "unable to init the cmd", FAILURE, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("cmd->id", cmd->id, scm_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("cmd->response_header_offset", cmd->response_header_offset, scm_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("cmd->buffer_offset", cmd->buffer_offset, scm_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("cmd->length", cmd->length, scm_dbg, DBG_LEVEL_3);

	// create a unique id by combining a service id and command id
	cmd->id = (svc_id << 10) | cmd_id;

	CHECK_NOT_NULL(cmd_buf, "cmd_buf is null", cmd_buf, scm_dbg, DBG_LEVEL_3)
		scm_command_fini(cmd);
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(scm_get_command_buffer(cmd, &tmp), "scm_get_command_buffer returned failure", FAILURE, scm_dbg, DBG_LEVEL_3)
		scm_command_fini(cmd);
		return FAILURE;
	CHECK_END

	memcpy(tmp, cmd_buf, cmd_len);

	CHECK_SUCCESS(scm_call_c(cmd), "scm_call_c returned failure", FAILURE, scm_dbg, DBG_LEVEL_3)
		scm_command_fini(cmd);
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(scm_get_response(cmd, &resp), "unable to get resp from cmd", FAILURE, scm_dbg, DBG_LEVEL_3)
		scm_command_fini(cmd);
		return FAILURE;
	CHECK_END

	cac_flush_entire_data_cache();

	CHECK_NOT_NULL(resp_buf, "resp_buf is null", resp_buf, scm_dbg, DBG_LEVEL_3)
		scm_command_fini(cmd);
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(scm_get_response_buffer(cmd, &tmp), "scm_get_command_buffer returned failure", FAILURE, scm_dbg, DBG_LEVEL_3)
		scm_command_fini(cmd);
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("resp->finished", resp->finished, scm_dbg, DBG_LEVEL_3);

	do {
		cac_flush_entire_data_cache();
	} while (!resp->finished);

	memcpy(resp_buf, tmp, resp_len);

	scm_command_fini(cmd);

	return SUCCESS;
}

result_t scm_call_c(scm_command_t *cmd) {

	tt_virtual_address_t va;
	tt_physical_address_t pa;
	result_t result;
	size_t id = 0;

	DBG_LOG_FUNCTION(scm_dbg, DBG_LEVEL_3);

	CHECK_NOT_NULL(cmd, "cmd is null", cmd, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	va.all = (size_t)cmd;

	CHECK_SUCCESS(mmu_lookup_pa(va, &pa), "unable to lookup pa", va.all, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	cac_flush_entire_data_cache();

	do {
		result = scm_call_asm(&id, pa);
	} while(result == SCM_INTERRUPTED);

	return result;
}

result_t scm_get_response(scm_command_t *cmd, scm_response_t **resp) {

	DBG_LOG_FUNCTION(scm_dbg, DBG_LEVEL_3);

	CHECK_NOT_NULL(cmd, "cmd is null", cmd, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_NOT_NULL(resp, "resp is null", resp, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	*resp = (scm_response_t *)((size_t)cmd + cmd->response_header_offset);

	return SUCCESS;
}

result_t scm_get_command_buffer(scm_command_t *cmd, void **buffer) {

	DBG_LOG_FUNCTION(scm_dbg, DBG_LEVEL_3);

	CHECK_NOT_NULL(cmd, "cmd is null", cmd, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	*buffer = (void *)((size_t)cmd + cmd->buffer_offset);

	return SUCCESS;
}
result_t scm_get_response_buffer(scm_command_t *cmd, void **buffer) {

	scm_response_t *resp;

	DBG_LOG_FUNCTION(scm_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(scm_get_response(cmd, &resp), "failed to get the resp", FAILURE, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	*buffer = (void *)((size_t)resp + resp->buffer_offset);

	return SUCCESS;
}

result_t scm_command_init(size_t cmd_size, size_t resp_size, scm_command_t **cmd) {

	size_t length;

	DBG_LOG_FUNCTION(scm_dbg, DBG_LEVEL_3);

	length = sizeof(scm_command_t) + cmd_size + sizeof(scm_response_t) + resp_size;

	CHECK_NOT_NULL(cmd, "cmd is null", cmd, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	*cmd = memalign(FOUR_KILOBYTES, length);

	CHECK_NOT_NULL(*cmd, "*cmd is null", *cmd, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	memset(*cmd, 0, length);

	(*cmd)->length = length;
	(*cmd)->buffer_offset = sizeof(scm_command_t);
	(*cmd)->response_header_offset = (*cmd)->buffer_offset + cmd_size;

	return SUCCESS;
}

result_t scm_command_fini(scm_command_t *cmd) {

	DBG_LOG_FUNCTION(scm_dbg, DBG_LEVEL_3);

	CHECK_NOT_NULL(cmd, "cmd is null", cmd, scm_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	free(cmd);

	return SUCCESS;
}
