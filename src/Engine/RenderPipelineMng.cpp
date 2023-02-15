#include "RenderPipelineMng.hpp"


RenderPipelineMng::RenderPipelineMng(
    VkDevice& p_device,
    VkRenderPass& p_renderPass,
    VkPipelineLayout& p_layout,
    const GraphicPipelineConfig& p_config,
    Vector<VkPipelineShaderStageCreateInfo> p_shaderStages) noexcept
    : _device       { p_device }
    , _renderPass   { p_renderPass }
    , _layout       { p_layout }
    , _config       { p_config }
    , _shaderStages { p_shaderStages }
{
    initCreateInfo();
    createPipeline();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

RenderPipelineMng::~RenderPipelineMng()
{
    vkDestroyPipeline( _device, _pipeline, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPipelineMng::initCreateInfo()
{
    _createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    _createInfo.pNext = nullptr;
    _createInfo.flags = 0;

    _createInfo.stageCount  = _shaderStages.size();
    _createInfo.pStages     = _shaderStages.data();

    _createInfo.pViewportState      = &_config._viewportScissorInfo;
    _createInfo.pVertexInputState   = &_config._vertexInputInfo;
    _createInfo.pRasterizationState = &_config._rasterInfo;
    _createInfo.pInputAssemblyState = &_config._assemblyInfo;
    _createInfo.pMultisampleState   = &_config._msaaInfo;
    _createInfo.pDynamicState       = &_config._dynamicInfo;
    _createInfo.pColorBlendState    = &_config._colorInfo;
    _createInfo.pDepthStencilState  = nullptr;
    _createInfo.pTessellationState  = nullptr;

    _createInfo.layout      = _layout;
    _createInfo.renderPass  = _renderPass;
    _createInfo.subpass     = 0;

    _createInfo.basePipelineHandle  = VK_NULL_HANDLE;
    _createInfo.basePipelineIndex   = -1;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPipelineMng::createPipeline()
{
    auto result = vkCreateGraphicsPipelines( _device, VK_NULL_HANDLE, 1, &_createInfo, nullptr, &_pipeline);

    assert(result == VK_SUCCESS);
}
