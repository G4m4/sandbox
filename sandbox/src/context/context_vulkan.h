/// @file context_vulkan.h
/// @brief Base context object for Vulkan API
/// @author gm
/// @copyright gm 2018
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

#ifndef SANDBOX_CONTEXT_VULKAN_H_
#define SANDBOX_CONTEXT_VULKAN_H_

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "sandbox/src/common.h"

namespace sandbox {
namespace context {

/// @brief Context object, where the Vulkan instance lives at the moment
class ContextVulkan {
 public:
#if(_BUILD_CONFIGURATION_DEBUG)
  static constexpr bool c_enableValidationLayers = true;
#else
  static constexpr bool c_enableValidationLayers = false;
#endif // _BUILD_CONFIGURATION_
  ContextVulkan();
  ~ContextVulkan();

  bool Initialize();
  void Terminate();

  void Clear();
  void Update();
  bool ShouldClose();

 private:
  VkInstance instance_;
  VkDebugUtilsMessengerEXT callback_;
};

}  // namespace context
}  // namespace sandbox

#endif  // SANDBOX_CONTEXT_VULKAN_H_
