/* Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA */

//
#include "observer_server_actions.h"
#include "observer_trans.h"

int gcs_reset_master_logs(Binlog_transmit_param *param)
{
  register_server_reset_master();
  return 0;
}

int gcs_transmit_start(Binlog_transmit_param *param,
                       const char *log_file, my_off_t log_pos)
{
  return 0;
}

int gcs_transmit_stop(Binlog_transmit_param *param)
{
  return 0;
}

int gcs_reserve_header(Binlog_transmit_param *param,
                       unsigned char *header,
                       unsigned long size,
                       unsigned long *len)
{
  return 0;
}

int gcs_before_send_event(Binlog_transmit_param *param,
                          unsigned char *packet, unsigned long len,
                          const char *log_file, my_off_t log_pos)
{
  return 0;
}

int gcs_after_send_event(Binlog_transmit_param *param,
                         const char *event_buf, unsigned long len,
                         const char *skipped_log_file,
                         my_off_t skipped_log_pos)
{
  return 0;
}

Binlog_transmit_observer binlog_transmit_observer = {
  sizeof(Binlog_transmit_observer),

  gcs_transmit_start,     // transmit_start,
  gcs_transmit_stop,      // transmit_stop,
  gcs_reserve_header,     // reserve_header,
  gcs_before_send_event,  // before_send_event,
  gcs_after_send_event,   // after_send_event,
  gcs_reset_master_logs   // reset_master
};