/// @file sandbox.h
/// @brief SandBox UI class implementation
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

#include "sandbox/implementation/ui/sandbox.h"

#include "externals/imgui/imgui.h"

///////////////////////////////////////////////////////////////////////////////
// Based on alpqr implementation: https://github.com/alpqr/imgui-qtquick
///////////////////////////////////////////////////////////////////////////////

Sandbox::Sandbox() :
  dummy_class_instance_(new sandbox::dummygroup::DummyClass())  {
}

void Sandbox::frame() {
  // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
  {
    static ImVec4 clear_color{ 0.45f, 0.55f, 0.60f, 1.00f };
    static float f = 0.0f;
    static int counter = 0;
    ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("%s", dummy_class_instance_->DoSomething());
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }

  // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
  if (show_another_window) {
    ImGui::Begin("Another Window", &show_another_window);
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }

  // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
  if (show_demo_window) {
    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
    ImGui::ShowDemoWindow(&show_demo_window);
  }
}
