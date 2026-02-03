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

#include "sandbox/dummygroup/dummygroup.h"

#if SANDBOX_ANDROID
#include "imgui_android.cc"
#else
#include "imgui_vulkan.cc"
#endif

// Main code
void android_main(struct android_app* app) {
  auto base = sandbox::dummygroup::DummyGroup::Make();

  app->onAppCmd = handleAppCmd;
  app->onInputEvent = handleInputEvent;

  while (true) {
    int out_events;
    struct android_poll_source* out_data;

    // Poll all events. If the app is not visible, this loop blocks until g_Initialized == true.
    while (ALooper_pollOnce(g_Initialized ? 0 : -1, nullptr, &out_events,
                            (void**)&out_data)
           >= 0) {
      // Process one event
      if (out_data != nullptr)
        out_data->process(app, out_data);

      // Exit the app by returning from within the infinite loop
      if (app->destroyRequested != 0) {
        // shutdown() should have been called already while processing the
        // app command APP_CMD_TERM_WINDOW. But we play save here
        if (!g_Initialized)
          Shutdown();

        return;
      }
    }

    // Initiate a new frame
    UIFrame([&base]() {
      // Create a window called "Hello, world!" and append into it.
      ImGui::Begin("Sandbox");

      ImGui::Text("%s", base->GetSomething());
      ImGui::End();
    });
  }
}
