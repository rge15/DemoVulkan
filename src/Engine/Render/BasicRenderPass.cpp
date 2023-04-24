#include "BasicRenderPass.hpp"

BasicRenderPass::BasicRenderPass(VkDevice& p_device, const SwapchainMng& p_swapMng)
: BaseRenderPass { p_device, p_swapMng }
{
    createRenderPass();
}