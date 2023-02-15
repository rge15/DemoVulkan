#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/PipelineStructs/GraphicPipelineConfig.hpp>
#include <Engine/PipelineStructs/PipelineLayout.hpp>
#include <Engine/PipelineStructs/RenderPass.hpp>


class RenderPipelineMng
{
private:
    VkDevice&   _device;

    VkRenderPass&                     _renderPass;
    VkPipelineLayout&                 _layout;
    const GraphicPipelineConfig&    _config;

    Vector<VkPipelineShaderStageCreateInfo> _shaderStages;

    VkGraphicsPipelineCreateInfo _createInfo {};

public:
    VkPipeline _pipeline { VK_NULL_HANDLE };

public:
    RenderPipelineMng(
        VkDevice& p_device,
        VkRenderPass& p_renderPass,
        VkPipelineLayout& p_layout,
        const GraphicPipelineConfig& p_config,
        Vector<VkPipelineShaderStageCreateInfo> p_shaderStages ) noexcept;
    
    ~RenderPipelineMng();

private:

    void
    initCreateInfo();
    
    void
    createPipeline();

};
