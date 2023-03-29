#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/Driver/SwapchainMng.hpp>

class PipelineFrameBuffers
{
private:
    VkDevice&       device_;
    VkRenderPass&   renderPass_;
    SwapchainMng&   swapMng_;

    using Framebuffers = Vector<VkFramebuffer>;
    Framebuffers        buffers_ {};

public:
    PipelineFrameBuffers( VkDevice& p_device, VkRenderPass& p_renderPass, SwapchainMng& p_swapChainMng ) noexcept;
    ~PipelineFrameBuffers();

    inline
    VkFramebuffer&
    getFramebufferByIndex(uint32_t p_id ){ return buffers_[p_id]; };

private:

    void
    createBuffers() noexcept;

};