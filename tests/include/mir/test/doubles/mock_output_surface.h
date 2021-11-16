/*
 * Copyright © 2015 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or 3 as
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
 * Authored by: Christopher James Halse Rogers <christopher.halse.rogers@canonical.com>
 */

#ifndef MIR_TEST_DOUBLES_MOCK_OUTPUT_SURFACE_H_
#define MIR_TEST_DOUBLES_MOCK_OUTPUT_SURFACE_H_

#include <gmock/gmock.h>

#include "mir/renderer/gl/gl_surface.h"

namespace mir::test::doubles
{
class MockOutputSurface : public mir::graphics::gl::OutputSurface
{
public:
    MOCK_METHOD(void, bind, (), (override));
    MOCK_METHOD(void, make_current, (), (override));
    MOCK_METHOD(std::unique_ptr<graphics::Framebuffer>, commit, (), (override));
    MOCK_METHOD(Layout, layout, (), (const override));
};
}

#endif //MIR_TEST_DOUBLES_MOCK_OUTPUT_SURFACE_H_
