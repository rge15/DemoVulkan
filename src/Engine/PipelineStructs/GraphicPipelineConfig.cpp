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
    _dynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    _dynamicInfo.pNext = nullptr;
    _dynamicInfo.flags = 0;
    _dynamicInfo.dynamicStateCount = _dynamicStates.size(); 
    _dynamicInfo.pDynamicStates = _dynamicStates.data();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configVertexInput() noexcept
{
    _vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    _vertexInputInfo.pNext = nullptr;
    _vertexInputInfo.flags = 0;
    _vertexInputInfo.vertexBindingDescriptionCount = 0;
    _vertexInputInfo.pVertexBindingDescriptions = nullptr;
    _vertexInputInfo.vertexAttributeDescriptionCount = 0;
    _vertexInputInfo.pVertexAttributeDescriptions = nullptr;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configInputAssembly() noexcept
{
    _assemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    _assemblyInfo.pNext = nullptr;
    _assemblyInfo.flags = 0;
    _assemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    _assemblyInfo.primitiveRestartEnable = VK_FALSE;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configViewportScissor() noexcept
{
    _viewportScissorInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    _viewportScissorInfo.pNext = nullptr;
    _viewportScissorInfo.flags = 0;
    _viewportScissorInfo.viewportCount = 1;
    _viewportScissorInfo.scissorCount = 1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configRasterizer() noexcept
{
    _rasterInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    _rasterInfo.pNext = nullptr;
    _rasterInfo.flags = 0;
    _rasterInfo.depthClampEnable = VK_FALSE;
    _rasterInfo.rasterizerDiscardEnable = VK_FALSE;
    _rasterInfo.polygonMode = VK_POLYGON_MODE_FILL;
    _rasterInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    _rasterInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    _rasterInfo.depthBiasEnable = VK_FALSE;
    _rasterInfo.lineWidth = 1.f;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configMultisample() noexcept
{
    _msaaInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    _msaaInfo.pNext = nullptr;
    _msaaInfo.flags = 0;
    _msaaInfo.sampleShadingEnable = VK_FALSE;
    _msaaInfo.rasterizationSamples= VK_SAMPLE_COUNT_1_BIT;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
GraphicPipelineConfig::configColorBlending() noexcept
{
    _colorBlendAttach.blendEnable = VK_FALSE;
    _colorBlendAttach.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    _colorInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    _colorInfo.pNext = nullptr;
    _colorInfo.flags = 0;
    _colorInfo.logicOpEnable = VK_FALSE;

    _colorInfo.attachmentCount = 1;
    _colorInfo.pAttachments = &_colorBlendAttach;
    _colorInfo.blendConstants[0] = 0.f;
    _colorInfo.blendConstants[1] = 0.f;
    _colorInfo.blendConstants[2] = 0.f;
    _colorInfo.blendConstants[3] = 0.f;
}