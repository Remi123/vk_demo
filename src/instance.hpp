
#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "vulkan/vulkan.hpp"
#include "window.hpp"
#include <iostream>

namespace tri {
    struct instance {
        VkInstance m_instance;
        VkInstanceCreateInfo m_inst_create_info;

        const std::vector<const char*> validationLayers; 


#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else
        const bool enableValidationLayers = true;
#endif
        instance() : m_instance{}
        , m_inst_create_info{} 
        , validationLayers{"VK_LAYER_KHRONOS_validation"}
        {
            if (enableValidationLayers && !checkValidationLayerSupport()) {
                throw std::runtime_error("validation layers requested, but not available!");
            }
            VkApplicationInfo m_appinfo;
            m_appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            m_appinfo.pApplicationName = "Hello Triangle";
            m_appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            m_appinfo.pEngineName = "No Engine";
            m_appinfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            m_appinfo.apiVersion = VK_API_VERSION_1_0;
            //
            if (enableValidationLayers) {
                m_inst_create_info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                m_inst_create_info.ppEnabledLayerNames = validationLayers.data();
            } else {
                m_inst_create_info.enabledLayerCount = 0;
            }
            //
            m_inst_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            m_inst_create_info.pApplicationInfo = &m_appinfo;
            m_inst_create_info.enabledExtensionCount = tri::g_glfwExtensionCount;
            m_inst_create_info.ppEnabledExtensionNames = tri::g_glfwExtensions;
            //
            // This might change soon
            m_inst_create_info.enabledLayerCount = 0;
            //
            if (vkCreateInstance(&m_inst_create_info, nullptr, &m_instance) !=
                    VK_SUCCESS) {
                throw std::runtime_error("failed to create instance!");
            }
        }
        ~instance() { vkDestroyInstance(m_instance, nullptr); }
        void print_extensions() {
            uint32_t extensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
            std::vector<VkExtensionProperties> extensions(extensionCount);
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
                    extensions.data());
            std::cout << "available extensions:" << std::endl;

            for (const auto& extension : extensions) {
                std::cout << "\t" << extension.extensionName << std::endl;
            }
            std::cout << "NDebug: " << enableValidationLayers << std::endl;
        }
        bool checkValidationLayerSupport() {
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
            for (const char* layerName : validationLayers) {
                bool layerFound = false;

                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        layerFound = true;
                        break;
                    }
                }

                if (!layerFound) {
                    return false;
                }
            }

            return true;
        }

    };
}  // namespace tri
#endif
