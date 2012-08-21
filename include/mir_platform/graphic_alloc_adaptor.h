/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */
#ifndef MIR_PLATFORM_GRAPHIC_ALLOC_ADAPTOR_H_
#define MIR_PLATFORM_GRAPHIC_ALLOC_ADAPTOR_H_

/* NOTE: TO GO AWAY --kdub */
#include <hardware/gralloc.h>
#include <mir/geometry/dimensions.h>
#include <mir/compositor/buffer.h>
namespace mir
{

namespace graphics
{

class BufferData {};

class GraphicAllocAdaptor 
{
public:
    virtual bool alloc_buffer(BufferData&, geometry::Stride&,
                             geometry::Width, geometry::Height, compositor::PixelFormat, int usage) = 0;

    virtual bool free_buffer(BufferData handle) = 0;
    virtual bool inspect_buffer(char *buf, int buf_len) = 0;
};

}
}

#endif /* MIR_PLATFORM_GRAPHIC_ALLOC_ADAPTOR_H_ */
