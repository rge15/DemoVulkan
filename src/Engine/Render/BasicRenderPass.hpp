#pragma once
#include "BaseRenderPass.hpp"
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/Driver/SwapchainMng.hpp>

/**
 * @brief Basic Render Pass which doesn't have description sets.
 * 
 * This engine version just have a basic renderpass with no supbasses
 * 
 * This class PUBLIC inhers from @see BaseRenderPass
 */
class BasicRenderPass : public BaseRenderPass
{
public:
    /**
     * @brief Construct a new Basic Render Pass object
     * 
     * @param p_device Vulkan Logical device to create the Render Pass from
     * @param p_swapMng Swapchain Mng for getting info relative for Render Pass creation
     */
    BasicRenderPass( VkDevice& p_device, const SwapchainMng& p_swapMng );

    /**
     * @brief Destroy the Basic Render Pass object
     * 
     * Base render pass class manages Vulkan Render Pass destruction
     */
    ~BasicRenderPass() = default;
};