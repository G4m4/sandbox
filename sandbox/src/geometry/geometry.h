/// @file geometry.h
/// @brief Various geometry stuff
/// @author gm
/// @copyright gm 2020
///
/// This file is part of SandBox
///
/// SandBox is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// SandBox is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with SandBox.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SANDBOX_GEOMETRY_H_
#define SANDBOX_GEOMETRY_H_

#include <memory>
#include <utility>
#include <vector>

#include "sandbox/src/common.h"

namespace sf {
class ConvexShape;
class RenderWindow;
} // namespace sf

namespace sandbox {
namespace geometry {

/// @brief A convex shape to be drawn
class ShapeConvex {
public:
  ShapeConvex();
  ~ShapeConvex();

  void Set(std::vector<std::pair<float, float>> vertices);
  void Draw(sf::RenderWindow &window) const;

private:
  std::unique_ptr<sf::ConvexShape> shape_;
};

} // namespace geometry
} // namespace sandbox

#endif // SANDBOX_GEOMETRY_H_
