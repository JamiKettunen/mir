/*
 * Copyright © 2022 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 or 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "mir/test/doubles/stub_buffer_allocator.h"
#include "mir/test/doubles/stub_buffer.h"
#include "mir_test_framework/stub_platform_native_buffer.h"
#include "mir_toolkit/client_types.h"
#include "src/platforms/common/server/buffer_from_wl_shm.h"
#include "mir/graphics/egl_context_executor.h"
#include "mir/test/doubles/null_gl_context.h"
#include <wayland-server.h>

#include <vector>
#include <memory>

namespace mtd = mir::test::doubles;
namespace mg = mir::graphics;
namespace geometry = mir::geometry;

namespace
{
inline void memcpy_from_shm_buffer(struct wl_shm_buffer* buffer)
{
    auto const height = wl_shm_buffer_get_height(buffer);
    auto const stride = wl_shm_buffer_get_stride(buffer);
    // The 32 here is a workaround for a spurious(?) Valgrind failure
    auto dummy_destination = std::make_unique<unsigned char[]>(height * stride + 32);

    wl_shm_buffer_begin_access(buffer);
    memcpy(dummy_destination.get(), wl_shm_buffer_get_data(buffer), height * stride);
    wl_shm_buffer_end_access(buffer);
}
}

auto mtd::StubBufferAllocator::alloc_software_buffer(geometry::Size sz, MirPixelFormat pf) -> std::shared_ptr<mg::Buffer>
{
    graphics::BufferProperties properties{sz, pf, graphics::BufferUsage::software};
    return std::make_shared<StubBuffer>(std::make_shared<mir_test_framework::NativeBuffer>(properties), properties, geometry::Stride{sz.width.as_uint32_t() * MIR_BYTES_PER_PIXEL(pf)});
}

auto mtd::StubBufferAllocator::supported_pixel_formats() -> std::vector<MirPixelFormat>
{
    return { mir_pixel_format_argb_8888 };
}

void mtd::StubBufferAllocator::bind_display(wl_display*, std::shared_ptr<mir::Executor>)
{
}

void mtd::StubBufferAllocator::unbind_display(wl_display*)
{
}

auto mtd::StubBufferAllocator::buffer_from_resource(wl_resource*, std::function<void()>&&, std::function<void()>&&)
    -> std::shared_ptr<mg::Buffer>
{
    BOOST_THROW_EXCEPTION((std::runtime_error{"StubBufferAllocator doesn't do HW Wayland buffers"}));
}

auto mtd::StubBufferAllocator::buffer_from_shm(
    wl_resource* resource,
    std::shared_ptr<mir::Executor> executor,
    std::function<void()>&& on_consumed) -> std::shared_ptr<mg::Buffer>
{
    // Temporary(?!) hack to actually use the buffer, for WLCS test
    // Transitioning the StubGraphicsPlatform to use the MESA surfaceless GL platform would
    // allow us to test more of Mir, and drop this hack
    memcpy_from_shm_buffer(wl_shm_buffer_get(resource));

    return mg::wayland::buffer_from_wl_shm(
        resource,
        std::move(executor),
        std::make_shared<mg::common::EGLContextExecutor>(std::make_unique<mtd::NullGLContext>()),
        std::move(on_consumed));
}
