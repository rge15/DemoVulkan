#pragma once
#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

class DrawerMng
{
private:
    VkDevice&                   _device;
    const DeviceQueueFamilies&  _queueFamilyId;
    VkRenderPass&               _renderPass;
    VkPipeline&                 _pipeline;
    VkPipelineLayout&           _layout;

    const VkSwapchainCreateInfoKHR&   _swapInfo;

    VkCommandPool   _pool       { VK_NULL_HANDLE };
    VkCommandBuffer _cmdBuffer  { VK_NULL_HANDLE };

    VkCommandBufferBeginInfo _beginRecordInfo {};

public:

    DrawerMng(
        VkDevice& p_device, const DeviceQueueFamilies& p_queueFamilyId, VkRenderPass& p_renderPass,
        VkPipeline& p_pipeline, VkPipelineLayout& p_layout, const VkSwapchainCreateInfoKHR& p_swapInfo
    ) noexcept;

    ~DrawerMng();

    void
    recordDrawCommand( VkFramebuffer& p_framebuffer ) noexcept;

    inline
    VkCommandBuffer&
    getCmdBuffer() { return _cmdBuffer; };

private:

    void
    createCommandPool() noexcept;

    void
    allocateCommandBuffer() noexcept;

    void
    initCommandBufferRecordingInfo() noexcept;

    void
    beginRecording() noexcept;

    void
    recordCommands( VkFramebuffer& p_framebuffer ) noexcept;

    void
    endRecording() noexcept;

    void
    initRenderPass( VkFramebuffer& p_framebuffer ) noexcept;

    void
    initDynamicStates() noexcept;

    void
    passPushConstantData() noexcept;

    template<typename T>
    uint32_t
    getPushConstantSize( const Vector<T>& p_data ) noexcept;

};