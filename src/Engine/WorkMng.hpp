#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/DrawerMng.hpp>
#include <Engine/Render/PipelineFrameBuffers.hpp>
#include <Engine/Driver/SwapchainMng.hpp>
#include <Engine/Driver/DeviceMng.hpp>

class WorkMng
{
private:
    DeviceMng&              deviceMng_;
    VkDevice&               device_;
    SwapchainMng&           swapMng_;
    DrawerMng&              drawer_;
    PipelineFrameBuffers&   frameBuffers_;

    VkFence     cmdBufferAvailable_ { VK_NULL_HANDLE };
    VkSemaphore imgAvailable_       { VK_NULL_HANDLE };
    VkSemaphore imgRendered_        { VK_NULL_HANDLE };


public:
    WorkMng(DeviceMng& p_deviceMng, SwapchainMng& p_swapMng ,DrawerMng& p_drawer, PipelineFrameBuffers& p_buffers ) noexcept;

    ~WorkMng();

    void
    drawFrame();

private:
    void
    createSyncObjects();

    uint32_t
    getFrameBufferIndex();

    void
    submitCommands( uint32_t p_imageId ) noexcept;

};
