#include "DrawerMng.hpp"
#include <utilities/Timer/Timer.hpp>

DrawerMng::DrawerMng(
    VkDevice& p_device, const DeviceQueueFamilies& p_queueFamilyId, VkRenderPass& p_renderPass,
    VkPipeline& p_pipeline, VkPipelineLayout& p_layout, const VkSwapchainCreateInfoKHR& p_swapInfo
) noexcept
: _device { p_device }, _queueFamilyId { p_queueFamilyId }, _renderPass { p_renderPass }
, _pipeline { p_pipeline }, _layout { p_layout }, _swapInfo { p_swapInfo }
{
    createCommandPool();
    allocateCommandBuffer();
    initCommandBufferRecordingInfo();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DrawerMng::~DrawerMng()
{
    vkDestroyCommandPool( _device, _pool, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::createCommandPool() noexcept
{
    VkCommandPoolCreateInfo _info {};

    _info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    _info.pNext = nullptr;
    _info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    _info.queueFamilyIndex = _queueFamilyId._graphicQueueId.value();

    auto result = vkCreateCommandPool(_device, &_info, nullptr, &_pool);

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::allocateCommandBuffer() noexcept
{
    VkCommandBufferAllocateInfo _info {};
    
    _info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    _info.pNext = nullptr;
    _info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    
    _info.commandPool           = _pool;
    _info.commandBufferCount    = 1;

    auto result = vkAllocateCommandBuffers( _device, &_info, &_cmdBuffer );

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::recordDrawCommand( VkFramebuffer& p_framebuffer ) noexcept
{
    beginRecording();

    recordCommands( p_framebuffer );

    endRecording();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::beginRecording() noexcept
{
    vkBeginCommandBuffer(_cmdBuffer, &_beginRecordInfo);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::endRecording() noexcept
{
    vkEndCommandBuffer(_cmdBuffer);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::recordCommands(VkFramebuffer& p_framebuffer) noexcept
{
    initRenderPass( p_framebuffer );

    vkCmdBindPipeline( _cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline );

    initDynamicStates();

    passPushConstantData();

    vkCmdDraw( _cmdBuffer, 6, 1, 0, 0);

    vkCmdEndRenderPass( _cmdBuffer );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::initRenderPass( VkFramebuffer& p_framebuffer ) noexcept
{
    VkRenderPassBeginInfo _beginInfo {};

    _beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    _beginInfo.pNext = nullptr;
    
    _beginInfo.renderPass = _renderPass;
    _beginInfo.framebuffer = p_framebuffer;

    _beginInfo.renderArea.offset = { 0, 0 };
    _beginInfo.renderArea.extent = _swapInfo.imageExtent;

    _beginInfo.clearValueCount = 1;
    VkClearValue blackColor {0.f,0.f,0.f,1.f};
    _beginInfo.pClearValues = &blackColor;

    vkCmdBeginRenderPass( _cmdBuffer, &_beginInfo, VK_SUBPASS_CONTENTS_INLINE );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::initCommandBufferRecordingInfo() noexcept
{
    _beginRecordInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    _beginRecordInfo.pNext = nullptr;
    _beginRecordInfo.flags = 0;
    _beginRecordInfo.pInheritanceInfo = nullptr;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::initDynamicStates() noexcept
{
    VkViewport viewport{};

    viewport.x = 0;
    viewport.y = 0;
    viewport.height = _swapInfo.imageExtent.height;
    viewport.width = _swapInfo.imageExtent.width;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport( _cmdBuffer, 0, 1, &viewport );

    VkRect2D _scissor {};

    _scissor.offset = { 0 , 0 };
    _scissor.extent = _swapInfo.imageExtent;

    vkCmdSetScissor( _cmdBuffer, 0, 1, &_scissor );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::passPushConstantData() noexcept
{
    auto width  = (float)_swapInfo.imageExtent.width;
    auto heigth = (float)_swapInfo.imageExtent.height;
    auto time   = (float)Timer::getInstance().ellapsedSeconds();

    Vector<float> resolution { width, heigth, time };

    uint32_t finalSize = getPushConstantSize(resolution);

    vkCmdPushConstants(
        _cmdBuffer, _layout, VK_SHADER_STAGE_FRAGMENT_BIT,
        0, finalSize, resolution.data() 
    );

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
uint32_t
DrawerMng::getPushConstantSize( const Vector<T>& p_data ) noexcept
{
    auto dataSize   = p_data.size() * sizeof(p_data.data()[0]) ;
    auto multiple4  = (int)std::log2( dataSize );
    
    uint32_t perfectSize = pow(2,multiple4);
    uint32_t difference  = dataSize % perfectSize ;

    uint32_t finalSize = (difference == 0) ? perfectSize : pow(2,multiple4+1);

    return finalSize;
}
