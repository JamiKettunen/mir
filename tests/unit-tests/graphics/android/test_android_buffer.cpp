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

#include "mir_platform/android/android_buffer.h"
#include "mir_platform/graphic_alloc_adaptor.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

namespace mc=mir::compositor;
namespace mg=mir::graphics;
namespace geom=mir::geometry;

namespace mir
{
namespace graphics
{
class MockAllocAdaptor : public GraphicAllocAdaptor,
                         public alloc_device_t 
{
    public:
    MockAllocAdaptor(buffer_handle_t buf_handle)
    {
        using namespace testing;

        buffer_handle = buf_handle;
#if 0 
        alloc = hook_alloc;
        free = hook_free;
        dump = hook_dump;
#endif
        ON_CALL(*this, alloc_buffer(_,_,_,_,_,_))
                .WillByDefault(DoAll(
                            SaveArg<0>(&w),
                            SetArgPointee<4>(buffer_handle),
                            SetArgPointee<5>(w * 4), /* stride must be >= (bpp * width). 4bpp is the max supported */
                            Return(0)));
        ON_CALL(*this, free_buffer(_))
                .WillByDefault(Return(0));
    }
#if 0
    static int hook_alloc(alloc_device_t* mock_alloc,
                           int w, int h, int format, int usage,
                           buffer_handle_t* handle, int* stride)
    {
        MockAllocAdaptor* mocker = static_cast<MockAllocAdaptor*>(mock_alloc);
        return mocker->alloc_buffer(mock_alloc, w, h, format, usage, handle, stride);
    }

    static int hook_free(alloc_device_t* mock_alloc, buffer_handle_t handle)
    {
        MockAllocAdaptor* mocker = static_cast<MockAllocAdaptor*>(mock_alloc);
        return mocker->free_buffer(handle);
    }

    static void hook_dump(alloc_device_t* mock_alloc, char* buf, int buf_len)
    {
        MockAllocAdaptor* mocker = static_cast<MockAllocAdaptor*>(mock_alloc);
        mocker->inspect_buffer(mock_alloc, buf, buf_len);
    }
#endif
    MOCK_METHOD6(alloc_buffer, int(int, int, int, int, buffer_handle_t*, int*) );

    MOCK_METHOD1(free_buffer,  int(buffer_handle_t)); 
    MOCK_METHOD2(inspect_buffer, bool(char*, int));
    
    private:
    buffer_handle_t buffer_handle;
    int w;
        
};
}
}

class AndroidGraphicBufferBasic : public ::testing::Test
{
    protected:
    virtual void SetUp()
    {
        dummy_handle = &native_handle;
        mock_alloc_device = std::shared_ptr<mg::MockAllocAdaptor> (new mg::MockAllocAdaptor(dummy_handle));

        /* set up common defaults */
        pf = mc::PixelFormat::rgba_8888;
        width = geom::Width(300);
        height = geom::Height(200);

    }

    native_handle_t native_handle;
    buffer_handle_t dummy_handle;
    std::shared_ptr<mg::MockAllocAdaptor> mock_alloc_device;
    mc::PixelFormat pf;
    geom::Width width;
    geom::Height height;
};


TEST_F(AndroidGraphicBufferBasic, struct_mock) 
{
    EXPECT_CALL(*mock_alloc_device, free_buffer( NULL));
    mock_alloc_device->free_buffer( NULL);
}

#if 0
/* tests correct allocation type */
TEST_F(AndroidGraphicBufferBasic, resource_test) 
{
    using namespace testing;

    EXPECT_CALL(*mock_alloc_device, alloc_buffer(mock_alloc_device, _, _, _,
                                         (GRALLOC_USAGE_HW_TEXTURE | GRALLOC_USAGE_HW_RENDER),
                                          _, _ ));
    EXPECT_CALL(*mock_alloc_device, free_buffer(mock_alloc_device.get(), dummy_handle));

    std::shared_ptr<mc::Buffer> buffer(new mg::AndroidBuffer(mock_alloc_device, width, height, pf));

    EXPECT_NE((int)buffer.get(), NULL);
}

TEST_F(AndroidGraphicBufferBasic, dimensions_gralloc_conversion) 
{
    using namespace testing;

    EXPECT_CALL(*mock_alloc_device, mock_alloc(_,
                                 (int)width.as_uint32_t(), (int)height.as_uint32_t(),
                                  _, _ , _, _ ));
    EXPECT_CALL(*mock_alloc_device, mock_free(_,_));
    std::shared_ptr<mc::Buffer> buffer(new mg::AndroidBuffer(mock_alloc_device, width, height, pf));

    EXPECT_EQ(width, buffer->width());
    EXPECT_EQ(height, buffer->height());
}

TEST_F(AndroidGraphicBufferBasic, format_test_8888_gralloc_conversion) 
{
    using namespace testing;

    EXPECT_CALL(*mock_alloc_device, mock_alloc(_, _, _, HAL_PIXEL_FORMAT_RGBA_8888, _ , _, _ ));
    EXPECT_CALL(*mock_alloc_device, mock_free(_,_));
    std::shared_ptr<mc::Buffer> buffer(new mg::AndroidBuffer(mock_alloc_device, width, height, pf));

}

TEST_F(AndroidGraphicBufferBasic, dimensions_echo) 
{
    using namespace testing;

    EXPECT_CALL(*mock_alloc_device, mock_alloc(_, _, _, _, _ , _, _ ));
    EXPECT_CALL(*mock_alloc_device, mock_free(_,_));
    std::shared_ptr<mc::Buffer> buffer(new mg::AndroidBuffer(mock_alloc_device, width, height, pf));

    EXPECT_EQ(width, buffer->width());
    EXPECT_EQ(height, buffer->height());

}

TEST_F(AndroidGraphicBufferBasic, format_echo_test)
{
    using namespace testing;

    EXPECT_CALL(*mock_alloc_device, mock_alloc(_, _, _, _, _ , _, _ ));
    EXPECT_CALL(*mock_alloc_device, mock_free(_,_));
    std::shared_ptr<mc::Buffer> buffer(new mg::AndroidBuffer(mock_alloc_device, width, height, pf));

    EXPECT_EQ(buffer->pixel_format(), pf);

}
#endif
