/*
 * Copyright © 2019 Canonical Ltd.
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

#ifndef MIR_RENDERINGPLATFORM_H
#define MIR_RENDERINGPLATFORM_H

#include "mir/graphics/platform.h"

namespace mir
{
namespace graphics
{
namespace rpi
{
class RenderingPlatform : public graphics::RenderingPlatform
{
public:
    UniqueModulePtr<GraphicBufferAllocator> create_buffer_allocator(Display const &output) override;
};
}
}
}

#endif  // MIR_RENDERINGPLATFORM_H
