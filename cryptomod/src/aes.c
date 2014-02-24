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

#include <kernel/mas.h>

#include <cryptomod/aes.h>
#include <cryptomod/basic.h>
#include <cryptomod/rijndael.h>
#include <stdlib/string.h>

size_t aes_setup(u8_t *K, u32_t *w, size_t Nb, size_t Nk, size_t Nr, size_t *options) {

	if(*options & AES_RIJNDAEL) {
		return SUCCESS;
	}
	else if(*options & AES_BASIC) {
		// use the basic pure software based algorithm
		basic_setup(K, w, Nb, Nk, Nr);
		return SUCCESS;
	}
	else {
		// no supported or requested options available
		// lower the bits and return FAILURE
		*options &= ~AES_BASIC;
		return FAILURE;
	}
}
size_t aes_encrypt(u8_t *K, u8_t *data, size_t size, size_t options) {

	u8_t *tmp;
	u32_t *w;
	size_t Nb;
	size_t Nk;
	size_t Nr;
	size_t i;

	Nb = AES_DEFAULT_NB;
	Nk = AES_DEFAULT_NK;
	Nr = aes_number_of_rounds(Nb, Nk);

	tmp = (u8_t *)malloc((sizeof(u32_t) * Nb));

	w = (u32_t *)malloc(AES_SIZEOF_W(Nb, Nr) * sizeof(u32_t));

	if((tmp == NULL) || (w == NULL)) {
		if(tmp) {
			free(tmp);
		}
		if(w) {
			free(w);
		}

		return FAILURE;
	}

	if(aes_setup(K, w, Nb, Nk, Nr, &options) != SUCCESS) {
		return FAILURE;
	}

	if(options & AES_RIJNDAEL) {
		rijndaelKeySetupEnc(w, K, (Nk * sizeof(u32_t) * 8));

		for(i = 0; i < size; i += (sizeof(u32_t) * Nb)) {
			if((i + (sizeof(u32_t) * Nb)) <= size) {			
				rijndaelEncrypt(w, Nr, &(data[i]), &(data[i]));
			}
			else {
				if((i - size) < (sizeof(u32_t) * Nb)) {
					memset(tmp, 0 , (sizeof(u32_t) * Nb));
					memcpy(tmp, &(data[i]), (size - i));
					rijndaelEncrypt(w, Nr, &(data[i]), &(data[i]));
					memcpy(&(data[i]), tmp, (size - i));
				}
			}
		}		
	}
	else if(options & AES_BASIC) {
		for(i = 0; i < size; i += (sizeof(u32_t) * Nb)) {
			if((i + (sizeof(u32_t) * Nb)) <= size) {			
				basic_encrypt(&(data[i]), &(data[i]), w, Nb, Nr);
			}
			else {
				if((i - size) < (sizeof(u32_t) * Nb)) {
					memset(tmp, 0 , (sizeof(u32_t) * Nb));
					memcpy(tmp, &(data[i]), (i - size));
					basic_encrypt(tmp, tmp, w, Nb, Nr);
					memcpy(&(data[i]), tmp, (i - size));
				}
			}
		}
	}

	free(w);
	free(tmp);

	return SUCCESS;
}
size_t aes_decrypt(u8_t *K, u8_t *data, size_t size, size_t options) {
	u8_t *tmp;
	u32_t *w;
	size_t Nb = AES_DEFAULT_NB;
	size_t Nk = AES_DEFAULT_NK;
	size_t Nr;
	size_t i;

	Nr = aes_number_of_rounds(Nb, Nk);

	tmp = (u8_t *)malloc((sizeof(u32_t) * Nb));

	w = (u32_t *)malloc(AES_SIZEOF_W(Nb, Nr) * sizeof(u32_t));

	if((tmp == NULL) || (w == NULL)) {
		if(tmp) {
			free(tmp);
		}
		if(w) {
			free(w);
		}

		return FAILURE;
	}

	if(aes_setup(K, w, Nb, Nk, Nr, &options) != SUCCESS) {
		return FAILURE;
	}

	if(options & AES_RIJNDAEL) {
		rijndaelKeySetupDec(w, K, (Nk * sizeof(u32_t) * 8));

		for(i = 0; i < size; i += (sizeof(u32_t) * Nb)) {
			if((i + (sizeof(u32_t) * Nb)) <= size) {			
				rijndaelDecrypt(w, Nr, &(data[i]), &(data[i]));
			}
			else {
				if((i - size) < (sizeof(u32_t) * Nb)) {
					memset(tmp, 0 , (sizeof(u32_t) * Nb));
					memcpy(tmp, &(data[i]), (size - i));
					rijndaelDecrypt(w, Nr, &(data[i]), &(data[i]));
					memcpy(&(data[i]), tmp, (size - i));
				}
			}
		}		
	}
	else if(options & AES_BASIC) {
		for(i = 0; i < size; i += (sizeof(u32_t) * Nb)) {
			if((i + (sizeof(u32_t) * Nb)) <= size) {			
				basic_decrypt(&(data[i]), &(data[i]), w, Nb, Nr);
			}
			else {
				if((i - size) < (sizeof(u32_t) * Nb)) {
					memset(tmp, 0 , (sizeof(u32_t) * Nb));
					memcpy(tmp, &(data[i]), (i - size));
					basic_decrypt(tmp, tmp, w, Nb, Nr);
					memcpy(&(data[i]), tmp, (i - size));
				}
			}
		}
	}

	free(w);
	free(tmp);

	return SUCCESS;
}

size_t aes_number_of_rounds(u32_t Nb, u32_t Nk) {

	//AES_PRINTF("basic_number_of_rounds\n");

	if(Nb != 4) {
		return FAILURE;
	}

	if(Nk == 4) {
		return 10;
	}
	else if(Nk == 6) {
		return 12;
	}
	else if(Nk == 8) {
		return 14;
	}
	else {
		return 0;
	}
}

