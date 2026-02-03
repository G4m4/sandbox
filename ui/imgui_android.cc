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

// This is mostly code copied from imgui-src/examples/example_glfw_vulkan/main.cpp

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <stdio.h>   // printf, fprintf
#include <stdlib.h>  // abort
#include <string>
#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"

namespace {
// Data
EGLDisplay g_EglDisplay = EGL_NO_DISPLAY;
EGLSurface g_EglSurface = EGL_NO_SURFACE;
EGLContext g_EglContext = EGL_NO_CONTEXT;
struct android_app* g_App = nullptr;
bool g_Initialized = false;
char g_LogTag[] = "ImGuiExample";
std::string g_IniFilename = "";

// Forward declarations of helper functions
void Init(struct android_app* app);
void Shutdown();
int ShowSoftKeyboardInput();
int PollUnicodeChars();
int GetAssetData(const char* filename, void** out_data);

// Main code
void handleAppCmd(struct android_app* app, int32_t appCmd) {
  switch (appCmd) {
    case APP_CMD_SAVE_STATE:
      break;
    case APP_CMD_INIT_WINDOW:
      Init(app);
      break;
    case APP_CMD_TERM_WINDOW:
      Shutdown();
      break;
    case APP_CMD_GAINED_FOCUS:
    case APP_CMD_LOST_FOCUS:
      break;
  }
}

int32_t handleInputEvent(struct android_app* app, AInputEvent* inputEvent) {
  return ImGui_ImplAndroid_HandleInputEvent(inputEvent);
}

void Init(struct android_app* app) {
  if (g_Initialized)
    return;

  g_App = app;
  ANativeWindow_acquire(g_App->window);

  // Initialize EGL
  // This is mostly boilerplate code for EGL...
  {
    g_EglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (g_EglDisplay == EGL_NO_DISPLAY)
      __android_log_print(
          ANDROID_LOG_ERROR, g_LogTag, "%s",
          "eglGetDisplay(EGL_DEFAULT_DISPLAY) returned EGL_NO_DISPLAY");

    if (eglInitialize(g_EglDisplay, 0, 0) != EGL_TRUE)
      __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s",
                          "eglInitialize() returned with an error");

    const EGLint egl_attributes[] = {EGL_BLUE_SIZE,    8,
                                     EGL_GREEN_SIZE,   8,
                                     EGL_RED_SIZE,     8,
                                     EGL_DEPTH_SIZE,   24,
                                     EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                                     EGL_NONE};
    EGLint num_configs = 0;
    if (eglChooseConfig(g_EglDisplay, egl_attributes, nullptr, 0, &num_configs)
        != EGL_TRUE)
      __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s",
                          "eglChooseConfig() returned with an error");
    if (num_configs == 0)
      __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s",
                          "eglChooseConfig() returned 0 matching config");

    // Get the first matching config
    EGLConfig egl_config;
    eglChooseConfig(g_EglDisplay, egl_attributes, &egl_config, 1, &num_configs);
    EGLint egl_format;
    eglGetConfigAttrib(g_EglDisplay, egl_config, EGL_NATIVE_VISUAL_ID,
                       &egl_format);
    ANativeWindow_setBuffersGeometry(g_App->window, 0, 0, egl_format);

    const EGLint egl_context_attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 3,
                                             EGL_NONE};
    g_EglContext = eglCreateContext(g_EglDisplay, egl_config, EGL_NO_CONTEXT,
                                    egl_context_attributes);

    if (g_EglContext == EGL_NO_CONTEXT)
      __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s",
                          "eglCreateContext() returned EGL_NO_CONTEXT");

    g_EglSurface = eglCreateWindowSurface(g_EglDisplay, egl_config,
                                          g_App->window, nullptr);
    eglMakeCurrent(g_EglDisplay, g_EglSurface, g_EglSurface, g_EglContext);
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  // Redirect loading/saving of .ini file to our location.
  // Make sure 'g_IniFilename' persists while we use Dear ImGui.
  g_IniFilename = std::string(app->activity->internalDataPath) + "/imgui.ini";
  io.IniFilename = g_IniFilename.c_str();
  ;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplAndroid_Init(g_App->window);
  ImGui_ImplOpenGL3_Init("#version 300 es");

  // Setup scaling
  float main_scale = 2.0f;
  ImGuiStyle& style = ImGui::GetStyle();
  style.ScaleAllSizes(
      main_scale);  // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
  style.FontScaleDpi = main_scale;  // Set initial font scale.

  // Load Fonts
  // - If fonts are not explicitly loaded, Dear ImGui will call AddFontDefault() to select an embedded font: either AddFontDefaultVector() or AddFontDefaultBitmap().
  //   This selection is based on (style.FontSizeBase * style.FontScaleMain * style.FontScaleDpi) reaching a small threshold.
  // - You can load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - If a file cannot be loaded, AddFont functions will return a nullptr. Please handle those errors in your code (e.g. use an assertion, display an error and quit).
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use FreeType for higher quality font rendering.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  // - Android: The TTF files have to be placed into the assets/ directory (android/app/src/main/assets), we use our GetAssetData() helper to retrieve them.
  //style.FontSizeBase = 20.0f;
  //io.Fonts->AddFontDefaultVector();
  //io.Fonts->AddFontDefaultBitmap();

  // Important: when calling AddFontFromMemoryTTF(), ownership of font_data is transferred by Dear ImGui by default (deleted is handled by Dear ImGui), unless we set FontDataOwnedByAtlas=false in ImFontConfig
  //void*   font_data;
  //int     font_data_size;
  //ImFont* font;
  //font_data_size = GetAssetData("segoeui.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size);
  //IM_ASSERT(font != nullptr);
  //font_data_size = GetAssetData("DroidSans.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size);
  //IM_ASSERT(font != nullptr);
  //font_data_size = GetAssetData("Roboto-Medium.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size);
  //IM_ASSERT(font != nullptr);
  //font_data_size = GetAssetData("Cousine-Regular.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size);
  //IM_ASSERT(font != nullptr);
  //font_data_size = GetAssetData("ArialUni.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size);
  //IM_ASSERT(font != nullptr);

  g_Initialized = true;
}

