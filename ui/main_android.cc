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

#include "imgui_android.cc"

#if !OS_ANDROID
static_assert(false, "main function for Android only");
#endif

void android_main(struct android_app* app) {
  app->onAppCmd = handleAppCmd;
  app->onInputEvent = handleInputEvent;

  auto base = sandbox::dummygroup::DummyGroup::Make();

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

    UIFrame([&base]() {
      // Create a window called "Hello, world!" and append into it.
      ImGui::Begin("Sandbox");

      ImGui::Text("%s", base->GetSomething());
      ImGui::End();
    });
  }
}
