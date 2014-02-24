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

#include <socmod/soc.h>

void soc_get_model_number(u8_t **name) {

	*name = gen_add_base(SOC_MODEL_NUMBER);

	return;
}

void soc_get_family(u8_t **string) {

	*string = gen_add_base(SOC_FAMILY);

	return;
}

void soc_get_manufacture(u8_t **string) {

	*string = gen_add_base(SOC_MANUFACTURE);

	return;
}
