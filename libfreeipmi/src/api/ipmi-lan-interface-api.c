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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */
#if HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */
#include <assert.h>
#include <errno.h>

#include "freeipmi/api/ipmi-messaging-support-cmds-api.h"
#include "freeipmi/interface/ipmi-rmcpplus-interface.h"
#include "freeipmi/spec/ipmi-authentication-type-spec.h"

#include "ipmi-api-defs.h"
#include "ipmi-api-trace.h"
#include "ipmi-api-util.h"
#include "ipmi-lan-session-common.h"

#include "libcommon/ipmi-fiid-util.h"

#include "freeipmi-portability.h"

fiid_template_t tmpl_lan_raw =
  {
    { 8192, "raw_data", FIID_FIELD_OPTIONAL | FIID_FIELD_LENGTH_VARIABLE},
    { 0, "", 0}
  };

int
ipmi_lan_cmd (ipmi_ctx_t ctx,
              fiid_obj_t obj_cmd_rq,
              fiid_obj_t obj_cmd_rs)
{
  uint8_t authentication_type;
  unsigned int internal_workaround_flags = 0;

  if (!ctx || ctx->magic != IPMI_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!ctx->io.outofband.sockfd)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!fiid_obj_valid (obj_cmd_rq)
      || !fiid_obj_valid (obj_cmd_rs))
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_PARAMETERS);
      return (-1);
    }

  if (FIID_OBJ_PACKET_VALID (obj_cmd_rq) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rq);
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_INTERNAL_ERROR);
      return (-1);
    }

  ipmi_lan_cmd_get_session_parameters (ctx,
                                       &authentication_type,
                                       &internal_workaround_flags);

  /* if auth type NONE, still pass password.  Needed for
   * check_unexpected_authcode workaround
   */
  return (ipmi_lan_cmd_wrapper (ctx,
                                internal_workaround_flags,
                                ctx->lun,
                                ctx->net_fn,
                                authentication_type,
                                1,
                                &(ctx->io.outofband.session_sequence_number),
                                ctx->io.outofband.session_id,
                                &(ctx->io.outofband.rq_seq),
                                ctx->io.outofband.password,
                                IPMI_1_5_MAX_PASSWORD_LENGTH,
                                obj_cmd_rq,
                                obj_cmd_rs));
}

int
ipmi_lan_cmd_raw (ipmi_ctx_t ctx,
                  const void *buf_rq,
                  unsigned int buf_rq_len,
                  void *buf_rs,
                  unsigned int buf_rs_len)
{
  fiid_obj_t obj_cmd_rq = NULL;
  fiid_obj_t obj_cmd_rs = NULL;
  int len, rv = -1;
  uint8_t authentication_type;
  unsigned int internal_workaround_flags = 0;

  if (!ctx || ctx->magic != IPMI_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!ctx->io.outofband.sockfd)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!buf_rq
      || !buf_rq_len
      || !buf_rs
      || !buf_rs_len)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_PARAMETERS);
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_INTERNAL_ERROR);
      return (-1);
    }

  if (!(obj_cmd_rq = fiid_obj_create (tmpl_lan_raw)))
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }
  if (!(obj_cmd_rs = fiid_obj_create (tmpl_lan_raw)))
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (fiid_obj_set_all (obj_cmd_rq,
                        buf_rq,
                        buf_rq_len) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rq);
      goto cleanup;
    }

  ipmi_lan_cmd_get_session_parameters (ctx,
                                       &authentication_type,
                                       &internal_workaround_flags);

  if (ipmi_lan_cmd_wrapper (ctx,
                            internal_workaround_flags,
                            ctx->lun,
                            ctx->net_fn,
                            authentication_type,
                            1,
                            &(ctx->io.outofband.session_sequence_number),
                            ctx->io.outofband.session_id,
                            &(ctx->io.outofband.rq_seq),
                            ctx->io.outofband.password,
                            IPMI_1_5_MAX_PASSWORD_LENGTH,
                            obj_cmd_rq,
                            obj_cmd_rs) < 0)
    goto cleanup;

  if ((len = fiid_obj_get_all (obj_cmd_rs,
                               buf_rs,
                               buf_rs_len)) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rs);
      goto cleanup;
    }

  rv = len;
 cleanup:
  fiid_obj_destroy (obj_cmd_rq);
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}

