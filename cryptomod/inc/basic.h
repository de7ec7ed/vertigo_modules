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

#ifndef __BASIC_H__
#define __BASIC_H__

#include <types.h>

// Rcon[] = The round constant word array.

// Senc[] = The S-Box encrypt byte array.

// Sdec[] = The S-Box dycrypt byte array.

extern u32_t Rcon[];
extern u8_t Senc[];
extern u8_t Sdec[];

extern size_t basic_number_of_rounds(u32_t Nb, u32_t Nk);
extern void basic_setup(u8_t *K, u32_t *w, u32_t Nb, u32_t Nk, u32_t Nr);
extern void basic_transpose(u8_t *in, u8_t *out, u32_t Nb);
extern void basic_encrypt(u8_t *in, u8_t *out, u32_t *w, u32_t Nb, u32_t Nr);
extern void basic_decrypt(u8_t *in, u8_t *out, u32_t *w, u32_t Nb, u32_t Nr);

extern void basic_KeyExpansion(u8_t *K/*[(sizeof(u32_t) * Nk)]*/, u32_t *w/*[Nb*(Nr + 1)]*/, u32_t Nb, u32_t Nk, u32_t Nr);
extern u32_t basic_Multiply(u32_t a, u32_t b);

extern u32_t basic_RotWord(u32_t word);
extern u32_t basic_SubWord(u32_t word);

extern void basic_AddRoundKey(u8_t *State, u32_t *w, u32_t Nb, u32_t round);

extern void basic_SubBytes(u8_t *State, u32_t Nb);
extern void basic_ShiftRows(u8_t *State, u32_t Nb);
extern void basic_MixColumns(u8_t *State, u32_t Nb);

extern void basic_InvSubBytes(u8_t *State, u32_t Nb);
extern void basic_InvShiftRows(u8_t *State, u32_t Nb);
extern void basic_InvMixColumns(u8_t *State, u32_t Nb);

extern void basic_print_State(u8_t *State, u32_t Nb);
void basic_print_round_key(u8_t *w, u32_t Nb, u32_t round);

#endif //__BASIC_H__
