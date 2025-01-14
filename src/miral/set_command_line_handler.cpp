/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 or 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "miral/set_command_line_handler.h"

#include <mir/server.h>

miral::SetCommandLineHandler::SetCommandLineHandler(Handler const& handler) :
    handler{handler}
{
}

miral::SetCommandLineHandler::~SetCommandLineHandler() = default;

void miral::SetCommandLineHandler::operator()(mir::Server& server) const
{
    server.set_command_line_handler(handler);
}
