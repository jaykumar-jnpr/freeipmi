/*****************************************************************************\
 *  $Id: ipmi-sel-parse.h,v 1.5 2009-01-13 01:02:27 chu11 Exp $
 *****************************************************************************
 *  Copyright (C) 2007-2009 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2006-2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-222073
 *
 *  This file is part of Ipmimonitoring, an IPMI sensor monitoring
 *  library.  For details, see http://www.llnl.gov/linux/.
 *
 *  Ipmimonitoring is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmimonitoring is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmimonitoring.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef _IPMI_SEL_PARSE_H
#define _IPMI_SEL_PARSE_H

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>
#include <freeipmi/sdr-cache/ipmi-sdr-cache.h>

#define IPMI_SEL_PARSE_CTX_ERR_SUCCESS                                 0
#define IPMI_SEL_PARSE_CTX_ERR_CONTEXT_NULL                            1
#define IPMI_SEL_PARSE_CTX_ERR_CONTEXT_INVALID                         2
#define IPMI_SEL_PARSE_CTX_ERR_PARAMETERS                              3
#define IPMI_SEL_PARSE_CTX_ERR_OUT_OF_MEMORY                           4
#define IPMI_SEL_PARSE_CTX_ERR_SDR_CACHE_ERROR                         5
#define IPMI_SEL_PARSE_CTX_ERR_NO_SEL_ENTRIES                          6
#define IPMI_SEL_PARSE_CTX_ERR_SEL_ENTRIES_LIST_END                    7
#define IPMI_SEL_PARSE_CTX_ERR_INVALID_SEL_ENTRY                       8
#define IPMI_SEL_PARSE_CTX_ERR_NOT_FOUND                               9
#define IPMI_SEL_PARSE_CTX_ERR_CALLBACK_ERROR                         10
#define IPMI_SEL_PARSE_CTX_ERR_IPMI_ERROR                             11 
#define IPMI_SEL_PARSE_CTX_ERR_SYSTEM_ERROR                           12
#define IPMI_SEL_PARSE_CTX_ERR_OVERFLOW                               13
#define IPMI_SEL_PARSE_CTX_ERR_INTERNAL_ERROR                         14
#define IPMI_SEL_PARSE_CTX_ERR_ERRNUMRANGE                            15

#define IPMI_SEL_PARSE_FLAGS_DEFAULT                              0x0000
#define IPMI_SEL_PARSE_FLAGS_DEBUG_DUMP                           0x0001

#define IPMI_SEL_PARSE_STRING_FLAGS_DEFAULT                       0x0000
#define IPMI_SEL_PARSE_STRING_FLAGS_VERBOSE                       0x0001
#define IPMI_SEL_PARSE_STRING_FLAGS_IGNORE_UNAVAILABLE_FIELD      0x0002
#define IPMI_SEL_PARSE_STRING_FLAGS_OUTPUT_NOT_AVAILABLE          0x0004
#define IPMI_SEL_PARSE_STRING_FLAGS_DATE_USE_SLASH                0x0008
#define IPMI_SEL_PARSE_STRING_FLAGS_DATE_MONTH_STRING             0x0010
#define IPMI_SEL_PARSE_STRING_FLAGS_LEGACY                        0x1000

#define IPMI_SEL_RECORD_TYPE_CLASS_SYSTEM_EVENT_RECORD               0x0
#define IPMI_SEL_RECORD_TYPE_CLASS_TIMESTAMPED_OEM_RECORD            0x1
#define IPMI_SEL_RECORD_TYPE_CLASS_NON_TIMESTAMPED_OEM_RECORD        0x2
#define IPMI_SEL_RECORD_TYPE_CLASS_UNKNOWN                           0x3

typedef struct ipmi_sel_parse_ctx *ipmi_sel_parse_ctx_t;

typedef int (*Ipmi_Sel_Parse_Callback)(ipmi_sel_parse_ctx_t ctx, void *callback_data);

/* SEL Parse Context Functions 
 * - ipmi_ctx assumes ipmi opened and ready to go
 * - sdr_cache_ctx assumed ready for reading
 * - sdr_cache_ctx is optional, sdr won't be used if not available
 */
ipmi_sel_parse_ctx_t ipmi_sel_parse_ctx_create(ipmi_ctx_t ipmi_ctx, ipmi_sdr_cache_ctx_t sdr_cache_ctx);
void ipmi_sel_parse_ctx_destroy(ipmi_sel_parse_ctx_t ctx);
int ipmi_sel_parse_ctx_errnum(ipmi_sel_parse_ctx_t ctx);
char * ipmi_sel_parse_ctx_strerror(int errnum);

