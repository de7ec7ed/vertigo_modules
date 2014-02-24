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

#ifndef __AES_H__
#define __AES_H__

// NOTE: the current library has only been tested at the 128-bit key size

// References:
//	0: Intel® Advanced Encryption Standard (AES) Instructions Set - Rev 3
//	1: http://siyobik.info/main/reference
//	2: Federal Information Processing Standards Publication 197 November 26, 2001 Announcing the ADVANCED ENCRYPTION STANDARD (AES)
//	3: http://people.eku.edu/styere/Encrypt/JS-AES.html
//	4: http://rt.openssl.org/Ticket/Attachment/27708/13780/openssl-1.0.0-aesni-v3.patch

// AddRoundKey() = Transformation in the Cipher and Inverse Cipher in which a Round
// Key is added to the State using an XOR operation. The length of a
// Round Key equals the size of the State (i.e., for Nb = 4, the Round
// Key length equals 128 bits/16 bytes).

// InvMixColumns() = Transformation in the Inverse Cipher that is the inverse of
// MixColumns().

// InvShiftRows() = Transformation in the Inverse Cipher that is the inverse of
// ShiftRows().

// InvSubBytes() = Transformation in the Inverse Cipher that is the inverse of
// SubBytes().

// MixColumns() = Transformation in the Cipher that takes all of the columns of the
// State and mixes their data (independently of one another) to
// produce new columns.

// RotWord() = Function used in the Key Expansion routine that takes a four-byte
// word and performs a cyclic permutation.

// ShiftRows() = Transformation in the Cipher that processes the State by cyclically
// shifting the last three rows of the State by different offsets.

// SubBytes() = Transformation in the Cipher that processes the State using a non-
// linear byte substitution table (S-box) that operates on each of the
// State bytes independently.

// SubWord() = Function used in the Key Expansion routine that takes a four-byte
// input word and applies an S-box to each of the four bytes to
// produce an output word.

// K = Cipher Key.

// w = Key Schedule.

// Kr = Round Key.

// Nb = Number of columns (32-bit words) comprising the State. For this
// standard, Nb = 4. (Also see Sec. 6.3.)

// Nk = Number of 32-bit words comprising the Cipher Key. For this
// standard, Nk = 4, 6, or 8. (Also see Sec. 6.3.)

// Nr = Number of rounds, which is a function of Nk and Nb (which is
// fixed). For this standard, Nr = 10, 12, or 14. (Also see Sec. 6.3.)

// State[] = the AES algorithm’s operations are performed on a two-dimensional array of bytes
// called the State. The State consists of four rows of bytes, each containing Nb bytes, where Nb is
// the block length divided by 32.

#include <types.h>

#define AES_RIJNDAEL (1 << 1)
#define AES_BASIC    (1 << 2)

#define AES_DEFAULT_NB 4
#define AES_DEFAULT_NK 4
#define AES_SIZEOF_W(Nb, Nr) (Nb * (Nr + 1))

extern size_t aes_setup(u8_t *K, u32_t *w, size_t Nb, size_t Nk, size_t Nr, size_t *options);
extern size_t aes_encrypt(u8_t *K, u8_t *data, size_t size, size_t options);
extern size_t aes_decrypt(u8_t *K, u8_t *data, size_t size, size_t options);
extern size_t aes_number_of_rounds(u32_t Nb, u32_t Nk);

#endif //__AES_H_
