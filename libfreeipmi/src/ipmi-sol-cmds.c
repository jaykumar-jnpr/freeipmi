/* 
   ipmi-sol-cmds.c - IPMI SOL Commands

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

#include "freeipmi.h"

fiid_template_t tmpl_set_sol_conf_param_sol_enable_rq =
  {
    {8, "cmd"}, 
    {4, "channel_number"}, 
    {4, "reserved1"}, 
    {8, "parameter_selector"}, 
    
    {1, "sol_payload"}, 
    {7, "reserved2"}, 
    
    {0, ""}
  };

fiid_template_t tmpl_set_sol_conf_param_sol_enable_rs =
  {
    {8,  "cmd"}, 
    {8,  "comp_code"}, 
    {0,  ""}
  };

fiid_template_t tmpl_get_sol_conf_param_rq =
  {
    {8, "cmd"}, 
    
    {4, "channel_number"}, 
    {3, "reserved1"}, 
    {1, "parameter_type"}, 
    
    {8, "parameter_selector"}, 
    
    {8, "set_selector"}, 
    {8, "block_selector"}, 
    {0, ""}
  };

fiid_template_t tmpl_get_sol_conf_param_sol_enable_rs =
  {
    {8,  "cmd"}, 
    {8,  "comp_code"}, 
    
    {4, "present_revision"}, 
    {4, "oldest_revision_parameter"}, 
    
    {1, "sol_payload"}, 
    {7, "reserved2"}, 
    
    {0,  ""}
  };

int8_t 
fill_sol_conf_sol_enable_disable (fiid_obj_t obj_data_rq, 
				  uint8_t channel_number, 
				  uint8_t sol_payload)
{
  if (!obj_data_rq
      || !IPMI_CHANNEL_NUMBER_VALID(channel_number))
    {
      errno = EINVAL;
      return -1;
    }
  
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_set_sol_conf_param_sol_enable_rq, 
		(uint8_t *)"cmd", 
		IPMI_CMD_SET_SOL_CONF_PARAMS);
  
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_set_sol_conf_param_sol_enable_rq, 
		(uint8_t *)"channel_number", 
		channel_number);
  
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_set_sol_conf_param_sol_enable_rq, 
		(uint8_t *)"parameter_selector", 
		IPMI_SOL_PARAM_SELECTOR_SOL_ENABLE);
  
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_set_sol_conf_param_sol_enable_rq, 
		(uint8_t *)"sol_payload", 
		sol_payload);
  
  return 0;
}

int8_t 
fill_get_sol_conf_param (fiid_obj_t obj_data_rq, 
			 uint8_t parameter_selector, 
			 uint8_t channel_number,
			 uint8_t parameter_type,
			 uint8_t set_selector,
			 uint8_t block_selector)
{
  if (!obj_data_rq
      || !IPMI_CHANNEL_NUMBER_VALID(channel_number))
    {
      errno = EINVAL;
      return -1;
    }

  FIID_OBJ_SET (obj_data_rq, 
		tmpl_get_sol_conf_param_rq, 
		(uint8_t *)"cmd", 
		IPMI_CMD_GET_SOL_CONF_PARAMS);
  
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_get_sol_conf_param_rq, 
		(uint8_t *)"channel_number", 
		channel_number);
    
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_get_sol_conf_param_rq, 
		(uint8_t *)"parameter_type", 
		parameter_type);
    
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_get_sol_conf_param_rq, 
		(uint8_t *)"parameter_selector", 
		parameter_selector);
    
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_get_sol_conf_param_rq, 
		(uint8_t *)"set_selector", 
		set_selector);
    
  FIID_OBJ_SET (obj_data_rq, 
		tmpl_get_sol_conf_param_rq, 
		(uint8_t *)"block_selector", 
		block_selector);
  
  return 0;
}

int8_t 
ipmi_cmd_sol_conf_sol_enable_disable2 (ipmi_device_t *dev, 
				       uint8_t channel_number, 
				       uint8_t sol_payload, 
				       fiid_obj_t obj_cmd_rs)
{
  fiid_obj_t obj_cmd_rq = NULL;
  
  if (!dev
      || !IPMI_CHANNEL_NUMBER_VALID(channel_number)
      || !obj_cmd_rs)
    {
      errno = EINVAL;
      return -1;
    }

  FIID_OBJ_ALLOCA (obj_cmd_rq, tmpl_set_sol_conf_param_sol_enable_rq);
  ERR (fill_sol_conf_sol_enable_disable (obj_cmd_rq, 
					 channel_number, 
					 sol_payload) == 0);
  ERR (ipmi_cmd (dev, 
		 IPMI_BMC_IPMB_LUN_BMC, 
		 IPMI_NET_FN_TRANSPORT_RQ, 
		 obj_cmd_rq, 
		 tmpl_set_sol_conf_param_sol_enable_rq, 
		 obj_cmd_rs, 
		 tmpl_set_sol_conf_param_sol_enable_rs) == 0);
  ERR (ipmi_comp_test (obj_cmd_rs) == 1);
  
  return (0);
}

int8_t 
ipmi_cmd_sol_conf_sol_enable2 (ipmi_device_t *dev, 
			       uint8_t channel_number, 
			       fiid_obj_t obj_cmd_rs)
{
  return ipmi_cmd_sol_conf_sol_enable_disable2 (dev, 
						channel_number, 
						IPMI_SOL_PAYLOAD_ENABLE, 
						obj_cmd_rs);
}

int8_t 
ipmi_cmd_sol_conf_sol_disable2 (ipmi_device_t *dev, 
				uint8_t channel_number, 
				fiid_obj_t obj_cmd_rs)
{
  return ipmi_cmd_sol_conf_sol_enable_disable2 (dev, 
						channel_number, 
						IPMI_SOL_PAYLOAD_DISABLE, 
						obj_cmd_rs);
}

int8_t 
ipmi_cmd_sol_conf_get_sol_enable2 (ipmi_device_t *dev, 
				   uint8_t channel_number,
				   uint8_t parameter_type,
				   uint8_t set_selector,
				   uint8_t block_selector,
				   fiid_obj_t obj_cmd_rs)
{
  fiid_obj_t obj_cmd_rq = NULL;
  
  if (!dev
      || !IPMI_CHANNEL_NUMBER_VALID(channel_number)
      || !obj_cmd_rs)
    {
      errno = EINVAL;
      return -1;
    }

  FIID_OBJ_ALLOCA (obj_cmd_rq, tmpl_get_sol_conf_param_rq);
  ERR (fill_get_sol_conf_param (obj_cmd_rq, 
				IPMI_SOL_PARAM_SELECTOR_SOL_ENABLE, 
				channel_number, 
				parameter_type, 
				set_selector, 
				block_selector) == 0);
  ERR (ipmi_cmd (dev, 
		 IPMI_BMC_IPMB_LUN_BMC, 
		 IPMI_NET_FN_TRANSPORT_RQ, 
		 obj_cmd_rq, 
		 tmpl_get_sol_conf_param_rq, 
		 obj_cmd_rs, 
		 tmpl_get_sol_conf_param_sol_enable_rs) == 0);
  ERR (ipmi_comp_test (obj_cmd_rs) == 1);
  
  return (0);
}

