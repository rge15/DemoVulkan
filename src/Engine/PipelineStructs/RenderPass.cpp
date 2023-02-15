#include "RenderPass.hpp"

RenderPass::RenderPass(VkDevice& p_device, const SwapchainMng& p_swapMng)
: _device { p_device }, _swapMng { p_swapMng }
{
    initInfo();
    createRenderPass();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

RenderPass::~RenderPass()
{
    vkDestroyRenderPass( _device, _renderPass, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPass::initInfo() noexcept
{
    initAttachmentInfo();
    initSubpassInfo();

    _renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    _renderPassInfo.pNext = nullptr;
    _renderPassInfo.flags = 0;

    _renderPassInfo.attachmentCount = 1;
    _renderPassInfo.pAttachments = &_attachmentDesc;

    _renderPassInfo.subpassCount = 1;
    _renderPassInfo.pSubpasses = &_subpassDesc;

    _renderPassInfo.dependencyCount = 0;
    _renderPassInfo.pDependencies = nullptr;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPass::createRenderPass() noexcept
{
    auto result = vkCreateRenderPass( _device, &_renderPassInfo, nullptr, &_renderPass );

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPass::initAttachmentInfo() noexcept
{
    auto _swapInfo = _swapMng.getSwapchainInfo();
    
    _attachmentDesc.flags = 0;
    _attachmentDesc.format = _swapInfo.imageFormat;
    _attachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;

    _attachmentDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    _attachmentDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    _attachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    _attachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    _attachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    _attachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPass::initSubpassInfo() noexcept
{
    _subpassDesc.flags = 0;
    _subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    _subpassDesc.inputAttachmentCount = 0;
    _subpassDesc.pInputAttachments = nullptr;

    _attachmentReference.attachment = 0;
    _attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    _subpassDesc.colorAttachmentCount = 1;
    _subpassDesc.pColorAttachments = &_attachmentReference;

    _subpassDesc.pDepthStencilAttachment = nullptr;
    _subpassDesc.preserveAttachmentCount = 0;
    _subpassDesc.pPreserveAttachments = nullptr;
    _subpassDesc.pResolveAttachments = nullptr;
}
