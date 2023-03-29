#include "PipelineFrameBuffers.hpp"

PipelineFrameBuffers::PipelineFrameBuffers( VkDevice& p_device, VkRenderPass& p_renderPass, SwapchainMng& p_swapChainMng ) noexcept
: device_ { p_device }, renderPass_ { p_renderPass }, swapMng_ { p_swapChainMng }
{
    createBuffers();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

PipelineFrameBuffers::~PipelineFrameBuffers()
{
    for(size_t i = 0 ; i < buffers_.size(); i++)
    {
        vkDestroyFramebuffer( device_, buffers_[i], nullptr );
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineFrameBuffers::createBuffers() noexcept
{
    auto swapInfo = swapMng_.getSwapchainInfo();
    auto vkImages = swapMng_.getSwapchainImageViews();
    buffers_.resize(vkImages.size());

    VkFramebufferCreateInfo info {};
    info.sType  = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    info.pNext  = nullptr;
    info.flags  = 0;

    info.renderPass = renderPass_;
    
    info.height = swapInfo.imageExtent.height;
    info.width = swapInfo.imageExtent.width;
    info.layers = swapInfo.imageArrayLayers;

    info.attachmentCount = 1;

    int i = 0;
    for(auto& image : vkImages)
    {
        info.pAttachments = &image;

        auto result = vkCreateFramebuffer( device_, &info, nullptr, &buffers_[i]);
        
        assert(result == VK_SUCCESS);
        
        ++i;
    }
}
