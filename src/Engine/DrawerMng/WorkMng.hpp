#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/DrawerMng/CommandMng.hpp>
#include <Engine/Render/PipelineFrameBuffers.hpp>
#include <Engine/Driver/SwapchainMng.hpp>
#include <Engine/Driver/DeviceMng.hpp>

class WorkMng
{
private:
    VkDevice&               device_;
    
    /*
    DeviceMng&              deviceMng_;
    SwapchainMng&           swapMng_;
    CommandMng&              drawer_;
    PipelineFrameBuffers&   frameBuffers_;
    */

    VkFence     cmdBufferAvailable_ { VK_NULL_HANDLE };
    VkSemaphore imgAvailable_       { VK_NULL_HANDLE };
    VkSemaphore imgRendered_        { VK_NULL_HANDLE };


public:

    //WorkMng(DeviceMng& p_deviceMng, SwapchainMng& p_swapMng, CommandMng& p_drawer, PipelineFrameBuffers& p_buffers ) noexcept;

    explicit WorkMng(VkDevice& p_deviceMng ) noexcept;

    ~WorkMng();

    void
    drawFrame();

    uint32_t
    getFrameBufferIndex( VkSwapchainKHR& p_swap );

    void
    waitBufferSync() noexcept;

    inline
    VkSemaphore& getImgAvailableSemaphore(){ return imgAvailable_; };

    inline
    VkSemaphore& getImgRenderedSemaphore(){ return imgRendered_; };

    inline
    VkFence& getCmdAvailableFence(){ return cmdBufferAvailable_; };

private:
    void
    createSyncObjects();

    void
    submitCommands( uint32_t p_imageId ) noexcept;

};
