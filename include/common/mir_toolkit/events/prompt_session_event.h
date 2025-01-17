/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 2 or 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIR_TOOLKIT_EVENTS_PROMPT_SESSION_EVENT_H_
#define MIR_TOOLKIT_EVENTS_PROMPT_SESSION_EVENT_H_

#include <mir_toolkit/events/event.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Retrieve the new prompt session state reported by a given MirPromptSessionEvent
 *
 * \param [in] event The prompt session event
 * \return           The new state
 */
MirPromptSessionState mir_prompt_session_event_get_state(MirPromptSessionEvent const* event);

#ifdef __cplusplus
}
#endif

#endif /* MIR_TOOLKIT_PROMPT_SESSION_EVENT_H_ */
