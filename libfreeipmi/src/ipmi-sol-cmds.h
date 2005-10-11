/*
   ipmi-sol-cmds.h - IPMI SOL Commands

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
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef _IPMI_SOL_CMDS_H
#define _IPMI_SOL_CMDS_H

#define IPMI_CMD_SET_SOL_CONF_PARAMS    0x21
#define IPMI_CMD_GET_SOL_CONF_PARAMS    0x22

#define IPMI_SOL_PARAM_SELECTOR_SOL_ENABLE    0x1

#define IPMI_SOL_PAYLOAD_DISABLE    0x0
#define IPMI_SOL_PAYLOAD_ENABLE     0x1

#ifdef __cplusplus
extern "C" {
#endif

extern fiid_template_t tmpl_set_sol_conf_param_sol_enable_rq;
extern fiid_template_t tmpl_set_sol_conf_param_sol_enable_rs;
extern fiid_template_t tmpl_set_sol_conf_param_sol_disable_rs;

extern fiid_template_t tmpl_get_sol_conf_param_rq;
extern fiid_template_t tmpl_get_sol_conf_param_sol_enable_rs;

int8_t ipmi_sol_conf_sol_enable (u_int16_t sms_io_base, 
				 u_int8_t channel_number, 
				 fiid_obj_t obj_data_rs);

int8_t ipmi_sol_conf_sol_disable (u_int16_t sms_io_base, 
				  u_int8_t channel_number, 
				  fiid_obj_t obj_data_rs);

int8_t ipmi_sol_conf_get_sol_enable (u_int16_t sms_io_base, 
				     u_int8_t channel_number, 
				     u_int8_t parameter_type, 
				     u_int8_t set_selector, 
				     u_int8_t block_selector, 
				     fiid_obj_t obj_data_rs);

int8_t ipmi_cmd_sol_conf_sol_enable_disable2 (ipmi_device_t *dev, 
					      u_int8_t channel_number, 
					      u_int8_t sol_payload, 
					      fiid_obj_t obj_cmd_rs);
int8_t ipmi_cmd_sol_conf_sol_enable2 (ipmi_device_t *dev, 
				      u_int8_t channel_number, 
				      fiid_obj_t obj_cmd_rs);
int8_t ipmi_cmd_sol_conf_sol_disable2 (ipmi_device_t *dev, 
				       u_int8_t channel_number, 
				       fiid_obj_t obj_cmd_rs);
int8_t ipmi_cmd_sol_conf_get_sol_enable2 (ipmi_device_t *dev, 
					  u_int8_t channel_number,
					  u_int8_t parameter_type,
					  u_int8_t set_selector,
					  u_int8_t block_selector,
					  fiid_obj_t obj_cmd_rs);


#ifdef __cplusplus
}
#endif


#endif
