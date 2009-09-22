/*
   Copyright (C) 2003-2009 FreeIPMI Core Team

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 */

#ifndef _IPMI_SENSOR_NUMBERS_OEM_SPEC_H
#define _IPMI_SENSOR_NUMBERS_OEM_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * Dell
 */

/*
 * Dell Poweredge R610
 * Dell Poweredge R710
 */

#define IPMI_SENSOR_NUMBER_OEM_DELL_ECC_CORRECTABLE_ERRORS                              0x01
#define IPMI_SENSOR_NUMBER_OEM_DELL_ECC_UNCORRECTABLE_ERRORS                            0x02
#define IPMI_SENSOR_NUMBER_OEM_DELL_IO_CHANNEL_CHECK                                    0x03
#define IPMI_SENSOR_NUMBER_OEM_DELL_PCI_PARITY_ERROR                                    0x04
#define IPMI_SENSOR_NUMBER_OEM_DELL_PCI_SYSTEM_ERROR                                    0x05
#define IPMI_SENSOR_NUMBER_OEM_DELL_EVENT_LOGGING_FOR_CORRECTABLE_ECC_EVENTS_DISABLED   0x06
#define IPMI_SENSOR_NUMBER_OEM_DELL_EVENT_LOGGING_DISABLED                              0x07
#define IPMI_SENSOR_NUMBER_OEM_DELL_UNKNOWN_ERROR                                       0x08
#define IPMI_SENSOR_NUMBER_OEM_DELL_CPU_INTERNAL_ERROR                                  0x09
#define IPMI_SENSOR_NUMBER_OEM_DELL_CPU_PROTOCOL_ERROR                                  0x0A
#define IPMI_SENSOR_NUMBER_OEM_DELL_CPU_BUSS_PERR                                       0x0B
#define IPMI_SENSOR_NUMBER_OEM_DELL_CPU_BUS_INITIALIZATION_ERROR                        0x0C
#define IPMI_SENSOR_NUMBER_OEM_DELL_CPU_MACHINE_CHECK_ERROR                             0x0D
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEMORY_SPARE                                        0x11
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEMORY_MIRROR                                       0x12
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEMORY_RAID                                         0x13
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEMORY_HOT_ADD                                      0x14
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEMORY_HOT_REMOVE                                   0x15
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEMORY_HOT_FAILURE                                  0x16
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEMORY_REDUNDANCY_REGAINED                          0x17
#define IPMI_SENSOR_NUMBER_OEM_DELL_FATAL_PCI_EXPRESS_ERRORS                            0x18
#define IPMI_SENSOR_NUMBER_OEM_DELL_CHIPSET_ERROR                                       0x19
#define IPMI_SENSOR_NUMBER_OEM_DELL_ERROR_REGISTER_POINTER                              0x1A
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEMORY_CORRECTABLE_ECC_WARNING_OR_CRITICAL_EXCEEDED 0x1B
#define IPMI_SENSOR_NUMBER_OEM_DELL_CRC_MEMORY_ERROR                                    0x1C
#define IPMI_SENSOR_NUMBER_OEM_DELL_USB_OVER_CURRENT                                    0x1D
#define IPMI_SENSOR_NUMBER_OEM_DELL_POST_FATAL_ERROR                                    0x1E
#define IPMI_SENSOR_NUMBER_OEM_DELL_INCOMPATIBLE_BMC_FIRMWARE                           0x1F
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEM_OVERTEMP                                        0x20
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEM_FATAL_SB_CRC                                    0x21
#define IPMI_SENSOR_NUMBER_OEM_DELL_MEM_FATAL_NB_CRC                                    0x22
#define IPMI_SENSOR_NUMBER_OEM_DELL_OS_WATCHDOG_TIMER                                   0x23
#define IPMI_SENSOR_NUMBER_OEM_DELL_LINK_TUNING_ERROR                                   0x24
#define IPMI_SENSOR_NUMBER_OEM_DELL_LT_FLEXADDR                                         0x25
#define IPMI_SENSOR_NUMBER_OEM_DELL_NON_FATAL_PCI_EXPRESS_ERRORS                        0x26
#define IPMI_SENSOR_NUMBER_OEM_DELL_FATAL_IO_ERROR                                      0x27
#define IPMI_SENSOR_NUMBER_OEM_DELL_MSR_INFO_LOG                                        0x28

/* 
 * Inventec
 */

/*
 * Inventec 5441/Dell Xanadu2
 */
/* achu: not official names, named based on use context */
#define IPMI_SENSOR_NUMBER_OEM_INVENTEC_POST_START        0x81
#define IPMI_SENSOR_NUMBER_OEM_INVENTEC_POST_OK           0x85
#define IPMI_SENSOR_NUMBER_OEM_INVENTEC_POST_ERROR_CODE   0x06
#define IPMI_SENSOR_NUMBER_OEM_INVENTEC_PORT80_CODE_EVENT 0x55
#define IPMI_SENSOR_NUMBER_OEM_INVENTEC_MEMORY            0x60

#ifdef __cplusplus
}
#endif

#endif
