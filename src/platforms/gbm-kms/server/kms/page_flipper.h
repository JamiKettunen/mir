/*
 * Copyright © 2013 Canonical Ltd.
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

#ifndef MIR_GRAPHICS_GBM_PAGE_FLIPPER_H_
#define MIR_GRAPHICS_GBM_PAGE_FLIPPER_H_

#include "mir/graphics/frame.h"
#include <cstdint>

namespace mir
{
namespace graphics
{
namespace gbm
{

class PageFlipper
{
public:
    virtual ~PageFlipper() {}

    virtual bool schedule_flip(uint32_t crtc_id, uint32_t fb_id, uint32_t connector_id) = 0;
    virtual Frame wait_for_flip(uint32_t crtc_id) = 0;

protected:
    PageFlipper() = default;
    PageFlipper(PageFlipper const&) = delete;
    PageFlipper& operator=(PageFlipper const&) = delete;
};

}
}
}

#endif /* MIR_GRAPHICS_GBM_PAGE_FLIPPER_H_ */
