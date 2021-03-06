/*
 * Copyright (C) 2003-2013 FreeIPMI Core Team
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

#ifndef CONFIG_TOOL_ARGP_H
#define CONFIG_TOOL_ARGP_H

#if HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdint.h>

#if HAVE_ARGP_H
#include <argp.h>
#else /* !HAVE_ARGP_H */
#include "freeipmi-argp.h"
#endif /* !HAVE_ARGP_H */

#include "config-tool-common.h"

enum config_argp_option_keys
  {
    CONFIG_ARGP_CHECKOUT_KEY = 'o',
    CONFIG_ARGP_COMMIT_KEY = 'c',
    CONFIG_ARGP_DIFF_KEY = 'd',
    CONFIG_ARGP_FILENAME_KEY_LEGACY = 'f',
    CONFIG_ARGP_FILENAME_KEY = 'n',
    CONFIG_ARGP_KEYPAIR_KEY = 'e',
    CONFIG_ARGP_SECTIONS_KEY = 'S',
    CONFIG_ARGP_LIST_SECTIONS_KEY = 'L',
    CONFIG_ARGP_VERBOSE_KEY = 'v',
    CONFIG_ARGP_LAN_CHANNEL_NUMBER_KEY = 200,
    CONFIG_ARGP_SERIAL_CHANNEL_NUMBER_KEY = 201,
    CONFIG_ARGP_SOL_CHANNEL_NUMBER_KEY = 202,
  };

#define CONFIG_ARGP_COMMON_OPTIONS                                                        \
  { "checkout", CONFIG_ARGP_CHECKOUT_KEY, 0, 0,                                           \
      "Fetch configuration information.", 51},                                            \
  { "commit", CONFIG_ARGP_COMMIT_KEY, 0, 0,                                               \
      "Update configuration information from a config file or key pairs.", 52},           \
  { "diff", CONFIG_ARGP_DIFF_KEY, 0, 0,                                                   \
      "Show differences between stored information and a config file or key pairs.", 53}, \
  { "filename", CONFIG_ARGP_FILENAME_KEY, "FILENAME", 0,                                  \
      "Specify a config file for checkout/commit/diff.", 54},                             \
  { "key-pair", CONFIG_ARGP_KEYPAIR_KEY, "KEY-PAIR", 0,                                   \
      "Specify KEY=VALUE pairs for checkout/commit/diff.", 55},                           \
  { "section", CONFIG_ARGP_SECTIONS_KEY, "SECTION", 0,                                    \
      "Specify a SECTION for checkout.", 56},                                             \
  { "listsections", CONFIG_ARGP_LIST_SECTIONS_KEY, 0, 0,                                  \
      "List available sections for checkout.", 57},                                       \
  { "verbose", CONFIG_ARGP_VERBOSE_KEY, 0, 0,                                             \
      "Print additional detailed information.", 58}

#define CONFIG_ARGP_LAN_CHANNEL_OPTION                                                    \
  { "lan-channel-number", CONFIG_ARGP_LAN_CHANNEL_NUMBER_KEY, "NUMBER", 0,                \
      "Use a specific LAN Channel Number.", 59}

#define CONFIG_ARGP_SERIAL_CHANNEL_OPTION                                                 \
  { "serial-channel-number", CONFIG_ARGP_SERIAL_CHANNEL_NUMBER_KEY, "NUMBER", 0,          \
      "Use a specific Serial Channel Number.", 60}

#define CONFIG_ARGP_SOL_CHANNEL_OPTION                                                    \
  { "sol-channel-number", CONFIG_ARGP_SOL_CHANNEL_NUMBER_KEY, "NUMBER", 0,                \
      "Use a specific SOL Channel Number.", 60}

/* legacy short-option */
#define CONFIG_ARGP_COMMON_OPTIONS_LEGACY                \
  { "foobar", CONFIG_ARGP_FILENAME_KEY_LEGACY, "FILENAME", OPTION_HIDDEN, \
      "Specify a config file for checkout/commit/diff.", 61}

void init_config_args (struct config_arguments *config_args);

error_t config_parse_opt (int key,
                          char *arg,
                          struct config_arguments *config_args);

void config_args_validate (struct config_arguments *config_args);

#endif /* CONFIG_TOOL_ARGP_H */
