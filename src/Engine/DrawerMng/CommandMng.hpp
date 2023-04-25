#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

class CommandMng
{
private:
    VkDevice&                   device_;
    const DeviceQueueFamilies&  queueFamilyId_;
    
    /*
    VkRenderPass&               renderPass_;
    VkPipeline&                 pipeline_;
    VkPipelineLayout&           layout_;
    const VkSwapchainCreateInfoKHR&   swapInfo_;
    */

    VkCommandPool   pool_       { VK_NULL_HANDLE };
    VkCommandBuffer cmdBuffer_  { VK_NULL_HANDLE };

    VkCommandBufferBeginInfo beginRecordInfo_ {};

public:

    /*
    CommandMng(
        VkDevice& p_device, const DeviceQueueFamilies& p_queueFamilyId, VkRenderPass& p_renderPass,
        VkPipeline& p_pipeline, VkPipelineLayout& p_layout, const VkSwapchainCreateInfoKHR& p_swapInfo
    ) noexcept;
    */

    explicit CommandMng( 
        VkDevice& p_device, const DeviceQueueFamilies& p_queueFamilyId
    ) noexcept;

    ~CommandMng();

    inline
    VkCommandBuffer&
    getCmdBuffer() { return cmdBuffer_; };

    void
    beginRecording() noexcept;

    void
    endRecording() noexcept;

    void
    submitSingle( VkQueue& p_queue ) noexcept;

private:

    void
    createCommandPool() noexcept;

    void
    allocateCommandBuffer() noexcept;

    void
    initCommandBufferRecordingInfo() noexcept;

/*
    void
    recordCommands( VkFramebuffer& p_framebuffer ) noexcept;

    void
    initRenderPass( VkFramebuffer& p_framebuffer ) noexcept;

    void
    initDynamicStates() noexcept;

    void
    passPushConstantData() noexcept;

    template<typename T>
    uint32_t
    getPushConstantSize( const Vector<T>& p_data ) noexcept;
*/

};