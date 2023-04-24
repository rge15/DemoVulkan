#include "BaseRenderPass.hpp"

BaseRenderPass::BaseRenderPass( VkDevice& p_device, const SwapchainMng& p_swapMng ) noexcept
: device_ { p_device }, swapMng_ { p_swapMng }
{
    initBaseCreateInfo();
}

BaseRenderPass::~BaseRenderPass()
{
    if( renderPass_ != VK_NULL_HANDLE )
        vkDestroyRenderPass( device_, renderPass_, nullptr );
}

void
BaseRenderPass::createRenderPass() noexcept
{
    auto result = vkCreateRenderPass( device_, &createInfo_, nullptr, &renderPass_ );

    assert(result == VK_SUCCESS);
}

void
BaseRenderPass::initBaseCreateInfo() noexcept
{
    initBaseAttachementInfo();
    initBaseSupbassInfo();

    createInfo_.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    createInfo_.pNext = nullptr;
    createInfo_.flags = 0;

    createInfo_.attachmentCount = 1;
    createInfo_.pAttachments = &attachmentDesc_;

    createInfo_.subpassCount = 1;
    createInfo_.pSubpasses = &subpassDesc_;

    createInfo_.dependencyCount = 0;
    createInfo_.pDependencies = nullptr;
}


void
BaseRenderPass::initBaseAttachementInfo() noexcept
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

void
BaseRenderPass::initBaseSupbassInfo() noexcept
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
