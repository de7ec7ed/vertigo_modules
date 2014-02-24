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

#include <stdlib/string.h>

#include <cryptomod/aes.h>
#include <cryptomod/basic.h>


u8_t Senc[] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
	0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
	0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
	0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
	0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
	0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
	0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
	0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
	0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
	0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
	0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
	0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
	0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
	0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
	0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
	0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
	0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

u8_t Sdec[] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
	0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
	0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
	0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
	0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
	0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
	0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
	0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
	0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
	0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
	0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
	0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
	0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
	0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
	0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
	0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
	0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

u32_t Rcon[] = {
	0x00000001, 0x000000002, 0x00000004, 0x00000008,
	0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x0000001B, 0x00000036 /* for 128-bit blocks, Rijndael never uses more than 10 rcon values */
};

void basic_setup(u8_t *K, u32_t *w, u32_t Nb, u32_t Nk, u32_t Nr) {

	u32_t i;
	u32_t tmp[AES_SIZEOF_W(Nb, Nr)];

	basic_KeyExpansion(K, w, Nb, Nk, Nr);

	memcpy(tmp, w, AES_SIZEOF_W(Nb, Nr) * sizeof(u32_t));

	for(i = 0; i < AES_SIZEOF_W(Nb, Nr); i += Nb) {
		basic_transpose((u8_t *)&(tmp[i]), (u8_t *)&(w[i]), Nb);
	}

	return;
}

void basic_transpose(u8_t *in, u8_t *out, u32_t Nb) {

	u32_t i;
	u32_t j;

	//AES__PRINTF("basic_transpose\n");

	for(i = 0; i < sizeof(u32_t); i++) {
		for(j = 0; j < Nb; j++) {
			out[(j * Nb) + i] = in[(i * Nb) + j];
		}
	}

	return;
}

void basic_encrypt(u8_t *in, u8_t *out, u32_t *w, u32_t Nb, u32_t Nr) {

	u8_t State[(sizeof(u32_t) * Nb)];
	u32_t round;

	//AES__PRINTF("basic_encrypt\n");

	//basic_print_State(in, Nb);
	basic_transpose(in, State, Nb);
	//basic_print_State(State, Nb);

	//basic_print_round_key((u8_t *)w, Nb, 0);
	basic_AddRoundKey(State, w, Nb, 0);
	//basic_print_State(State, Nb);

	for(round = 1; round < Nr; round++) {
		basic_SubBytes(State, Nb);
		//basic_print_State(State, Nb);
		basic_ShiftRows(State, Nb);
		//basic_print_State(State, Nb);
		basic_MixColumns(State, Nb);
		//basic_print_State(State, Nb);
		//basic_print_round_key((u8_t *)w, Nb, round);
		basic_AddRoundKey(State, w, Nb, round);
		//basic_print_State(State, Nb);
	}

	basic_SubBytes(State, Nb);
	//basic_print_State(State, Nb);
	basic_ShiftRows(State, Nb);
	//basic_print_State(State, Nb);
	//basic_print_round_key((u8_t *)w, Nb, round);
	basic_AddRoundKey(State, w, Nb, round);

	//basic_print_State(State, Nb);
	basic_transpose(State, out, Nb);
	//basic_print_State(out, Nb);

	return;
}

