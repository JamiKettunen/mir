/*
 * Copyright © 2013 Canonical Ltd.
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


#ifndef MIR_SCENE_SCENE_REPORT_H_
#define MIR_SCENE_SCENE_REPORT_H_

#include <memory>

namespace mir
{
namespace scene
{
class SceneReport
{
public:
    typedef void* BasicSurfaceId;
    virtual void surface_created(BasicSurfaceId id, std::string const& name) = 0;
    virtual void surface_added(BasicSurfaceId id, std::string const& name) = 0;

    virtual void surface_removed(BasicSurfaceId id, std::string const& name) = 0;
    virtual void surface_deleted(BasicSurfaceId id, std::string const& name) = 0;

protected:
    SceneReport() = default;
    virtual ~SceneReport() = default;
    SceneReport(SceneReport const&) = delete;
    SceneReport& operator=(SceneReport const&) = delete;
};

}
}

#endif /* MIR_SCENE_SCENE_REPORT_H_ */
