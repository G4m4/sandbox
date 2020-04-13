/// @file context.h
/// @brief Base context object to spawn windows
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

#ifndef SANDBOX_CONTEXT_H_
#define SANDBOX_CONTEXT_H_

#include <memory>

#include "sandbox/src/common.h"

namespace sf {
  class RenderWindow;
}

namespace sandbox {

namespace geometry {
class ShapeConvex;
}

namespace context {

/// @brief Context object, where everything lives at the moment
class Context {
 public:
  Context();
  ~Context();

  void Initialize();
  void Terminate();

  void Update();

  void Clear();
  void Render();
  void Display();

  void Draw(const geometry::ShapeConvex & shape);
  bool ShouldClose() const;

 private:
  void CreateImGuiWidgets(sf::RenderWindow & window);

  std::unique_ptr<sf::RenderWindow> window_;
  bool should_close_;
};

}  // namespace context
}  // namespace sandbox

#endif  // SANDBOX_CONTEXT_H_
