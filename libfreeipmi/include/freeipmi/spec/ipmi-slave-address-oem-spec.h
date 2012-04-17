/*
 * Copyright (C) 2003-2012 FreeIPMI Core Team
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef IPMI_SLAVE_ADDRESS_OEM_SPEC_H
#define IPMI_SLAVE_ADDRESS_OEM_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
 * Intel                                   *
 *******************************************/

/*
 * Intel S5500WB/Penguin Computing Relion 700
 */

#define IPMI_GENERATOR_ID_OEM_INTEL_BIOS_SMI_HANDLER   0x33
#define IPMI_GENERATOR_ID_OEM_INTEL_ME_FIRMWARE        0x2C
#define IPMI_GENERATOR_ID_OEM_INTEL_HSC_FIRMWARE       0xC0

/*******************************************
 * Inventec                                *
 *******************************************/

/*
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 */
/* achu: not official names, named based on use context */
#define IPMI_GENERATOR_ID_OEM_INVENTEC_BIOS            0x01
#define IPMI_GENERATOR_ID_OEM_INVENTEC_SMI             0x21
#define IPMI_GENERATOR_ID_OEM_INVENTEC_POST_ERROR_CODE 0x31

/*******************************************
 * Quanta                                  *
 *******************************************/

/*
 * Quanta S99Q/Dell FS12-TY
 */
/* achu: not official names, named based on use context */
#define IPMI_GENERATOR_ID_OEM_QUANTA_ERROR           0x01

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SLAVE_ADDRESS_OEM_SPEC_H */
