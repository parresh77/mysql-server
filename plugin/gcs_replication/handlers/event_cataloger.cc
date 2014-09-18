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

#include "event_cataloger.h"
#include <log_event.h>

Event_cataloger::Event_cataloger() {}

int
Event_cataloger::initialize()
{
  return 0;
}

int
Event_cataloger::terminate()
{
  return 0;
}

int
Event_cataloger::handle_event(PipelineEvent *pevent, Continuation *cont)
{
  Log_event_type event_type= pevent->get_event_type();

  if (event_type == TRANSACTION_CONTEXT_EVENT)
  {
    pevent->mark_event(TRANSACTION_BEGIN);
  }
  else
  {
    pevent->mark_event(UNMARKED_EVENT);
  }

  //Check if the current transaction was discarded
  if (cont->is_transaction_discarded())
  {
    if (pevent->get_event_context() == TRANSACTION_BEGIN ||
        pevent->get_event_type() == VIEW_CHANGE_EVENT)
    {
      //a new transaction begins
      cont->set_transation_discarded(false);
    }
    else
    {
      //The event belongs to a discarded transaction
      cont->signal(0, true);
      return 0;
    }
  }

  next(pevent, cont);
  return 0;
}

int Event_cataloger::handle_action(PipelineAction *action){
  return(next(action));
}

bool Event_cataloger::is_unique()
{
  return true;
}

int Event_cataloger::get_role()
{
  return EVENT_CATALOGER;
}

