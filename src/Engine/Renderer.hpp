#pragma once
#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/DrawerMng.hpp>
#include <Engine/PipelineStructs/PipelineFrameBuffers.hpp>
#include <Engine/SwapchainMng.hpp>
#include <Engine/DeviceMng.hpp>

class Renderer
{
private:
    DeviceMng&              _deviceMng;
    VkDevice&               _device;
    SwapchainMng&           _swapMng;
    DrawerMng&              _drawer;
    PipelineFrameBuffers&   _frameBuffers;

    VkFence     _cmdBufferAvailable { VK_NULL_HANDLE };
    VkSemaphore _imgAvailable       { VK_NULL_HANDLE };
    VkSemaphore _imgRendered        { VK_NULL_HANDLE };


public:
    Renderer(DeviceMng& p_deviceMng, SwapchainMng& p_swapMng ,DrawerMng& p_drawer, PipelineFrameBuffers& p_buffers ) noexcept;

    ~Renderer();

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