int
ipmi_lan_2_0_cmd (ipmi_ctx_t ctx,
                  fiid_obj_t obj_cmd_rq,
                  fiid_obj_t obj_cmd_rs)
{
  uint8_t payload_authenticated;
  uint8_t payload_encrypted;

  if (!ctx || ctx->magic != IPMI_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN_2_0)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!ctx->io.outofband.sockfd)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!fiid_obj_valid (obj_cmd_rq)
      || !fiid_obj_valid (obj_cmd_rs))
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_PARAMETERS);
      return (-1);
    }

  if (FIID_OBJ_PACKET_VALID (obj_cmd_rq) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rq);
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN_2_0)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_INTERNAL_ERROR);
      return (-1);
    }

  ipmi_lan_2_0_cmd_get_session_parameters (ctx,
                                           &payload_authenticated,
                                           &payload_encrypted);

  return (ipmi_lan_2_0_cmd_wrapper (ctx,
                                    ctx->lun,
                                    ctx->net_fn,
                                    IPMI_PAYLOAD_TYPE_IPMI,
                                    payload_authenticated,
                                    payload_encrypted,
                                    NULL,
                                    &(ctx->io.outofband.session_sequence_number),
                                    ctx->io.outofband.managed_system_session_id,
                                    &(ctx->io.outofband.rq_seq),
                                    ctx->io.outofband.authentication_algorithm,
                                    ctx->io.outofband.integrity_algorithm,
                                    ctx->io.outofband.confidentiality_algorithm,
                                    ctx->io.outofband.integrity_key_ptr,
                                    ctx->io.outofband.integrity_key_len,
                                    ctx->io.outofband.confidentiality_key_ptr,
                                    ctx->io.outofband.confidentiality_key_len,
                                    strlen (ctx->io.outofband.password) ? ctx->io.outofband.password : NULL,
                                    strlen (ctx->io.outofband.password),
                                    obj_cmd_rq,
                                    obj_cmd_rs));
}

int
ipmi_lan_2_0_cmd_raw (ipmi_ctx_t ctx,
                      const void *buf_rq,
                      unsigned int buf_rq_len,
                      void *buf_rs,
                      unsigned int buf_rs_len)
{
  uint8_t payload_authenticated;
  uint8_t payload_encrypted;
  fiid_obj_t obj_cmd_rq = NULL;
  fiid_obj_t obj_cmd_rs = NULL;
  int len, rv = -1;

  if (!ctx || ctx->magic != IPMI_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN_2_0)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!ctx->io.outofband.sockfd)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!buf_rq
      || !buf_rq_len
      || !buf_rs
      || !buf_rs_len)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_PARAMETERS);
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN_2_0)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_INTERNAL_ERROR);
      return (-1);
    }

  if (!(obj_cmd_rq = fiid_obj_create (tmpl_lan_raw)))
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }
  if (!(obj_cmd_rs = fiid_obj_create (tmpl_lan_raw)))
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (fiid_obj_set_all (obj_cmd_rq,
                        buf_rq,
                        buf_rq_len) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rq);
      goto cleanup;
    }

  ipmi_lan_2_0_cmd_get_session_parameters (ctx,
                                           &payload_authenticated,
                                           &payload_encrypted);

  if (ipmi_lan_2_0_cmd_wrapper (ctx,
                                ctx->lun,
                                ctx->net_fn,
                                IPMI_PAYLOAD_TYPE_IPMI,
                                payload_authenticated,
                                payload_encrypted,
                                NULL,
                                &(ctx->io.outofband.session_sequence_number),
                                ctx->io.outofband.managed_system_session_id,
                                &(ctx->io.outofband.rq_seq),
                                ctx->io.outofband.authentication_algorithm,
                                ctx->io.outofband.integrity_algorithm,
                                ctx->io.outofband.confidentiality_algorithm,
                                ctx->io.outofband.integrity_key_ptr,
                                ctx->io.outofband.integrity_key_len,
                                ctx->io.outofband.confidentiality_key_ptr,
                                ctx->io.outofband.confidentiality_key_len,
                                strlen (ctx->io.outofband.password) ? ctx->io.outofband.password : NULL,
                                strlen (ctx->io.outofband.password),
                                obj_cmd_rq,
                                obj_cmd_rs) < 0)
    goto cleanup;

  if ((len = fiid_obj_get_all (obj_cmd_rs,
                               buf_rs,
                               buf_rs_len)) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rs);
      goto cleanup;
    }
  rv = len;

 cleanup:
  fiid_obj_destroy (obj_cmd_rq);
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}
