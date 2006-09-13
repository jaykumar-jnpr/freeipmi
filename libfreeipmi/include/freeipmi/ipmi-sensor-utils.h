/* 
   ipmi-sensor-utils.h - IPMI Sensor utility procedures

   Copyright (C) 2003, 2004, 2005 FreeIPMI Core Team

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
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  
*/


#ifndef _IPMI_SENSOR_UTILS_H
#define _IPMI_SENSOR_UTILS_H

#include <sys/types.h>

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

int ipmi_sensor_decode_value (int8_t r_exponent, 
			      int8_t b_exponent, 
                              int16_t m,
                              int16_t b,
                              uint8_t linearization,
			      uint8_t analog_data_format, 
			      uint8_t raw_data,
			      double *value);

#endif /* _IPMI_SENSOR_UTILS_H */
