#include "WorkMng.hpp"

WorkMng::WorkMng(DeviceMng& p_deviceMng, SwapchainMng& p_swapMng, DrawerMng& p_drawer, PipelineFrameBuffers& p_buffers ) noexcept
: deviceMng_ { p_deviceMng }, device_ { p_deviceMng.getDevice() }, swapMng_{ p_swapMng }, drawer_ { p_drawer }, frameBuffers_ { p_buffers }
{
    createSyncObjects();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

WorkMng::~WorkMng()
{
    vkDestroySemaphore( device_, imgAvailable_, nullptr );
    vkDestroySemaphore( device_, imgRendered_, nullptr );
    vkDestroyFence( device_, cmdBufferAvailable_, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
WorkMng::drawFrame()
{
    auto imageId        = getFrameBufferIndex();
    auto frameBuffer    = frameBuffers_.getFramebufferByIndex( imageId );

    vkWaitForFences( device_, 1, &cmdBufferAvailable_, true, UINT64_MAX );
    vkResetFences( device_, 1, &cmdBufferAvailable_ );

    drawer_.recordDrawCommand( frameBuffer );

    submitCommands( imageId );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
WorkMng::createSyncObjects()
{
    VkSemaphoreCreateInfo semaInfo {};
    semaInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaInfo.pNext = nullptr;
    semaInfo.flags = 0; 
    
    vkCreateSemaphore( device_, &semaInfo, nullptr, &imgAvailable_ );
    vkCreateSemaphore( device_, &semaInfo, nullptr, &imgRendered_ );

    VkFenceCreateInfo fenceInfo {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = nullptr;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    vkCreateFence( device_, &fenceInfo, nullptr, &cmdBufferAvailable_);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

uint32_t
WorkMng::getFrameBufferIndex()
{
    uint32_t imgId  = 0;
    auto swapchain  = swapMng_.getSwapchain();

    vkAcquireNextImageKHR( device_, swapchain, UINT64_MAX, imgAvailable_, VK_NULL_HANDLE, &imgId);
    return imgId;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
WorkMng::submitCommands( uint32_t p_imageId ) noexcept
{
    VkPipelineStageFlags stageFlags { VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT };
    VkSubmitInfo _subInfo {};
    
    _subInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    _subInfo.pNext = nullptr;
    _subInfo.waitSemaphoreCount = 1;
    _subInfo.pWaitSemaphores    = &imgAvailable_;    
    _subInfo.pWaitDstStageMask  = &stageFlags;
    _subInfo.commandBufferCount = 1;
    
    _subInfo.pCommandBuffers        = &drawer_.getCmdBuffer();
    _subInfo.signalSemaphoreCount   = 1;
    _subInfo.pSignalSemaphores      = &imgRendered_;

    auto graphicQueueHandler = deviceMng_.getGraphicQueueHandler();
    vkQueueSubmit( graphicQueueHandler, 1, &_subInfo, cmdBufferAvailable_ );

    VkPresentInfoKHR presentInfo {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = nullptr;

    presentInfo.waitSemaphoreCount  = 1;
    presentInfo.pWaitSemaphores     = &imgRendered_;

    presentInfo.swapchainCount  = 1;
    presentInfo.pSwapchains     = &swapMng_.getSwapchain();
    presentInfo.pImageIndices   = &p_imageId;
    presentInfo.pResults = nullptr;

    vkQueuePresentKHR( deviceMng_.getPresentQueueHandler(), &presentInfo );

}