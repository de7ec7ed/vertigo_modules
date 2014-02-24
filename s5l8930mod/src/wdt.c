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

#include <defines.h>
#include <types.h>

#include <socmod/wdt.h>

// iBoot and LLB usage of the wdt on iPhone3,1_5.0_9A334_Restore

// RAM:5FF092E8 sub_5FF092E8                            ; CODE XREF: sub_5FF190DC+Ep
// RAM:5FF092E8                 MOVW            R0, #0x202C
// RAM:5FF092EC                 MOVW            R2, #0x2024
// RAM:5FF092F0                 MOVT.W          R0, #0xBF10
// RAM:5FF092F4                 MOVS            R1, #0
// RAM:5FF092F6                 MOVT.W          R2, #0xBF10
// RAM:5FF092FA                 MOVS            R3, #1
// RAM:5FF092FC                 STR             R1, [R0]
// RAM:5FF092FE                 STR             R3, [R2]
// RAM:5FF09300                 MOV             R2, 0xBF102020
// RAM:5FF09308                 MOV.W           R3, #0x80000000
// RAM:5FF0930C                 STR             R3, [R2]
// RAM:5FF0930E                 MOVS            R3, #4
// RAM:5FF09310                 STR             R3, [R0]
// RAM:5FF09312                 STR             R1, [R2]
// RAM:5FF09314                 BX              LR
// RAM:5FF09314 ; End of function sub_5FF092E8

// u32_t *wtcon = 0xBF10202C;
// u32_t *wtrstdat = 0xBF102024;
// *wtcon = 0;                 // disable the watchdog
// *wtrstdat = 1;                 // set the tigger value
// u32_t *wtcnt = 0xBF102020;
// *wtcnt = 0x80000000;        // turn off the counter ???
// *wtcon = 4;                 // enable the watchdog, reset enable
// *wtcnt = 0;                 // turn on the counter ???
// this set of code effectively tells the wdt to count up t 1 from 0x8000000 and reset if it gets there

// RAM:5FF09318 sub_5FF09318                            ; CODE XREF: sub_5FF18838+6Cp
// RAM:5FF09318                 MOVW            R0, #0x202C
// RAM:5FF0931C                 MOVW            R2, #0x2024
// RAM:5FF09320                 MOVW            R3, #0x5000
// RAM:5FF09324                 MOVT.W          R0, #0xBF10
// RAM:5FF09328                 MOVS            R1, #0
// RAM:5FF0932A                 MOVT.W          R2, #0xBF10
// RAM:5FF0932E                 MOVT.W          R3, #0xABA9
// RAM:5FF09332                 STR             R1, [R0]
// RAM:5FF09334                 STR             R3, [R2]
// RAM:5FF09336                 MOV             R2, 0xBF102020
// RAM:5FF0933E                 MOV.W           R3, #0x80000000
// RAM:5FF09342                 STR             R3, [R2]
// RAM:5FF09344                 MOVS            R3, #0xC
// RAM:5FF09346                 STR             R3, [R0]
// RAM:5FF09348                 STR             R1, [R2]
// RAM:5FF0934A                 BX              LR
// RAM:5FF0934A ; End of function sub_5FF09318

// u32_t *wtcon = 0xbf10202c;
// u32_t *wtrstdat = 0xbf102024;
// *wtcon = 0;                  // disable the watchdog
// *wtrstdat = 0xABA95000;         // set a trigger value
// u32_t *wtcnt = 0xBF102020;
// *wtcnt = 0x80000000;         // stop the counter ???
// *wtcon = 0xC;                // enable the watchdog, reset and interrupt enable
// *wtcnt = 0;                  // start the counter ???
// this set of code effectively tells the wdt to count from 0x80000000 to 0xABA95000 and then trigger a reset
// bit 0x8 in wtcon is still not certain

// dynamic analysis with vertigo shows
// addresses : 0x0
// &wtirqdat : 0xc0000028
// &wtcon : 0xc000002c
// &wtrstdat : 0xc0000024
// &wtcnt : 0xc0000020
// values before : 0x0
// wtirqdatint : 0x7270e00
// wtcon : 0xd
// wtrstdat : 0xe4e1c00
// wtcnt : 0xafcd6b
// [%]watchdog timer disabled : 0x0
// values after : 0x0
// wtirqdat : 0x0
// wtcon : 0x0
// wtrstdat : 0x0
// wtcnt : 0x1fa8c

// if vertigo is thrown into a while 1 loop and just
// prints out wtcnt the device restarts after it
// exceeds 0xe545a88

// the values printed after the "watchdog timer disable" string
// does successfully disable the wdt

result_t wdt_init(wdt_block_t *block, size_t options) {

	UNUSED_VARIABLE(options);

	block->wtcon.all = 0;
	block->wtintdat.all = 0;
	block->wtrstdat.all = 0;
	block->wtcnt.all = 0;

	return SUCCESS;
}

result_t wdt_fini(wdt_block_t *block) {

	// TODO: maybe restore the state of the watchdog

	UNUSED_VARIABLE(block);

	return SUCCESS;
}

result_t wdt_acknowledge_interrupt(wdt_block_t *block) {

	if(block == NULL) {
		return FAILURE;
	}

	block->wtcon.fields.ic = TRUE;

	return SUCCESS;
}

result_t wdt_interrupt_disable(wdt_block_t *block) {

	if(block == NULL) {
		return FAILURE;
	}

	block->wtcon.fields.ie = FALSE;

	return SUCCESS;
}

result_t wdt_interrupt_enable(wdt_block_t *block) {

	if(block == NULL) {
		return FAILURE;
	}

	block->wtcon.fields.ie = TRUE;

	return SUCCESS;
}

result_t wdt_reset_disable(wdt_block_t *block) {

	if(block == NULL) {
		return FAILURE;
	}

	block->wtcon.fields.re = FALSE;

	return SUCCESS;
}

result_t wdt_reset_enable(wdt_block_t *block) {

	if(block == NULL) {
		return FAILURE;
	}

	block->wtcon.fields.re = TRUE;

	return SUCCESS;
}

result_t wdt_get_reset_data(wdt_block_t *block, size_t *data) {

	if(block == NULL) {
		return FAILURE;
	}

*data = block->wtrstdat.all;

	return SUCCESS;
}

result_t wdt_set_reset_data(wdt_block_t *block, size_t data) {

	if(block == NULL) {
		return FAILURE;
	}

	block->wtrstdat.all = data;

	return SUCCESS;
}

result_t wdt_get_interrupt_data(wdt_block_t *block, size_t *data) {

	if(block == NULL) {
		return FAILURE;
	}

	 *data = block->wtintdat.all;

	return SUCCESS;
}

result_t wdt_set_interrupt_data(wdt_block_t *block, size_t data) {

	if(block == NULL) {
		return FAILURE;
	}

	block->wtintdat.all = data;

	return SUCCESS;
}

result_t wdt_get_count(wdt_block_t *block, size_t *count) {

	if(block == NULL) {
		return FAILURE;
	}

	*count = block->wtcnt.all;

	return SUCCESS;
}

result_t wdt_set_count(wdt_block_t *block, size_t count) {

	if(block == NULL) {
		return FAILURE;
	}

	block->wtcnt.all = count;

	return SUCCESS;

}
