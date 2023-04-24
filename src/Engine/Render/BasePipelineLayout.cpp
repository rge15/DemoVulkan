#include "BasePipelineLayout.hpp"


BasePipelineLayout::BasePipelineLayout( VkDevice& p_device, const SwapchainMng& p_swapMng ) noexcept
: device_ { p_device }, swapMng_ { p_swapMng }
{
    initBaseCreateInfo();
}

BasePipelineLayout::~BasePipelineLayout()
{
    if( pipeLayout_ != VK_NULL_HANDLE )
        vkDestroyPipelineLayout( device_, pipeLayout_, nullptr );
}

void
BasePipelineLayout::initBaseCreateInfo() noexcept
{
    createInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    createInfo_.pNext = nullptr;
    createInfo_.flags = 0;
    createInfo_.setLayoutCount = 0;
    createInfo_.pSetLayouts = nullptr;
    createInfo_.pushConstantRangeCount = 0;
    createInfo_.pPushConstantRanges = nullptr;
}

void
BasePipelineLayout::createPipelineLayout() noexcept
{
    auto result = vkCreatePipelineLayout( device_, &createInfo_, nullptr, &pipeLayout_);

    assert(result == VK_SUCCESS);
}