void basic_decrypt(u8_t *in, u8_t *out, u32_t *w, u32_t Nb, u32_t Nr) {

	u8_t State[(sizeof(u32_t) * Nb)];
	u32_t round;

	//AES__PRINTF("basic_decrypt\n");

	//basic_print_State(in, Nb);
	basic_transpose(in, State, Nb);
	//basic_print_State(State, Nb);

	//basic_print_round_key((u8_t *)w, Nb, Nr);
	basic_AddRoundKey(State, w, Nb, Nr);
	//basic_print_State(State, Nb);

	for(round = (Nr - 1); round >= 1; round--) {
		basic_InvShiftRows(State, Nb);
		//basic_print_State(State, Nb);
		basic_InvSubBytes(State, Nb);
		//basic_print_State(State, Nb);
		//basic_print_round_key((u8_t *)w, Nb, round);
		basic_AddRoundKey(State, w, Nb, round);
		//basic_print_State(State, Nb);
		basic_InvMixColumns(State, Nb);
		//basic_print_State(State, Nb);
	}

	basic_InvShiftRows(State, Nb);
	//basic_print_State(State, Nb);
	basic_InvSubBytes(State, Nb);
	//basic_print_State(State, Nb);
	//basic_print_round_key((u8_t *)w, Nb, round);
	basic_AddRoundKey(State, w, Nb, 0);

	//basic_print_State(State, Nb);
	basic_transpose(State, out, Nb);
	//basic_print_State(out, Nb);

	return;
}

void basic_KeyExpansion(u8_t *K/*[(sizeof(u32_t) * Nk)]*/, u32_t *w/*[Nb*(Nr + 1)]*/, u32_t Nb, u32_t Nk, u32_t Nr) {
	u32_t tmp;
	u32_t *ptr;
	u32_t i;

	//AES__PRINTF("basic_KeyExpansion\n");

	ptr = (u32_t *)K;

	i = 0;
	while(i < Nk) {
		w[i] = ptr[i];
		i = i + 1;
	}

	i = Nk;
	while(i < (Nb * (Nr + 1))) {
		tmp = w[(i - 1)];
		if((i % Nk) == 0) {
			tmp = (basic_SubWord(basic_RotWord(tmp)) ^ Rcon[((i - 1) / Nk)]);
		}
		else if((Nk > 6) && (i % Nk) == 4) {
			tmp = basic_SubWord(tmp);
		}
		w[i] = w[(i - Nk)] ^ tmp;
		i = i + 1;
	}

	return;
}

u32_t basic_Multiply(u32_t a, u32_t b) {
	u32_t res = 0;
	u32_t hbit;
	u32_t mod;

	//AES__PRINTF("basic_Multiply\n");

	while(a > 0) {
	  if((a & 1) != 0) {
		  res = res ^ b;	// "add" to the result
	  }
	  a = a >> 1;			// shift a to get next higher-order bit
	  b = b << 1;			// shift multiplier also
	}

	// now reduce it modulo x**8 + x**4 + x**3 + x + 1
	hbit = 0x10000;					// bit to test if we need to take action
	mod = 0x11b00;					// modulus - XOR by this to change value
	while(hbit >= 0x100) {
		if((res & hbit) != 0) {		// if the high-order bit is set
			res ^= mod;				// XOR with the modulus
		}
	  // prepare for the next loop
	  hbit = hbit >> 1;
	  mod = mod >> 1;
	}

	return res;
}

u32_t basic_RotWord(u32_t word) {
	u8_t *tmp_in;
	u8_t tmp_out[sizeof(u32_t)];

	//AES__PRINTF("basic_RotWord\n");

	tmp_in = (u8_t *)&word;

	tmp_out[0] = tmp_in[1];
	tmp_out[1] = tmp_in[2];
	tmp_out[2] = tmp_in[3];
	tmp_out[3] = tmp_in[0];

	//AES__PRINTF("basic_RotWord in:%08x, out:%08x\n", word, *((u32_t *)tmp_out));

	return *((u32_t *)tmp_out);
}

u32_t basic_SubWord(u32_t word) {
	u32_t i;
	u8_t *tmp_in;
	u8_t tmp_out[sizeof(u32_t)];

	//AES__PRINTF("basic_SubWord\n");

	tmp_in = (u8_t *)&word;

	for(i = 0; i < sizeof(u32_t); i++) {
		tmp_out[i] = Senc[tmp_in[i]];
	}

	//AES__PRINTF("in:%08x, out:%08x\n", word, *((u32_t *)tmp_out));

	return *((u32_t *)tmp_out);
}

