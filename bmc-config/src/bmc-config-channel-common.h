/*
 * Copyright (C) 2003-2010 FreeIPMI Core Team
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

#ifndef _BMC_CONFIG_CHANNEL_COMMON_H_
#define _BMC_CONFIG_CHANNEL_COMMON_H_

#include "bmc-config.h"

int bmc_config_channel_common_section_get (bmc_config_state_data_t *state_data,
                                           struct config_section *channel_section);

#endif /* _BMC_CONFIG_CHANNEL_COMMON_H_ */
