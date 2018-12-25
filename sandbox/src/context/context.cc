/// @file context.cc
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

#include <cstdio>
#include <cstdlib>

#include "sandbox/src/context/context.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

template <typename T, std::size_t N>
constexpr std::size_t countof(T const (&)[N])
{
  return N;
}

#define TEST_VK_RESULT( _call_ ) { VkResult result = _call_; \
  if (result != VK_SUCCESS) {\
  std::printf("Unsuccessful call '%s': %d", #_call_, result); \
  }\
}

namespace {
  constexpr const char * enabledExtensions[] = {"VK_KHR_SURFACE_EXTENSION_NAME",
						//"VK_KHR_WIN32_SURFACE_EXTENSION_NAME",
						"VK_KHR_SWAPCHAIN_EXTENSION_NAME",
						// debug layers
						"VK_EXT_DEBUG_REPORT_EXTENSION_NAME"};

  constexpr const char * enabledLayers[] = {"VK_LAYER_LUNARG_standard_validation"};

  void CreateInstance(VkInstance & instance) {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Sandbox";
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, VK_HEADER_VERSION);

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = countof(enabledExtensions);
    createInfo.ppEnabledExtensionNames = &enabledExtensions[0];
    createInfo.enabledLayerCount = countof(enabledLayers);
    createInfo.ppEnabledLayerNames = &enabledLayers[0];
    TEST_VK_RESULT( vkCreateInstance(&createInfo, NULL, &instance) );
  }
}

namespace sandbox {
namespace context {

Context::Context() {
  // Nothing to do here for now
}

Context::~Context() {
  // Nothing to do here for now
}

bool Context::Initialize() {

  {  // GLFW init
    if (!glfwInit()) {
      return false;
    }

    // Create window
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(640, 480, "SandBox Title", NULL, NULL);
    if (!window_) {
      return false;
    }
    glfwMakeContextCurrent(window_);
    //std::printf("GL version: %s\n", glGetString(GL_VERSION));

    glfwSwapInterval(1);
    glfwSetInputMode(window_, GLFW_STICKY_KEYS, GLFW_TRUE);
  }

  return true;
}

void Context::Terminate() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void Context::Clear() {
}

void Context::Update() {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

bool Context::ShouldClose() {
  bool got_close_key = glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS;
  return got_close_key
    || glfwWindowShouldClose(window_) != 0;
}

}  // namespace context
}  // namespace sandbox
