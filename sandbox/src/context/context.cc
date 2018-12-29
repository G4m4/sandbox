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

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "sandbox/src/context/context.h"
#include "sandbox/src/context/context_vulkan.h"

namespace sandbox {
namespace context {

Context::Context() : window_(nullptr), context_impl_(new ContextVulkan()) {
  // Nothing to do here for now
}

Context::~Context() {
  delete context_impl_;
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
  context_impl_->Initialize();

  return true;
}

void Context::Terminate() {
  glfwDestroyWindow(window_);
  glfwTerminate();
  context_impl_->Terminate();
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
