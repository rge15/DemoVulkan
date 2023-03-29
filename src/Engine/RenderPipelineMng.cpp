#include "RenderPipelineMng.hpp"


RenderPipelineMng::RenderPipelineMng(
    VkDevice& p_device,
    VkRenderPass& p_renderPass,
    VkPipelineLayout& p_layout,
    const GraphicPipelineConfig& p_config,
    Vector<VkPipelineShaderStageCreateInfo> p_shaderStages) noexcept
    : device_       { p_device }
    , renderPass_   { p_renderPass }
    , layout_       { p_layout }
    , config_       { p_config }
    , shaderStages_ { p_shaderStages }
{
    initCreateInfo();
    createPipeline();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

RenderPipelineMng::~RenderPipelineMng()
{
    vkDestroyPipeline( device_, pipeline_, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPipelineMng::initCreateInfo()
{
    createInfo_.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    createInfo_.pNext = nullptr;
    createInfo_.flags = 0;

    createInfo_.stageCount  = shaderStages_.size();
    createInfo_.pStages     = shaderStages_.data();

    createInfo_.pViewportState      = &config_.viewportScissorInfo_;
    createInfo_.pVertexInputState   = &config_.vertexInputInfo_;
    createInfo_.pRasterizationState = &config_.rasterInfo_;
    createInfo_.pInputAssemblyState = &config_.assemblyInfo_;
    createInfo_.pMultisampleState   = &config_.msaaInfo_;
    createInfo_.pDynamicState       = &config_.dynamicInfo_;
    createInfo_.pColorBlendState    = &config_.colorInfo_;
    createInfo_.pDepthStencilState  = nullptr;
    createInfo_.pTessellationState  = nullptr;

    createInfo_.layout      = layout_;
    createInfo_.renderPass  = renderPass_;
    createInfo_.subpass     = 0;

    createInfo_.basePipelineHandle  = VK_NULL_HANDLE;
    createInfo_.basePipelineIndex   = -1;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
RenderPipelineMng::createPipeline()
{
    auto result = vkCreateGraphicsPipelines( device_, VK_NULL_HANDLE, 1, &createInfo_, nullptr, &pipeline_);

    assert(result == VK_SUCCESS);
}
