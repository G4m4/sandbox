/// @file context.cc
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

#include <SFML/Graphics.hpp>

#include "sandbox/src/context/context.h"
#include "sandbox/src/geometry/geometry.h"

namespace sandbox {
namespace context {

Context::Context()
    : window_(std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 768), "Sandbox")),
      should_close_(false) {}

Context::~Context() {}

void Context::Initialize() {
  window_->setVerticalSyncEnabled(true);
}

void Context::Terminate() {
  window_->close();
}

void Context::Update() {
  sf::Event event;
  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      should_close_ = true;
    }
  }

void Context::Clear() {
  window_->clear();
}

void Context::Render() {
}

void Context::Display() {
  window_->display();
}

void Context::Draw(const geometry::ShapeConvex & shape) {
  shape.Draw(*window_);
}

bool Context::ShouldClose() const { return should_close_; }

} // namespace context
} // namespace sandbox