/* SEL Parse flag functions */
int ipmi_sel_parse_ctx_get_flags(ipmi_sel_parse_ctx_t ctx, unsigned int *flags);
int ipmi_sel_parse_ctx_set_flags(ipmi_sel_parse_ctx_t ctx, unsigned int flags);
char *ipmi_sel_parse_ctx_get_debug_prefix(ipmi_sel_parse_ctx_t ctx);
int ipmi_sel_parse_ctx_set_debug_prefix(ipmi_sel_parse_ctx_t ctx, const char *prefix);

/* determines separator between fields in string functions
 *
 * defaults to " | "
 */
char *ipmi_sel_parse_ctx_get_separator(ipmi_sel_parse_ctx_t ctx);
int ipmi_sel_parse_ctx_set_separator(ipmi_sel_parse_ctx_t ctx, const char *separator);

/* SEL Parse Functions 
 * 
 * callback is called after each SEL entry is parsed
 *
 * Returns the number of entries parsed
 */
int ipmi_sel_parse(ipmi_sel_parse_ctx_t ctx,
                   Ipmi_Sel_Parse_Callback callback,
                   void *callback_data);

/* SEL data retrieval functions after SEL is parsed 
 *
 * seek_record_id moves the iterator to the closest record_id >= record_id
 * search_record_id finds the record id, will return NOT_FOUND if it can't be found
 */
int ipmi_sel_parse_first(ipmi_sel_parse_ctx_t ctx);
int ipmi_sel_parse_next(ipmi_sel_parse_ctx_t ctx);
int ipmi_sel_parse_sel_entry_count(ipmi_sel_parse_ctx_t ctx);
int ipmi_sel_parse_seek_record_id(ipmi_sel_parse_ctx_t ctx, uint16_t record_id);
int ipmi_sel_parse_search_record_id(ipmi_sel_parse_ctx_t ctx, uint16_t record_id);

/* SEL read functions - can be used after sel parsed or within callbacks 
 * - will return IPMI_SEL_PARSE_CTX_ERR_INVALID_SEL_ENTRY if current sel entry
 *   is not appropriate for data requested.
 */

/* record_id & record_type - works with all SEL record types */
int ipmi_sel_parse_read_record_id(ipmi_sel_parse_ctx_t ctx, uint16_t *record_id);
int ipmi_sel_parse_read_record_type(ipmi_sel_parse_ctx_t ctx, uint8_t *record_type);

/* timetamp - works with sel event and timestamped OEM record types */
int ipmi_sel_parse_read_timestamp(ipmi_sel_parse_ctx_t ctx, uint32_t *timestamp);

/* generator_id, event message format version, sensor type, sensor
 * number, event direction, event type code, and event data available
 * form system event record type 
 */
int ipmi_sel_parse_read_generator_id(ipmi_sel_parse_ctx_t ctx, uint8_t *generator_id);
int ipmi_sel_parse_read_ipmb_device_lun(ipmi_sel_parse_ctx_t ctx, uint8_t *ipmb_device_lun);
int ipmi_sel_parse_read_channel_number(ipmi_sel_parse_ctx_t ctx, uint8_t *channel_number);
int ipmi_sel_parse_read_event_message_format_version(ipmi_sel_parse_ctx_t ctx, uint8_t *event_message_format_version);
int ipmi_sel_parse_read_sensor_type(ipmi_sel_parse_ctx_t ctx, uint8_t *sensor_type);
int ipmi_sel_parse_read_sensor_number(ipmi_sel_parse_ctx_t ctx, uint8_t *sensor_number);
int ipmi_sel_parse_read_event_direction(ipmi_sel_parse_ctx_t ctx, uint8_t *event_direction);
int ipmi_sel_parse_read_event_type_code(ipmi_sel_parse_ctx_t ctx, uint8_t *event_type_code);
int ipmi_sel_parse_read_event_data1(ipmi_sel_parse_ctx_t ctx, uint8_t *event_data1);
int ipmi_sel_parse_read_event_data1_offset_from_event_reading_type_code(ipmi_sel_parse_ctx_t ctx, 
                                                                        uint8_t *event_data1_offset);
int ipmi_sel_parse_read_event_data1_event_data2_flag(ipmi_sel_parse_ctx_t ctx, 
                                                     uint8_t *event_data2_flag);
int ipmi_sel_parse_read_event_data1_event_data3_flag(ipmi_sel_parse_ctx_t ctx, 
                                                     uint8_t *event_data3_flag);
