/*
 * Copyright © 2018 Canonical Ltd.
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
 *
 * Authored by: Christopher James Halse Rogers <christopher.halse.rogers@canonical.com>
 */

#ifndef MIR_PLATFORM_TEXTURE_H_
#define MIR_PLATFORM_TEXTURE_H_

namespace mir
{
namespace graphics
{
namespace gl
{

class Program;
class ProgramFactory;

class Texture
{
public:
    Texture() = default;
    virtual ~Texture();

    Texture(Texture const&) = delete;
    Texture& operator=(Texture const&) = delete;

    virtual Program const& shader(ProgramFactory& cache) const = 0;

    virtual bool y_inverted() const = 0;
    virtual void bind() = 0;
    virtual void add_syncpoint() = 0;
};
}
}
}

#endif //MIR_PLATFORM_TEXTURE_H_
