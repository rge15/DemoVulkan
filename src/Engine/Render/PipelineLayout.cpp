#include "PipelineLayout.hpp"

PipelineLayout::PipelineLayout( VkDevice& p_device )
: device_ { p_device }
{
    addPushConstants();
    initCreateInfo();
    createLayout();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

PipelineLayout::~PipelineLayout()
{
    vkDestroyPipelineLayout( device_, pipeLayout_, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::initCreateInfo()
{
    layoutInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    layoutInfo_.pNext = nullptr;
    layoutInfo_.flags = 0;
    layoutInfo_.setLayoutCount = 0;
    layoutInfo_.pSetLayouts = nullptr;
    layoutInfo_.pushConstantRangeCount = pushConstantsInfo_.size();
    layoutInfo_.pPushConstantRanges = pushConstantsInfo_.data();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::createLayout()
{
    auto result = vkCreatePipelineLayout( device_, &layoutInfo_, nullptr, &pipeLayout_);

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::addPushConstants()
{
    auto& resolutionCnst        = pushConstantsInfo_.emplace_back();
    resolutionCnst.stageFlags   = VK_SHADER_STAGE_FRAGMENT_BIT;
    resolutionCnst.offset       = 0;
    resolutionCnst.size         = sizeof( float ) * 4;
}
