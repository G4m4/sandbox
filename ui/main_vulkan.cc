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

#include "sandbox/common.h"
#include "sandbox/dummygroup/dummygroup.h"

#include "imgui_vulkan.cc"

#if !OS_WINDOWS && !OS_LINUX && !OS_OSX
static_assert(false, "main function for desktop only");
#endif  // desktop

int main(int /*argc*/, char** /*argv*/) {
  auto base = sandbox::dummygroup::DummyGroup::Make();

  // Initiate a new frame
  UILoop([&base]() {
    // Create a window called "Hello, world!" and append into it.
    ImGui::Begin("Sandbox");

    ImGui::Text("%s", base->GetSomething());
    ImGui::End();
  });
}
