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