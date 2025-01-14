/*
 * Copyright © 2012 Canonical Ltd.
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

#include "mir/graphics/buffer_basic.h"
#include <atomic>

namespace mg = mir::graphics;

namespace
{
mg::BufferID generate_next_buffer_id()
{
    static std::atomic<uint32_t> next_id{0};

    return mg::BufferID(next_id.fetch_add(1));
}
}

mg::BufferBasic::BufferBasic() :
    buffer_id(generate_next_buffer_id())
{
}
