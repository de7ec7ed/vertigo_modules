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

#ifndef __MSM8960_SCM_H__
#define __MSM8960_SCM_H__

#include <armv7lib/vmsa/tt.h>

#define PAS_INIT_IMAGE_CMD        0x1
#define PAS_AUTH_AND_RESET_CMD    0x5
#define PAS_SHUTDOWN_CMD          0x6
#define PAS_IS_SUPPORTED_CMD      0x7

#define SCM_BOOT_ADDRESS_CMD        0x1
#define SCM_FLAG_COLDBOOT_CPU1      0x01
#define SCM_FLAG_COLDBOOT_CPU2      0x08
#define SCM_FLAG_COLDBOOT_CPU3      0x20
#define SCM_FLAG_WARMBOOT_CPU1      0x02
#define SCM_FLAG_WARMBOOT_CPU0      0x04
#define SCM_FLAG_WARMBOOT_CPU2      0x10
#define SCM_FLAG_WARMBOOT_CPU3      0x40

#define SCM_SERVICE_BOOT           0x1
#define SCM_SERVICE_PIL            0x2
#define SCM_SERVICE_UTILITIES      0x3
#define SCM_SERVICE_TRUST_ZONE     0x4
#define SCM_SERVICE_IO             0x5
#define SCM_SERVICE_INFORMATION    0x6
#define SCM_SERVICE_SSD            0x7
#define SCM_SERVICE_FUSE           0x8
#define SCM_SERVICE_POWER          0x9
#define SCM_SERVICE_CP             0xC
#define SCM_SERVICE_DCVS           0xD
#define SCM_SERVICE_SCHEDULER     0xFC

// result_t codes
#define SCM_NO_MEMORY                -5
#define SCM_OPERATION_NOT_SUPPORTED  -4
#define SCM_INVALID_ADDRRESS         -3
#define SCM_INVALID_ARGUMENT         -2
#define SCM_ERROR                    -1
#define SCM_INTERRUPTED               1

#define SCM_IS_CALL_AVAILABLE         1

#ifdef __C__

typedef struct scm_command scm_command_t;
typedef struct scm_response scm_response_t;
typedef struct scm_boot_address_command scm_boot_address_command_t;

// An SCM command is laid out in memory as follows:
//
//	------------------- <--- scm_command_t
//	| command header  |
//	------------------- <--- scm_get_command_buffer()
//	| command buffer  |
//	------------------- <--- scm_response_t and scm_command_to_response()
//	| response header |
//	------------------- <--- scm_get_response_buffer()
//	| response buffer |
//	-------------------
//
// There can be arbitrary padding between the headers and buffers so
// you should always use the appropriate scm_get_*_buffer() routines
// to access the buffers in a safe manner.

struct scm_command {
		u32_t length;
		u32_t buffer_offset;
		u32_t response_header_offset;
		u32_t id;
} PACKED;

struct scm_response {
	u32_t length;
	u32_t buffer_offset;
	u32_t finished;
} PACKED;

struct scm_boot_address_command {
	unsigned int flags;
	void *address;
} PACKED;

result_t scm_exeucte_command(u32_t svc_id, u32_t cmd_id, const void *cmd_buf, size_t cmd_len, void *resp_buf, size_t resp_len);

result_t scm_call_c(scm_command_t *cmd);

result_t scm_call_asm(size_t *id, tt_physical_address_t pa);

result_t scm_get_response(scm_command_t *cmd, scm_response_t **resp);

result_t scm_get_command_buffer(scm_command_t *cmd, void **buffer);

result_t scm_get_response_buffer(scm_command_t *cmd, void **buffer);

result_t scm_command_init(size_t cmd_size, size_t resp_size, scm_command_t **cmd);

result_t scm_command_fini(scm_command_t *cmd);

#endif //__C__

#ifdef __ASSEMBLY__

.extern smc_call_asm

#endif //__ASSEMBLY__

#endif //__MSM8960_SCM_H__
