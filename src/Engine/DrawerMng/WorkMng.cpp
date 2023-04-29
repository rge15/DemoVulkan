#include "WorkMng.hpp"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

WorkMng::WorkMng(VkDevice& p_device ) noexcept
: device_ { p_device }
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
WorkMng::getImageBufferIndex( VkSwapchainKHR& p_swap )
{
    uint32_t imgId  = 0;

    vkAcquireNextImageKHR( device_ , p_swap, UINT64_MAX, imgAvailable_, VK_NULL_HANDLE, &imgId);
    
    return imgId;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
WorkMng::waitBufferSync() noexcept
{
    vkWaitForFences( device_, 1, &cmdBufferAvailable_, true, UINT64_MAX );
    vkResetFences( device_, 1, &cmdBufferAvailable_ );
}