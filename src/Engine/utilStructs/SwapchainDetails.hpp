#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include "utilities/typeAliases.hpp"

/**
 * @brief Struct handling the swapchain data support
 */
struct SwapchainDetails
{
    //! Surface Capabilities Vulkan Data
    VkSurfaceCapabilitiesKHR capabilities;
    //! Vector with all supported Surface Formants
    Vector<VkSurfaceFormatKHR> formats;
    //! Vector with all supportes Present Modes
    Vector<VkPresentModeKHR> presentModes;
};