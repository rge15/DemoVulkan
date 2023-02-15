#include "PipelineFrameBuffers.hpp"

PipelineFrameBuffers::PipelineFrameBuffers( VkDevice& p_device, VkRenderPass& p_renderPass, SwapchainMng& p_swapChainMng ) noexcept
: _device { p_device }, _renderPass { p_renderPass }, _swapMng { p_swapChainMng }
{
    createBuffers();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

PipelineFrameBuffers::~PipelineFrameBuffers()
{
    for(size_t i = 0 ; i < _buffers.size(); i++)
    {
        vkDestroyFramebuffer( _device, _buffers[i], nullptr );
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineFrameBuffers::createBuffers() noexcept
{
    auto swapInfo = _swapMng.getSwapchainInfo();
    auto vkImages = _swapMng.getSwapchainImageViews();
    _buffers.resize(vkImages.size());

    VkFramebufferCreateInfo info {};
    info.sType  = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    info.pNext  = nullptr;
    info.flags  = 0;

    info.renderPass = _renderPass;
    
    info.height = swapInfo.imageExtent.height;
    info.width = swapInfo.imageExtent.width;
    info.layers = swapInfo.imageArrayLayers;

    info.attachmentCount = 1;

    int i = 0;
    for(auto& image : vkImages)
    {
        info.pAttachments = &image;

        auto result = vkCreateFramebuffer( _device, &info, nullptr, &_buffers[i]);
        
        assert(result == VK_SUCCESS);
        
        ++i;
    }
}