void basic_AddRoundKey(u8_t *State, u32_t *w, u32_t Nb, u32_t round) {
	u32_t l;
	u32_t col;

	//AES__PRINTF("basic_AddRoundKey\n");

	l = round * Nb;

	for(col = 0; col < Nb; col++) {
		State[0 + (col * sizeof(u32_t))] ^= ((u8_t *)w)[l * sizeof(u32_t) + (col * sizeof(u32_t))];
		State[1 + (col * sizeof(u32_t))] ^= ((u8_t *)w)[l * sizeof(u32_t) + (col * sizeof(u32_t)) + 1];
		State[2 + (col * sizeof(u32_t))] ^= ((u8_t *)w)[l * sizeof(u32_t) + (col * sizeof(u32_t)) + 2];
		State[3 + (col * sizeof(u32_t))] ^= ((u8_t *)w)[l * sizeof(u32_t) + (col * sizeof(u32_t)) + 3];
	}

	return;
}

void basic_SubBytes(u8_t *State, u32_t Nb) {
	u32_t i;
	//AES__PRINTF("basic_SubBytes\n");

	for(i = 0; i < (Nb * sizeof(u32_t)); i++) {
		State[i] = Senc[State[i]];
	}

	return;
}

void basic_ShiftRows(u8_t *State, u32_t Nb) {
	u32_t t[sizeof(u32_t)];
	u32_t i = 0;

	//AES__PRINTF("basic_ShiftRows\n");
	// top row (row 0) isn't shifted

	// next row (row 1) rotated left 1 place
	i = Nb;
	t[0] = State[i + 0];
	t[1] = State[i + 1];
	t[2] = State[i + 2];
	t[3] = State[i + 3];
	State[i + 0] = t[1];
	State[i + 1] = t[2];
	State[i + 2] = t[3];
	State[i + 3] = t[0];

	// next row (row 2) rotated left 2 places
	i += Nb;
	t[0] = State[i + 0];
	t[1] = State[i + 1];
	t[2] = State[i + 2];
	t[3] = State[i + 3];
	State[i + 0] = t[2];
	State[i + 1] = t[3];
	State[i + 2] = t[0];
	State[i + 3] = t[1];

	// bottom row (row 3) rotated left 3 places
	i += Nb;
	t[0] = State[i + 0];
	t[1] = State[i + 1];
	t[2] = State[i + 2];
	t[3] = State[i + 3];
	State[i + 0] = t[3];
	State[i + 1] = t[0];
	State[i + 2] = t[1];
	State[i + 3] = t[2];

	return;
}

void basic_MixColumns(u8_t *State, u32_t Nb) {

	u32_t col;
	u8_t c[sizeof(u32_t)];

	//AES__PRINTF("basic_MixColumns\n");

	for(col=0; col < Nb; col++) {
		c[0] = State[0 * sizeof(u32_t) + col];
		c[1] = State[1 * sizeof(u32_t) + col];
		c[2] = State[2 * sizeof(u32_t) + col];
		c[3] = State[3 * sizeof(u32_t) + col];

		// do mixing, and put back into array
		State[0 * sizeof(u32_t) + col] = basic_Multiply(2, c[0]) ^ basic_Multiply(3, c[1]) ^ c[2] ^ c[3];
		State[1 * sizeof(u32_t) + col] = c[0] ^ basic_Multiply(2, c[1]) ^ basic_Multiply(3, c[2]) ^ c[3];
		State[2 * sizeof(u32_t) + col] = c[0] ^ c[1] ^ basic_Multiply(2, c[2]) ^ basic_Multiply(3, c[3]);
		State[3 * sizeof(u32_t) + col] = basic_Multiply(3, c[0]) ^ c[1] ^ c[2] ^ basic_Multiply(2, c[3]);
	}

	return;
}

void basic_InvSubBytes(u8_t *State, u32_t Nb) {
	u32_t i;

	//AES__PRINTF("basic_InvSubBytes\n");

	for(i = 0; i < Nb * sizeof(u32_t); i++) {
		State[i] = Sdec[State[i]];
	}

	return;
}

