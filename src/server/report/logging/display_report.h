/*
 * Copyright © 2012 Canonical Ltd.
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


#ifndef MIR_REPORT_LOGGING_DISPLAY_REPORTER_H_
#define MIR_REPORT_LOGGING_DISPLAY_REPORTER_H_

#include "mir/graphics/display_report.h"
#include "mir/graphics/frame.h"

#include <unordered_map>
#include <memory>
#include <mutex>

namespace mir
{
namespace logging
{
class Logger;
}
namespace graphics { struct Frame; }
namespace report
{
namespace logging
{

class DisplayReport : public graphics::DisplayReport
{
  public:

    static const char* component();

    DisplayReport(
        std::shared_ptr<mir::logging::Logger> const& logger);

    virtual ~DisplayReport();

    virtual void report_successful_setup_of_native_resources() override;
    virtual void report_successful_egl_make_current_on_construction() override;
    virtual void report_successful_egl_buffer_swap_on_construction() override;
    virtual void report_successful_drm_mode_set_crtc_on_construction() override;
    virtual void report_successful_display_construction() override;
    virtual void report_vsync(unsigned int output_id, graphics::Frame const&) override;
    virtual void report_drm_master_failure(int error) override;
    virtual void report_vt_switch_away_failure() override;
    virtual void report_vt_switch_back_failure() override;
    virtual void report_egl_configuration(EGLDisplay disp, EGLConfig cfg) override;

  protected:
    DisplayReport(DisplayReport const&) = delete;
    DisplayReport& operator=(DisplayReport const&) = delete;

  private:
    std::shared_ptr<mir::logging::Logger> const logger;
    std::mutex vsync_event_mutex;
    std::unordered_map<unsigned int, mir::graphics::Frame> prev_frame;
};
}
}
}

#endif /* MIR_REPORT_LOGGING_DISPLAY_REPORTER_H_ */