// Additional loop code so we have zero boilerplate code in our main
template <typename T>
int UIFrame(T&& callback) {
  ImGuiIO& io = ImGui::GetIO();
  if (g_EglDisplay == EGL_NO_DISPLAY)
    return 1;

  // Our state
  // (we use static, which essentially makes the variable globals, as a convenience to keep the example code easy to follow)
  static bool show_demo_window = true;
  static bool show_another_window = false;
  static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Poll Unicode characters via JNI
  // FIXME: do not call this every frame because of JNI overhead
  PollUnicodeChars();

  // Open on-screen (soft) input if requested by Dear ImGui
  static bool WantTextInputLast = false;
  if (io.WantTextInput && !WantTextInputLast)
    ShowSoftKeyboardInput();
  WantTextInputLast = io.WantTextInput;

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplAndroid_NewFrame();
  ImGui::NewFrame();

  // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  { callback(); }

  // Rendering
  ImGui::Render();
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  eglSwapBuffers(g_EglDisplay, g_EglSurface);

  return 0;
}

void Shutdown() {
  if (!g_Initialized)
    return;

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplAndroid_Shutdown();
  ImGui::DestroyContext();

  if (g_EglDisplay != EGL_NO_DISPLAY) {
    eglMakeCurrent(g_EglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,
                   EGL_NO_CONTEXT);

    if (g_EglContext != EGL_NO_CONTEXT)
      eglDestroyContext(g_EglDisplay, g_EglContext);

    if (g_EglSurface != EGL_NO_SURFACE)
      eglDestroySurface(g_EglDisplay, g_EglSurface);

    eglTerminate(g_EglDisplay);
  }

  g_EglDisplay = EGL_NO_DISPLAY;
  g_EglContext = EGL_NO_CONTEXT;
  g_EglSurface = EGL_NO_SURFACE;
  ANativeWindow_release(g_App->window);

  g_Initialized = false;
}

// Helper functions

// Unfortunately, there is no way to show the on-screen input from native code.
// Therefore, we call ShowSoftKeyboardInput() of the main activity implemented in MainActivity.kt via JNI.
int ShowSoftKeyboardInput() {
  JavaVM* java_vm = g_App->activity->vm;
  JNIEnv* java_env = nullptr;

  jint jni_return = java_vm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
  if (jni_return == JNI_ERR)
    return -1;

  jni_return = java_vm->AttachCurrentThread(&java_env, nullptr);
  if (jni_return != JNI_OK)
    return -2;

  jclass native_activity_clazz =
      java_env->GetObjectClass(g_App->activity->clazz);
  if (native_activity_clazz == nullptr)
    return -3;

  jmethodID method_id =
      java_env->GetMethodID(native_activity_clazz, "showSoftInput", "()V");
  if (method_id == nullptr)
    return -4;

  java_env->CallVoidMethod(g_App->activity->clazz, method_id);

  jni_return = java_vm->DetachCurrentThread();
  if (jni_return != JNI_OK)
    return -5;

  return 0;
}

// Unfortunately, the native KeyEvent implementation has no getUnicodeChar() function.
// Therefore, we implement the processing of KeyEvents in MainActivity.kt and poll
// the resulting Unicode characters here via JNI and send them to Dear ImGui.
int PollUnicodeChars() {
  JavaVM* java_vm = g_App->activity->vm;
  JNIEnv* java_env = nullptr;

  jint jni_return = java_vm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
  if (jni_return == JNI_ERR)
    return -1;

  jni_return = java_vm->AttachCurrentThread(&java_env, nullptr);
  if (jni_return != JNI_OK)
    return -2;

  jclass native_activity_clazz =
      java_env->GetObjectClass(g_App->activity->clazz);
  if (native_activity_clazz == nullptr)
    return -3;

  jmethodID method_id =
      java_env->GetMethodID(native_activity_clazz, "pollUnicodeChar", "()I");
  if (method_id == nullptr)
    return -4;

  // Send the actual characters to Dear ImGui
  ImGuiIO& io = ImGui::GetIO();
  jint unicode_character;
  while ((unicode_character =
              java_env->CallIntMethod(g_App->activity->clazz, method_id))
         != 0)
    io.AddInputCharacter(unicode_character);

  jni_return = java_vm->DetachCurrentThread();
  if (jni_return != JNI_OK)
    return -5;

  return 0;
}

// Helper to retrieve data placed into the assets/ directory (android/app/src/main/assets)
int GetAssetData(const char* filename, void** outData) {
  int num_bytes = 0;
  AAsset* asset_descriptor = AAssetManager_open(g_App->activity->assetManager,
                                                filename, AASSET_MODE_BUFFER);
  if (asset_descriptor) {
    num_bytes = AAsset_getLength(asset_descriptor);
    *outData = IM_ALLOC(num_bytes);
    int64_t num_bytes_read = AAsset_read(asset_descriptor, *outData, num_bytes);
    AAsset_close(asset_descriptor);
    IM_ASSERT(num_bytes_read == num_bytes);
  }
  return num_bytes;
}
}  // namespace
