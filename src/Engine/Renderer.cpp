#include "Renderer.hpp"


Renderer::Renderer(Driver& p_driver)
: driver_ { p_driver }
{
    auto& device    = driver_.getDeviceManager().getDevice();
    auto& swapMng   = driver_.getSwapchainManager();

    pipeLayout_ = std::make_unique<PipelineLayout>( device );
    renderPass_ = std::make_unique<RenderPass>( device, swapMng );

    auto& renderPassObj  = renderPass_.get()->getRenderPass();

    framebuffer_ = std::make_unique<PipelineFrameBuffers>( device, renderPassObj, swapMng);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
Renderer::initRenderPass( uint32_t p_imageId, VkCommandBuffer& p_cmd ) noexcept
{
    auto& vkRenderPass  = renderPass_.get()->getRenderPass();
    auto& frameBuffer   = framebuffer_.get()->getFramebufferByIndex( p_imageId );

    auto& swapInfo = driver_.getSwapchainManager().getSwapchainInfo();

    VkRenderPassBeginInfo _beginInfo {};

    _beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    _beginInfo.pNext = nullptr;
    
    _beginInfo.renderPass = vkRenderPass;
    _beginInfo.framebuffer = frameBuffer;

    _beginInfo.renderArea.offset = { 0, 0 };
    _beginInfo.renderArea.extent = swapInfo.imageExtent;

    _beginInfo.clearValueCount = 1;
    VkClearValue blackColor {0.f,0.f,0.f,1.f};
    _beginInfo.pClearValues = &blackColor;

    vkCmdBeginRenderPass( p_cmd, &_beginInfo, VK_SUBPASS_CONTENTS_INLINE );
}
