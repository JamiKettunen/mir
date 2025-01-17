/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 2 or 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIR_GRAPHICS_GAMMA_CURVES_H_
#define MIR_GRAPHICS_GAMMA_CURVES_H_

#include <cstdint>
#include <vector>

namespace mir
{
namespace graphics
{

typedef std::vector<uint16_t> GammaCurve;

class GammaCurves
{
public:
    GammaCurves() = default;
    GammaCurves(GammaCurves const& other) = default;
    GammaCurves(GammaCurves&& other) = default;

    GammaCurves(GammaCurve const& red,
                GammaCurve const& green,
                GammaCurve const& blue);

    GammaCurves& operator=(GammaCurves const& other) = default;
    GammaCurves& operator=(GammaCurves&& other) = default;

    GammaCurve red;
    GammaCurve green;
    GammaCurve blue;
};

class LinearGammaLUTs : public GammaCurves
{
public:
    explicit LinearGammaLUTs(int size);
};

}
}

#endif
