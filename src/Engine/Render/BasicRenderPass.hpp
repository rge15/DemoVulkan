#pragma once
#include "BaseRenderPass.hpp"
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/Driver/SwapchainMng.hpp>

class BasicRenderPass : public BaseRenderPass
{
public:
    BasicRenderPass( VkDevice& p_device, const SwapchainMng& p_swapMng );
    ~BasicRenderPass() = default;
};