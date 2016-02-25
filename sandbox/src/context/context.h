/// @file context.h
/// @brief Base context object to spawn windows
/// @author gm
/// @copyright gm 2016
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

#include "sandbox/src/common.h"

struct GLFWwindow;

namespace sandbox {
namespace context {

/// @brief Context object, where everything lives at the moment
class SANDBOX_API Context {
 public:
  Context();
  ~Context();

  bool Initialize();
  void Terminate();

  void Clear();
  void Update();
  bool ShouldClose();

 private:
  GLFWwindow* window_;
};

}  // namespace context
}  // namespace sandbox

#endif  // SANDBOX_CONTEXT_H_
