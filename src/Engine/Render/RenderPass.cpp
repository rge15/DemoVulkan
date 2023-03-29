#include "RenderPass.hpp"

RenderPass::RenderPass(VkDevice& p_device, const SwapchainMng& p_swapMng)
: device_ { p_device }, swapMng_ { p_swapMng }
{
    initInfo();
    createRenderPass();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

RenderPass::~RenderPass()
{
    vkDestroyRenderPass( device_, renderPass_, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPass::initInfo() noexcept
{
    initAttachmentInfo();
    initSubpassInfo();

    renderPassInfo_.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo_.pNext = nullptr;
    renderPassInfo_.flags = 0;

    renderPassInfo_.attachmentCount = 1;
    renderPassInfo_.pAttachments = &attachmentDesc_;

    renderPassInfo_.subpassCount = 1;
    renderPassInfo_.pSubpasses = &subpassDesc_;

    renderPassInfo_.dependencyCount = 0;
    renderPassInfo_.pDependencies = nullptr;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPass::createRenderPass() noexcept
{
    auto result = vkCreateRenderPass( device_, &renderPassInfo_, nullptr, &renderPass_ );

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPass::initAttachmentInfo() noexcept
{
    auto _swapInfo = swapMng_.getSwapchainInfo();
    
    attachmentDesc_.flags = 0;
    attachmentDesc_.format = _swapInfo.imageFormat;
    attachmentDesc_.samples = VK_SAMPLE_COUNT_1_BIT;

    attachmentDesc_.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDesc_.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    attachmentDesc_.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDesc_.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDesc_.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDesc_.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPass::initSubpassInfo() noexcept
{
    subpassDesc_.flags = 0;
    subpassDesc_.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    subpassDesc_.inputAttachmentCount = 0;
    subpassDesc_.pInputAttachments = nullptr;

    attachmentReference_.attachment = 0;
    attachmentReference_.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    subpassDesc_.colorAttachmentCount = 1;
    subpassDesc_.pColorAttachments = &attachmentReference_;

    subpassDesc_.pDepthStencilAttachment = nullptr;
    subpassDesc_.preserveAttachmentCount = 0;
    subpassDesc_.pPreserveAttachments = nullptr;
    subpassDesc_.pResolveAttachments = nullptr;
}
