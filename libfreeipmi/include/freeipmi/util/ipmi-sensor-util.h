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


#ifndef _IPMI_SENSOR_UTIL_H
#define _IPMI_SENSOR_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* return length of string written into buffer on success, -1 on error */
int ipmi_get_threshold_message (uint8_t offset, char *buf, unsigned int buflen);

const char *ipmi_get_sensor_type_string (uint8_t sensor_type);

/* b_exponent - sometimes documented as k1 */
/* r_exponent - sometimes documented as k2 */
int ipmi_sensor_decode_value (int8_t r_exponent,
                              int8_t b_exponent,
                              int16_t m,
                              int16_t b,
                              uint8_t linearization,
                              uint8_t analog_data_format,
                              uint8_t raw_data,
                              double *value);

/* b_exponent - sometimes documented as k1 */
/* r_exponent - sometimes documented as k2 */
int ipmi_sensor_decode_raw_value (int8_t r_exponent,
                                  int8_t b_exponent,
                                  int16_t m,
                                  int16_t b,
                                  uint8_t linearization,
                                  uint8_t analog_data_format,
                                  double value,
                                  uint8_t *raw_data);

/* r_exponent - sometimes documented as k2 */
int ipmi_sensor_decode_tolerance (int8_t r_exponent,
                                  int16_t m,
                                  uint8_t raw_data,
                                  uint8_t linearization,
                                  double *value);

/* accuracy returned as percentage */
int ipmi_sensor_decode_accuracy (uint16_t accuracy_raw,
                                 uint8_t accuracy_exp,
                                 double *value);

#ifdef __cplusplus
}
#endif

#endif /* _IPMI_SENSOR_UTIL_H */