void basic_InvShiftRows(u8_t *State, u32_t Nb) {
	u32_t t[sizeof(u32_t)];
	u32_t i = 0;

	//AES__PRINTF("basic_InvShiftRows\n");

	// top row (row 0) isn't shifted

	// next row (row 1) rotated left 1 place
	i = Nb;
	t[0] = State[i + 0];
	t[1] = State[i + 1];
	t[2] = State[i + 2];
	t[3] = State[i + 3];
	State[i + 0] = t[3];
	State[i + 1] = t[0];
	State[i + 2] = t[1];
	State[i + 3] = t[2];

	// next row (row 2) rotated left 2 places
	i += Nb;
	t[0] = State[i + 0];
	t[1] = State[i + 1];
	t[2] = State[i + 2];
	t[3] = State[i + 3];
	State[i + 0] = t[2];
	State[i + 1] = t[3];
	State[i + 2] = t[0];
	State[i + 3] = t[1];

	// bottom row (row 3) rotated left 3 places
	i += Nb;
	t[0] = State[i + 0];
	t[1] = State[i + 1];
	t[2] = State[i + 2];
	t[3] = State[i + 3];
	State[i + 0] = t[1];
	State[i + 1] = t[2];
	State[i + 2] = t[3];
	State[i + 3] = t[0];

	return;
}

void basic_InvMixColumns(u8_t *State, u32_t Nb) {

	u32_t col;
	u8_t c[sizeof(u32_t)];

	//AES__PRINTF("basic_InvMixColumns\n");

	for(col = 0; col < Nb; col++) {
		c[0] = State[0 * sizeof(u32_t) + col];
		c[1] = State[1 * sizeof(u32_t) + col];
		c[2] = State[2 * sizeof(u32_t) + col];
		c[3] = State[3 * sizeof(u32_t) + col];

		// do inverse mixing, and put back into array
		State[0 * sizeof(u32_t) + col] = basic_Multiply(0x0e,c[0]) ^ basic_Multiply(0x0b,c[1]) ^ basic_Multiply(0x0d,c[2]) ^ basic_Multiply(0x09,c[3]);
		State[1 * sizeof(u32_t) + col] = basic_Multiply(0x09,c[0]) ^ basic_Multiply(0x0e,c[1]) ^ basic_Multiply(0x0b,c[2]) ^ basic_Multiply(0x0d,c[3]);
		State[2 * sizeof(u32_t) + col] = basic_Multiply(0x0d,c[0]) ^ basic_Multiply(0x09,c[1]) ^ basic_Multiply(0x0e,c[2]) ^ basic_Multiply(0x0b,c[3]);
		State[3 * sizeof(u32_t) + col] = basic_Multiply(0x0b,c[0]) ^ basic_Multiply(0x0d,c[1]) ^ basic_Multiply(0x09,c[2]) ^ basic_Multiply(0x0e,c[3]);
	}

	return;
}

/*
void basic_print_State(u8_t *State, u32_t Nb) {
	u32_t i;

	AES__PRINTF("State:\t");
	for(i = 0; i < (sizeof(u32_t) * Nb); i++) {
		if(i != 0 && i % 4 == 0) {
			AES__PRINTF("\n\t");
		}
		AES__PRINTF("%02x ", State[i]);
	}
	AES__PRINTF("\n");

	return;
}

void basic_print_round_key(u8_t *w, u32_t Nb, u32_t round) {
	u32_t i;

	AES__PRINTF("Round %d Key:\t", round);
	for(i = 0; i < (sizeof(u32_t) * Nb); i++) {
		if(i != 0 && i % 4 == 0) {
			AES__PRINTF("\n\t\t");
		}
		AES__PRINTF("%02x ", w[i + (round * sizeof(u32_t) * Nb)]);
	}
	AES__PRINTF("\n");

	return;
}
*/

