#include "PipelineLayout.hpp"

PipelineLayout::PipelineLayout( VkDevice& p_device )
: _device { p_device }
{
    addPushConstants();
    initCreateInfo();
    createLayout();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

PipelineLayout::~PipelineLayout()
{
    vkDestroyPipelineLayout( _device, _pipeLayout, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::initCreateInfo()
{
    _layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    _layoutInfo.pNext = nullptr;
    _layoutInfo.flags = 0;
    _layoutInfo.setLayoutCount = 0;
    _layoutInfo.pSetLayouts = nullptr;
    _layoutInfo.pushConstantRangeCount = _pushConstantsInfo.size();
    _layoutInfo.pPushConstantRanges = _pushConstantsInfo.data();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::createLayout()
{
    auto result = vkCreatePipelineLayout( _device, &_layoutInfo, nullptr, &_pipeLayout);

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::addPushConstants()
{
    auto& resolutionCnst        = _pushConstantsInfo.emplace_back();
    resolutionCnst.stageFlags   = VK_SHADER_STAGE_FRAGMENT_BIT;
    resolutionCnst.offset       = 0;
    resolutionCnst.size         = sizeof( float ) * 4;
}
