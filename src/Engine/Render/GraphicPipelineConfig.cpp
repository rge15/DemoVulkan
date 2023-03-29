#include "GraphicPipelineConfig.hpp"

GraphicPipelineConfig::GraphicPipelineConfig() noexcept
{
    configDynamicStates();
    configVertexInput();
    configInputAssembly();
    configViewportScissor();
    configRasterizer();
    configMultisample();
    configColorBlending();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configDynamicStates() noexcept
{
    dynamicInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicInfo_.pNext = nullptr;
    dynamicInfo_.flags = 0;
    dynamicInfo_.dynamicStateCount = dynamicStates_.size(); 
    dynamicInfo_.pDynamicStates = dynamicStates_.data();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configVertexInput() noexcept
{
    vertexInputInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo_.pNext = nullptr;
    vertexInputInfo_.flags = 0;
    vertexInputInfo_.vertexBindingDescriptionCount = 0;
    vertexInputInfo_.pVertexBindingDescriptions = nullptr;
    vertexInputInfo_.vertexAttributeDescriptionCount = 0;
    vertexInputInfo_.pVertexAttributeDescriptions = nullptr;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configInputAssembly() noexcept
{
    assemblyInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assemblyInfo_.pNext = nullptr;
    assemblyInfo_.flags = 0;
    assemblyInfo_.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    assemblyInfo_.primitiveRestartEnable = VK_FALSE;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configViewportScissor() noexcept
{
    viewportScissorInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportScissorInfo_.pNext = nullptr;
    viewportScissorInfo_.flags = 0;
    viewportScissorInfo_.viewportCount = 1;
    viewportScissorInfo_.scissorCount = 1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configRasterizer() noexcept
{
    rasterInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterInfo_.pNext = nullptr;
    rasterInfo_.flags = 0;
    rasterInfo_.depthClampEnable = VK_FALSE;
    rasterInfo_.rasterizerDiscardEnable = VK_FALSE;
    rasterInfo_.polygonMode = VK_POLYGON_MODE_FILL;
    rasterInfo_.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterInfo_.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterInfo_.depthBiasEnable = VK_FALSE;
    rasterInfo_.lineWidth = 1.f;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configMultisample() noexcept
{
    msaaInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    msaaInfo_.pNext = nullptr;
    msaaInfo_.flags = 0;
    msaaInfo_.sampleShadingEnable = VK_FALSE;
    msaaInfo_.rasterizationSamples= VK_SAMPLE_COUNT_1_BIT;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configColorBlending() noexcept
{
    colorBlendAttach_.blendEnable = VK_FALSE;
    colorBlendAttach_.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    colorInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorInfo_.pNext = nullptr;
    colorInfo_.flags = 0;
    colorInfo_.logicOpEnable = VK_FALSE;

    colorInfo_.attachmentCount = 1;
    colorInfo_.pAttachments = &colorBlendAttach_;
    colorInfo_.blendConstants[0] = 0.f;
    colorInfo_.blendConstants[1] = 0.f;
    colorInfo_.blendConstants[2] = 0.f;
    colorInfo_.blendConstants[3] = 0.f;
}