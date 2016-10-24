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

#ifndef __QEMUMOD_SOC_H__
#define __QEMUMOD_SOC_H__

#define SOC_MIDR 0x511F04D0 // FIXME: get the right midr

#define SOC_MODEL_NUMBER "goldfish"

#define SOC_FAMILY "emulator"

#define SOC_MANUFACTURER "qemu"

void soc_get_model_number(u8_t **string);

void soc_get_family(u8_t **string);

void soc_get_manufacturer(u8_t **string);

#endif //__QEMUMOD_SOC_H__
