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

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

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
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(640, 480, "SandBox Title", NULL, NULL);
    if (!window_) {
      return false;
    }
    glfwMakeContextCurrent(window_);
    std::printf("GL version: %s\n", glGetString(GL_VERSION));

    glfwSwapInterval(1);
    glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
  }

  glewExperimental = 1;  // This is required due to driver issues
  if (glewInit() != GLEW_OK) {
    return false;
  }
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  return true;
}

void Context::Terminate() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void Context::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
