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
#include <stdlib/string.h>

#include <kernel/mas.h>
#include <kernel/vec.h>

#include <socmod/uart.h>
#include <socmod/wdt.h>

DBG_DEFINE_VARIABLE(gdb_dbg, DBG_LEVEL_3);

size_t gdb_interval = 0;
size_t gdb_vector = VEC_UNDEFINED_INSTRUCTION_VECTOR;
gen_general_purpose_registers_t *gdb_registers =  NULL;
uart_block_t *gdb_uart_block = NULL;
wdt_block_t *gdb_wdt_block = NULL;

result_t gdb_init(void) {

	tt_physical_address_t pa;
	tt_virtual_address_t va;
	size_t size;

	DBG_LOG_FUNCTION(gdb_dbg, DBG_LEVEL_3);

	// initialize and disable the watchdog timer
	CHECK_SUCCESS(wdt_get_physical_address((void **)&(pa.all)), "unable to get the wdt physical address", FAILURE, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(wdt_get_size(&size), "unable to get the wdt size", FAILURE, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	va.all = 0;
	CHECK_SUCCESS(mmu_map(pa, size, MMU_MAP_INTERNAL | MMU_MAP_DEVICE_MEMORY, &va), "unable to map the wdt", pa.all, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	GEN_REFERENCE_GLOBAL(gdb_wdt_block) = (wdt_block_t *)(va.all);

	CHECK_SUCCESS(wdt_init(GEN_REFERENCE_GLOBAL(gdb_wdt_block), 0), "unable to initialize the wdt", FAILURE, gdb_dbg, DBG_LEVEL_3)
		CHECK_SUCCESS(mmu_unmap(va, size, MMU_MAP_INTERNAL), "unable to unmap the wdt", va.all, gdb_dbg, DBG_LEVEL_3) CHECK_END
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(wdt_disable(GEN_REFERENCE_GLOBAL(gdb_wdt_block)), "unable to disable the wdt", FAILURE, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(uart_get_physical_address(UART_DEFAULT, (void **)&(pa.all)), "unable to get the wdt physical address", FAILURE, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(wdt_get_size(UART_DEFAULT, &size), "unable to get the wdt size", FAILURE, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	va.all = 0;
	CHECK_SUCCESS(mmu_map(pa, size, MMU_MAP_INTERNAL | MMU_MAP_DEVICE_MEMORY, &va), "unable to map the wdt", pa.all, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	GEN_REFERENCE_GLOBAL(gdb_uart_block) = (uart_block_t *)(va.all);

	CHECK_SUCCESS(uart_init(GEN_REFERENCE_GLOBAL(gdb_wdt_block), 0), "unable to initialize the wdt", FAILURE, gdb_dbg, DBG_LEVEL_3)
		CHECK_SUCCESS(mmu_unmap(va, size, MMU_MAP_INTERNAL), "unable to unmap the wdt", va.all, gdb_dbg, DBG_LEVEL_3) CHECK_END
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(vec_register_handler(VEC_INTERRUPT_VECTOR, gen_add_base(gdb_interrupt_handler), NULL), "unable to register the interrupt handler", FAILURE, gdb_dbg, DGB_LEVEL_3)
		CHECK_SUCCESS(mmu_unmap(va, size, MMU_MAP_INTERNAL), "unable to unmap the wdt", va.all, gdb_dbg, DBG_LEVEL_3) CHECK_END
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t gdb_get_packet(u8_t command, size_t size) {

	result_t result;
	u8_t character;
	size_t checksum;
	size_t count;
	bool_t escaped;
	size_t tmp;

	do {
		result = uart_getc(GEN_REFERENCE_GLOBAL(gdb_uart_block), &character);

		// if no data is available return
		if(result == FAILURE) {return SUCCESS;}

	} while(character != '$');

	command[0] = character;

	checksum = 0;
	count = 1;
	escaped = FALSE;

	// retrieve the rest of the packet, size - 1 so we have room for the '\0' byte at the end
	while(count < (size - 1)) {

		uart_getc(GEN_REFERENCE_GLOBAL(gdb_uart_block), &character);

		if(escaped == FALSE) {
			if (character == '$') {
				checksum = 0;
				count = 0;
			} else if (character == '#')
				break;
			else if (character == GDB_ESCAPE_CHARACTER) {
				escaped = 1;
				checksum += character;
			} else {
				checksum += character;
				command[count] = character;
				count++;
			}
		} else {
			escaped = 0;
			checksum += character;
			command[count] = character ^ 0x20;
			count++;
		}
	}

	// put a null byte at the end of the packet
	command[count] = '\0';

	if(character == '#') {

		uart_getc(GEN_REFERENCE_GLOBAL(gdb_uart_block), &character);
		tmp = atoi(character) << 4;

		uart_getc(GEN_REFERENCE_GLOBAL(gdb_uart_block), &character);
		tmp += atoi(character);

		if((checksum & 0xff) != tmp) {
			put_byte('-');
			return FAILURE;
		}
		else {
			put_byte('+');
			return SUCCESS;
		}
	}
	else {
		return FAILURE;
	}
}

result_t gdb_put_packet(u8_t *command) {
    size_t i, checksum;
    u8_t character;
    u8_t ch;
    u8_t tmp[3];

    do {

    	CHECK_SUCCESS(uart_putc(GEN_REFERENCE_GLOBAL(gdb_uart_block), '$'), "unable to put character into the uart", FAILURE, gdb_dbg, DBG_LEVEL_3)
    			return FAILURE;
    	CHECK_END

        checksum = 0;
        for (i = 0; command[i] != '\0'; i++) {
            checksum += command[i];
        }

        CHECK_SUCCESS(uart_write(command, i), "unable to write buffer into the uart", FAILURE, gdb_dgb, DBG_LEVEL_3)
        	return FAILURE;
        CHECK_END

        tmp[0] = '#';
        itoa(checksum & 0xff, &(tmp[1]), 16);

        CHECK_SUCCESS(uart_write(tmp, sizeof(tmp)), "unable to write buffer into the uart", FAILURE, gdb_dgb, DBG_LEVEL_3)
			return FAILURE;
		CHECK_END

		uart_getc(GEN_REFERENCE_GLOBAL(gdb_uart_block), &character);

    } while (character != '+');

    return SUCCESS;
}

result_t gdb_vector_to_signal(size_t vector, size_t *signal) {

	if(vector == VEC_UNDEFINED_INSTRUCTION_VECTOR) {
		*signal = GDB_SIGTRAP;
	}
	else if(vector == VEC_PREFETCH_ABORT_VECTOR) {
		*signal = GDB_SIGABRT;
	}
	else if(vector == VEC_DATA_ABORT_VECTOR) {
		*signal = GDB_SIGABRT;
	}
	else if(vector == VEC_INTERRUPT_VECTOR) {
		*signal = GDB_SIGINT;
	}
	else if(vector == VEC_FAST_INTERRUPT_VECTOR) {
		*signal = GDB_SIGINT;
	}
	else {
		*signal = GDB_SIGQUIT;
		DBG_LOG_STATEMENT("unable to translate vector to signal", vector, gdb_dbg, DBG_LEVEL_3);
		return FAILURE;
	}

	return SUCCESS;
}

result_t gdb_parse_packet(u8_t *command, size_t size) {
	u8_t response[GDB_RESPONSE_SIZE];

	if(command[0] == '?') {
		CHECK_SUCCESS(gdb_vector_to_signal(GEN_REFERENCE_GLOBAL(gdb_vector), &signal), "unable to translate vector to signal", GEN_REFERENCE_GLOBAL(gdb_vector), gdb_dbg, DBG_LEVEL_3)
			return FAILURE;
		CHECK_END
		//reply_signal(gdb_exception_no, reply_buf);
	}
	else if(command[0] == 'p') {
		//cmd_get_register(packet_buf + 1, reply_buf);
	}
	else if(command[0] == 'P') {
		//cmd_set_register(packet_buf + 1, reply_buf);
	}
	else if(command[0] == 'g') {
		//g_reply(reply_buf);
	}
	else if(command[0] == 'G') {
		 //cmd_set_registers(packet_buf + 1, reply_buf);
	}
	else if(command[0] == 'm') {
		//cmd_get_memory(packet_buf + 1, reply_buf);
	}
	else if(command[0] == 'M') {
		//cmd_put_memory(packet_buf + 1, reply_buf);
	}
	else if(command[0] == 'X') {
		//cmd_put_memory_binary(packet_buf + 1, reply_buf);
	}
	else if(command[0] == 'q') {
		//cmd_query(packet_buf + 1, reply_buf);
	}
	else if(command[0] == 'c') {
		//cmd_go(packet_buf + 1);
		//reply_error(1, reply_buf);
	}
	else if(command[0] == 's') {
		// step here
		//cmd_go(packet_buf + 1);
		//reply_error(1, reply_buf);
	}
	else {
		response[0] = '/0';
	}

	CHECK_SUCCESS(gdb_put_packet(response), "unable to send response", FAILURE, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t gdb_loop(void) {

	u8_t character;
	u8_t command[GDB_COMMAND_SIZE];

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch paging systems", MMU_SWITCH_INTERNAL, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	((bool_t)GEN_REFERENCE_GLOBAL(gdb_continue)) = FALSE;

	while(((bool_t)GEN_REFERENCE_GLOBAL(gdb_continue)) == FALSE) {

		// check to see if there are any commands available
		CHECK_SUCCESS(gdb_get_packet(command, sizeof(command)), "unable to get command packet", FAILURE, gdb_dbg, DBG_LEVEL_3)
			return SUCCESS;
		CHECK_END

		// parse the command that was received
		CHECK_SUCCESS(gdb_parse_packet(command, sizeof(command)), "unable to parse command packet", FAILURE, gdb_dbg, DBG_LEVEL_3)
			return SUCCESS;
		CHECK_END
	}

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_EXTERNAL), "unable to switch paging systems", MMU_SWITCH_INTERNAL, gdb_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t gdb_interrupt_handler(vec_handler_t *handler, bool_t *handled, gen_general_purpose_registers_t *registers) {

	size_t *interval;

	DBG_LOG_FUNCTION(gdb_dbg, DBG_LEVEL_3);


	((size_t)GEN_REFERENCE_GLOBAL(gdb_interval))++;

	if(*interval == GDB_COMMAND_INTERVAL) {

		// reset the command interval
		((size_t)GEN_REFERENCE_GLOBAL(gdb_interval)) = 0;

		// set the registers pointer
		((gen_general_purpose_registers_t *)GEN_REFERENCE_GLOBAL(gdb_registers)) = registers;
		((size_t)GEN_REFERENCE_GLOBAL(gdb_vector)) = VEC_INTERRUPT_VECTOR;

		CHECK_SUCCESS(gdb_loop(), "gdb loop returned failure", FAILURE, gdb_dbg, DBG_LEVEL_3)
			CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_EXTERNAL), "unable to switch paging systems", MMU_SWITCH_INTERNAL, gdb_dbg, DBG_LEVEL_3) CHECK_END
			return FAILURE;
		CHECK_END
	}

	return SUCCESS;
}
