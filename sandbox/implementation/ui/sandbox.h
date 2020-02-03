/// @file sandbox.h
/// @brief SandBox UI class header
/// @author gm
/// @copyright gm 2019
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

#ifndef SANDBOX_SRC_IMPLEMENTATION_SANDBOX_H
#define SANDBOX_SRC_IMPLEMENTATION_SANDBOX_H

#include "sandbox/src/dummygroup/dummyclass.h"
#include <QScopedPointer>
#include <memory>
#include <vector>

namespace sandbox {
namespace imgui {

namespace nodegraph {
struct CanvasState;
}

class Sandbox {
public:
  Sandbox();
  ~Sandbox();
  void frame();

private:
  QScopedPointer<sandbox::dummygroup::DummyClass> dummy_class_instance_;
  std::vector<std::unique_ptr<struct MyNode>> nodes_;
  std::unique_ptr<nodegraph::CanvasState> canvas_;
};

} // namespace imgui
} // namespace sandbox

#endif // SANDBOX_SRC_IMPLEMENTATION_SANDBOX_H