int ipmi_sel_parse_read_event_data2(ipmi_sel_parse_ctx_t ctx, uint8_t *event_data2);
int ipmi_sel_parse_read_event_data3(ipmi_sel_parse_ctx_t ctx, uint8_t *event_data3);

/* manufacturer_id - works with sel timestamped OEM record types */
int ipmi_sel_parse_read_manufacturer_id(ipmi_sel_parse_ctx_t ctx, uint32_t *manufacturer_id);

/* oem - works with sel timestamped and non-timestamped OEM record types */
/* will return number of bytes written to buffer on success */
int ipmi_sel_parse_read_oem(ipmi_sel_parse_ctx_t ctx, uint8_t *buf, unsigned int buflen);

/* returns length of data written into buffer */
int ipmi_sel_parse_read_record(ipmi_sel_parse_ctx_t ctx, 
                               uint8_t *buf,
                               unsigned int buflen);

/*
 * create a string output of the SEL entry.
 *
 * String format - availability for output dependent on SEL record
 * type.
 *
 * Available in all SEL record types
 *
 * %i - record ID in decimal
 *
 * Available in SEL event and timestamped OEM SEL records
 *
 * %t - time in format H:M:S using 24 hour clock
 * %d - date in format D-M-YEAR
 *
 * Available in SEL event records
 *
 * %g - sensor group name
 * %s - sensor name
 * %e - offset from event/reading code type string
 * %f - event data 2 string [1]
 * %h - event data 3 string
 * %c - combined event data 2 and event data 3 string [2]
 * %p - event data 2 previous state string [3]
 * %s - event data 2 severity string [3]
 * %k - event direction
 *
 * [1] - if a previous state and a severity state string are available
 * from a discrete sensor, they are concataneted with the defined
 * separator in between.
 *
 * [2] - most useful for threshold events where trigger and threshold
 * readings are available.  The combined output can indicate if the
 * reading has gone greater than, less than, etc. to a threshold.  If a discrete
 * sensor, event strings will just be put into the same string together with
 * the defined separator.
 *
 * [3] - if event type code indicates a discrete sensor and event data 2
 * flag indicates a previous state and/or severity state is available.
 *
 * Available in timestamped OEM SEL records
 *
 * %m - manufacturer id
 *
 * Available in SEL timestamped and non-timestamped OEM record types
 *
 * %o - oem data in hex
 *
 * Misc
 *
 * %% - percent sign
 *
 * flags
 * 
 * VERBOSE
 *
 * Output slightly more verbose text for selected fields.  For example:
 *
 * - If a sensor does not have a name, output sensor number and
 *   generator id instead of just sensor number.
 * - If an event data string cannot be determined (i.e. it is OEM or
 *   not defined by IPMI), output both the data and event type code
 *   instead of just the event data.
 *
 * IGNORE_UNAVAILABLE_FIELD
 * 
 * If a field is not available for output (for example, a timestamp field
 * in a SEL entry w/o a timestamp field), do not return an error.  Output
 * nothing.
 *
 * OUTPUT_NOT_AVAILABLE
 * 
 * If a field is not available, do not output an empty string, output
 * "N/A" (coincides with IGNORE_UNAVAILABLE_FIELD)
 *
 * DATE_USE_SLASH
 *
 * Use a '/' instead of hyphens when outputting the date.
 *
 * DATE_MONTH_STRING
 *
 * Output a month name (Jan, Feb, Mar, etc.) instead of the month
 * number when outputting the date.
 *
 * LEGACY
 *
 * Output strings in legacy format.
 *
 * Returns length of data written to buffer.  If >= buflen, no null
 * termination exists in buffer.
 */
int ipmi_sel_parse_read_record_string(ipmi_sel_parse_ctx_t ctx, 
                                      char *fmt, 
                                      char *buf, 
                                      unsigned int buflen,
                                      unsigned int flags);

/* Utility functions */
int ipmi_sel_parse_clear_sel(ipmi_sel_parse_ctx_t ctx);

int ipmi_sel_parse_delete_sel_entry(ipmi_sel_parse_ctx_t ctx, uint16_t record_id);

/* like ipmi_sel_parse_read_record_string - but pass in arbitrary buffer */
int ipmi_sel_parse_format_record_string(ipmi_sel_parse_ctx_t ctx,
                                        char *fmt,
                                        uint8_t *record_buf,
                                        unsigned int record_buflen,
                                        char *buf,
                                        unsigned int buflen,
                                        unsigned int flags);

int ipmi_sel_record_type_class(uint8_t record_type);

#endif /* _IPMI_SEL_PARSE_H */