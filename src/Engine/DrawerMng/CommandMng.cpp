#include "CommandMng.hpp"
#include <utilities/Timer/Timer.hpp>

CommandMng::CommandMng( 
    VkDevice& p_device, const DeviceQueueFamilies& p_queueFamilyId
) noexcept
: device_ { p_device }, queueFamilyId_ { p_queueFamilyId }
{
    createCommandPool();
    allocateCommandBuffer();
    initCommandBufferRecordingInfo();
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

CommandMng::~CommandMng()
{
    vkDestroyCommandPool( device_, pool_, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::createCommandPool() noexcept
{
    VkCommandPoolCreateInfo _info {};

    _info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    _info.pNext = nullptr;
    _info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    _info.queueFamilyIndex = queueFamilyId_._graphicQueueId.value();

    auto result = vkCreateCommandPool(device_, &_info, nullptr, &pool_);

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::allocateCommandBuffer() noexcept
{
    VkCommandBufferAllocateInfo info_ {};
    
    info_.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info_.pNext = nullptr;
    info_.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    
    info_.commandPool           = pool_;
    info_.commandBufferCount    = 1;

    auto result = vkAllocateCommandBuffers( device_, &info_, &cmdBuffer_ );

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::initCommandBufferRecordingInfo() noexcept
{
    beginRecordInfo_.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginRecordInfo_.pNext = nullptr;
    beginRecordInfo_.flags = 0;
    beginRecordInfo_.pInheritanceInfo = nullptr;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::beginRecording() noexcept
{
    vkBeginCommandBuffer(cmdBuffer_, &beginRecordInfo_);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::endRecording() noexcept
{
    vkEndCommandBuffer(cmdBuffer_);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::submitSingle( VkQueue& p_queue ) noexcept
{
    VkSubmitInfo info {};

    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.pNext = nullptr;
    info.signalSemaphoreCount = 0;
    info.pWaitSemaphores = nullptr;
    info.pWaitDstStageMask = nullptr;
    info.commandBufferCount = 1;
    info.pCommandBuffers = &cmdBuffer_;
    info.signalSemaphoreCount = 0;
    info.pSignalSemaphores = nullptr;

    vkQueueSubmit( p_queue, 1, &info, VK_NULL_HANDLE );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------