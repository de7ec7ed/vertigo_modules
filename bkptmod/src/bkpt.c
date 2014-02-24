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
#include <armv7lib/cmsa/cac.h>
#include <armv7lib/vmsa/gen.h>
#include <armv7lib/vmsa/flt.h>

#include <dbglib/gen.h>

#include <fxplib/gen.h>

#include <stdlib/check.h>
#include <stdlib/string.h>

#include <kernel/mas.h>
#include <kernel/mmu.h>

#include <bkptmod/bkpt.h>

DBG_DEFINE_VARIABLE(bkpt_dbg, DBG_LEVEL_3);


bkpt_handler_t *bkpt_handlers = NULL;

result_t bkpt_init(void) {

	DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(vec_register_handler(VEC_UNDEFINED_INSTRUCTION_VECTOR, gen_add_base(bkpt_und_handler), NULL), "unable to add vector handler", FAILURE, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t bkpt_patch(tt_virtual_address_t va, size_t *value) {

	tt_physical_address_t pa;
	size_t tmp;
	size_t *p;

	DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_EXTERNAL), "unable to switch the internal paging system", FAILURE, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(gen_va_to_pa(va, &pa), "va could not be translated", va.all, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("pa", pa.all, bkpt_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch the internal paging system", FAILURE, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	va.all = 0;

	CHECK_SUCCESS(mmu_map(pa, TT_SMALL_PAGE_SIZE, MMU_MAP_INTERNAL | MMU_MAP_NORMAL_MEMORY, &va), "unable to map pa", pa.all, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	p = (size_t *)va.all;

	DBG_LOG_STATEMENT("*value", *value, bkpt_dbg, DBG_LEVEL_3);

	tmp = *p;
	*p = *value;
	*value = tmp;

	DBG_LOG_STATEMENT("tmp", tmp, bkpt_dbg, DBG_LEVEL_3);

	cac_clean_cache_region(p, sizeof(*value));

	CHECK_SUCCESS(mmu_unmap(va, TT_SMALL_PAGE_SIZE, MMU_MAP_INTERNAL), "unable to unmap pa", va.all, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("p", p, bkpt_dbg, DBG_LEVEL_3);

	return SUCCESS;
}

result_t bkpt_register_handler(tt_virtual_address_t va, gen_program_status_register_t psr, bkpt_function_t function, void *data) {

	bkpt_handler_t **head;
	bkpt_handler_t *handler = NULL;

	DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	head = gen_add_base(&bkpt_handlers);

	handler = malloc(sizeof(bkpt_handler_t));

	CHECK_NOT_NULL(handler, "handler is null", handler, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("handler address", handler, bkpt_dbg, DBG_LEVEL_3);

	memset(handler, 0, sizeof(bkpt_handler_t));

	if(psr.fields.t == TRUE) {
		DBG_LOG_STATEMENT("BKPT_THUMB_BREAKPOINT_INSTRUCTION", BKPT_THUMB_BREAKPOINT_INSTRUCTION, bkpt_dbg, DBG_LEVEL_3);
		handler->value = BKPT_THUMB_BREAKPOINT_INSTRUCTION;
	}
	else {
		DBG_LOG_STATEMENT("BKPT_ARM_BREAKPOINT_INSTRUCTION", BKPT_ARM_BREAKPOINT_INSTRUCTION, bkpt_dbg, DBG_LEVEL_3);
		handler->value = BKPT_ARM_BREAKPOINT_INSTRUCTION;
	}

	CHECK_SUCCESS(bkpt_patch(va, &(handler->value)), "unable to patch the instruction", va.all, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	handler->prev = NULL;
	handler->va = va;
	handler->psr = psr;
	handler->function = function;
	handler->data = data;
	handler->next = *head;

	if(*head != NULL) {
		(*head)->prev = handler;
	}

	*head = handler;

	DBG_LOG_STATEMENT("handler->va.all", handler->va.all, bkpt_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->psr.all", handler->psr.all, bkpt_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->function", handler->function, bkpt_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->value", handler->value, bkpt_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->data", handler->data, bkpt_dbg, DBG_LEVEL_3);

	return SUCCESS;
}

result_t bkpt_lookup_handler(tt_virtual_address_t va, bkpt_handler_t **handler) {

	bkpt_handler_t **head;

	//DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	CHECK_NOT_NULL(handler, "handler is null", handler, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	head = gen_add_base(&bkpt_handlers);

	*handler = *head;

	while(*handler != NULL) {
		if((*handler)->va.all == va.all) {
			return SUCCESS;
		}
		*handler = (*handler)->next;
	}

	return FAILURE;
}

result_t bkpt_unregister_handler(bkpt_handler_t *handler) {

	bkpt_handler_t **head;

	DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	head = gen_add_base(&bkpt_handlers);

	CHECK_NOT_NULL(handler, "handler is null", handler, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("handler->va.all", handler->va.all, bkpt_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->function", handler->function, bkpt_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->value", handler->value, bkpt_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->data", handler->data, bkpt_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(bkpt_patch(handler->va, &(handler->value)), "unable to patch the instruction", handler->va.all, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	if(handler == *head) {
		*head = handler->next;
	}
	else {
		if(handler->prev != NULL) {
			handler->prev->next = handler->next;
		}

		if(handler->next != NULL) {
			handler->next->prev = handler->prev;
		}
	}

	free(handler);

	handler = handler->next;

	return SUCCESS;
}

result_t bkpt_dispatch_handler(tt_virtual_address_t va, bool_t *handled, gen_general_purpose_registers_t *registers) {

	//DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	bkpt_handler_t *handler = NULL;

	if(bkpt_lookup_handler(va, &handler) == SUCCESS) {
		CHECK_SUCCESS(handler->function(handler, registers), "handler returned failure", FAILURE, bkpt_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END
		*handled = TRUE;
	}

	return SUCCESS;
}

result_t bkpt_und_handler(vec_handler_t *handler, bool_t *handled, gen_general_purpose_registers_t *registers) {

	gen_program_status_register_t spsr;
	tt_virtual_address_t va;

	//DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	UNUSED_VARIABLE(handler);

	spsr = gen_get_spsr();

	if(spsr.fields.t == TRUE) {
		va.all = registers->lr - 2;
	}
	else {
		va.all = registers->lr - 4;
	}

	CHECK_SUCCESS(bkpt_dispatch_handler(va, handled, registers), "bkpt dispatch handler returned failure", va.all, bkpt_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t bkpt_fini(void) {

	bkpt_handler_t **head;
	bkpt_handler_t *tmp;

	DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	head = gen_add_base(&bkpt_handlers);

	CHECK_SUCCESS(vec_unregister_handler(VEC_UNDEFINED_INSTRUCTION_VECTOR, gen_add_base(bkpt_und_handler)), "unable to remove vector handler", FAILURE, bkpt_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	// free the linked list of handlers
	while(*head != NULL) {
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
	return SUCCESS;

}

result_t bkpt_get_debug_level(size_t *level) {

	DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	DBG_GET_VARIABLE(bkpt_dbg, *level);

	return SUCCESS;
}

result_t bkpt_set_debug_level(size_t level) {

	DBG_LOG_FUNCTION(bkpt_dbg, DBG_LEVEL_3);

	DBG_SET_VARIABLE(bkpt_dbg, level);

	return SUCCESS;
}
