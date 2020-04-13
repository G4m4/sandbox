/// @file geometry.cc
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

#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "sandbox/src/geometry/geometry.h"

namespace sandbox {
namespace geometry {

ShapeConvex::ShapeConvex() : shape_(std::make_unique<sf::ConvexShape>()) {
  const sf::Color randomColor(std::rand() % 256, std::rand() % 256,
                              std::rand() % 256);
  shape_->setFillColor(randomColor);
}

ShapeConvex::~ShapeConvex() {}

void ShapeConvex::Set(std::vector<std::pair<float, float>> vertices) {
  const auto pointsCount = vertices.size();
  shape_->setPointCount(pointsCount);
  for (std::size_t i = 0; i < pointsCount; ++i) {
    shape_->setPoint(i, sf::Vector2f(vertices[i].first, vertices[i].second));
  }
}

void ShapeConvex::Draw(sf::RenderWindow &window) const { window.draw(*shape_); }

} // namespace geometry
} // namespace sandbox
