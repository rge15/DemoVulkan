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
CommandMng::recordDrawCommand( VkFramebuffer& p_framebuffer ) noexcept
{
    beginRecording();

    //recordCommands( p_framebuffer );

    endRecording();
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

/*
void
CommandMng::recordCommands(VkFramebuffer& p_framebuffer) noexcept
{
    initRenderPass( p_framebuffer );

    vkCmdBindPipeline( cmdBuffer_, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_ );

    initDynamicStates();

    passPushConstantData();

    vkCmdDraw( cmdBuffer_, 6, 1, 0, 0);

    vkCmdEndRenderPass( cmdBuffer_ );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::initRenderPass( VkFramebuffer& p_framebuffer ) noexcept
{
    VkRenderPassBeginInfo _beginInfo {};

    _beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    _beginInfo.pNext = nullptr;
    
    _beginInfo.renderPass = renderPass_;
    _beginInfo.framebuffer = p_framebuffer;

    _beginInfo.renderArea.offset = { 0, 0 };
    _beginInfo.renderArea.extent = swapInfo_.imageExtent;

    _beginInfo.clearValueCount = 1;
    VkClearValue blackColor {0.f,0.f,0.f,1.f};
    _beginInfo.pClearValues = &blackColor;

    vkCmdBeginRenderPass( cmdBuffer_, &_beginInfo, VK_SUBPASS_CONTENTS_INLINE );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::initDynamicStates() noexcept
{
    VkViewport viewport{};

    viewport.x = 0;
    viewport.y = 0;
    viewport.height = swapInfo_.imageExtent.height;
    viewport.width = swapInfo_.imageExtent.width;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport( cmdBuffer_, 0, 1, &viewport );

    VkRect2D _scissor {};

    _scissor.offset = { 0 , 0 };
    _scissor.extent = swapInfo_.imageExtent;

    vkCmdSetScissor( cmdBuffer_, 0, 1, &_scissor );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
CommandMng::passPushConstantData(   ) noexcept
{
    auto width      = (float)swapInfo_.imageExtent.width;
    auto heigth     = (float)swapInfo_.imageExtent.height;
    auto absTime    = (float)Timer::getInstance().ellapsedSeconds();
    //auto relTime    = (float)Timer::getInstance().ellapsedSeconds();

    Vector<float> pushCnstData { width, heigth, absTime };

    uint32_t finalSize = getPushConstantSize(pushCnstData);

    vkCmdPushConstants(
        cmdBuffer_, layout_, VK_SHADER_STAGE_FRAGMENT_BIT,
        0, finalSize, pushCnstData.data() 
    );

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
uint32_t
CommandMng::getPushConstantSize( const Vector<T>& p_data ) noexcept
{
    auto dataSize   = p_data.size() * sizeof(p_data.data()[0]) ;
    auto multiple4  = (int)std::log2( dataSize );
    
    uint32_t perfectSize = pow(2,multiple4);
    uint32_t difference  = dataSize % perfectSize ;

    uint32_t finalSize = (difference == 0) ? perfectSize : pow(2,multiple4+1);

    return finalSize;
}

*/