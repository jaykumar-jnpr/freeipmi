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

#ifndef _IPMI_SENSOR_READ_UTIL_H
#define _IPMI_SENSOR_READ_UTIL_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#ifdef STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */
#include <errno.h>

#include "freeipmi/api/ipmi-api.h"
#include "freeipmi/fiid/fiid.h"
#include "freeipmi/sensor-read/ipmi-sensor-read.h"

#include "ipmi-sensor-read-defs.h"

void sensor_read_set_sensor_read_errnum_by_errno (ipmi_sensor_read_ctx_t ctx, int __errno);

void sensor_read_set_sensor_read_errnum_by_fiid_object (ipmi_sensor_read_ctx_t ctx, fiid_obj_t obj);

int sensor_read_fiid_obj_get (ipmi_sensor_read_ctx_t ctx, fiid_obj_t obj, char *field, uint64_t *val);

#endif /* ipmi-sensor-read-util.h */
