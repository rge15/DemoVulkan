#pragma once
#include "utilities/graphicInclude.hpp"
#include "utilities/typeAliases.hpp"

struct SwapchainDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    Vector<VkSurfaceFormatKHR> formats;
    Vector<VkPresentModeKHR> presentModes;
};