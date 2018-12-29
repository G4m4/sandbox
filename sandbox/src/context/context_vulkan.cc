/// @file context_vulkan.cc
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

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <vector>

#include "sandbox/src/context/context_vulkan.h"

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

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  VkDebugUtilsMessageTypeFlagsEXT messageType,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* pUserData) {

  std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

  return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pCallback);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

namespace {
  std::vector<const char*> getRequiredExtensions() {
    unsigned glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    return extensions;
  }
}

namespace sandbox {
namespace context {

ContextVulkan::ContextVulkan() {
}

ContextVulkan::~ContextVulkan() {
  // Nothing to do here for now
}

bool ContextVulkan::Initialize() {
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Sandbox";
  appInfo.apiVersion = VK_MAKE_VERSION(1, 0, VK_HEADER_VERSION);

  VkInstanceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  unsigned availableExtensionsCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
  std::vector<VkExtensionProperties> availableExtensions(availableExtensionsCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, availableExtensions.data());
  std::cout << "Extensions:" << std::endl;
  for (const auto & extension : availableExtensions) {
    std::cout << extension.extensionName << std::endl;
  }

  unsigned availableLayersCount = 0;
  vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);
  std::vector<VkLayerProperties> availableLayers(availableLayersCount);
  std::vector<const char *> availableLayersNames;
  vkEnumerateInstanceLayerProperties(&availableLayersCount, availableLayers.data());
  std::cout << "Layers:" << std::endl;
  for (const auto & layer : availableLayers) {
    std::cout << layer.layerName << std::endl;
    availableLayersNames.push_back(layer.layerName);
  }

  auto extensions = getRequiredExtensions();
  if (c_enableValidationLayers) {
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  createInfo.enabledExtensionCount = extensions.size();
  createInfo.ppEnabledExtensionNames = extensions.data();
  createInfo.enabledLayerCount = c_enableValidationLayers ? availableLayersNames.size() : 0;
  createInfo.ppEnabledLayerNames = availableLayersNames.data();
  TEST_VK_RESULT( vkCreateInstance(&createInfo, NULL, &instance_) );

  if (c_enableValidationLayers) {
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr; // Optional
    TEST_VK_RESULT( CreateDebugUtilsMessengerEXT(instance_, &createInfo, nullptr, &callback_) );
  }
  return true;
}

void ContextVulkan::Terminate() {
  vkDestroyInstance(instance_, nullptr);
}

void ContextVulkan::Clear() {
}

void ContextVulkan::Update() {
}

}  // namespace context
}  // namespace sandbox
