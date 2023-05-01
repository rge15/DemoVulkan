#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/Driver/SwapchainMng.hpp>

/**
 * @brief Class that manages a Vulkan framebuffer based on the only 
 * renderpass type created for the engine
 */
class PipelineFrameBuffers
{
private:
    //! Reference to the Vulkan Device to create the framebuffer  
    VkDevice&       device_;
    //! Reference to the Render Pass to create the framebuffer
    VkRenderPass&   renderPass_;
    //! Swapchain manager for get the images for the framebuffer creation
    SwapchainMng&   swapMng_;

    //! Typealias for the Vulkan FrameBuffers
    using Framebuffers = Vector<VkFramebuffer>;
    //! Framebuffer Object
    Framebuffers        buffers_ {};

public:
    /**
     * @brief Construct a new Pipeline Frame Buffers object
     * 
     * @param p_device Vulkan Device for creating the framebuffer 
     * @param p_renderPass Vulkan Render Pass to create the framebuffer from
     * @param p_swapChainMng Swapchain Manager for getting the images for the framebuffer
     */
    PipelineFrameBuffers( VkDevice& p_device, VkRenderPass& p_renderPass, SwapchainMng& p_swapChainMng ) noexcept;
    ~PipelineFrameBuffers();

    /**
     * @brief Get the specific buffer of the framebuffer based on the buffer Index
     * 
     * @param p_id Index of th ebuffer to get
     * @return VkFramebuffer& 
     */
    inline
    VkFramebuffer&
    getFramebufferByIndex(uint32_t p_id ){ return buffers_[p_id]; };

private:

    /**
     * @brief Create all the Buffers of the Framebuffer
     */
    void
    createBuffers() noexcept;

};