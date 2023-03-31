#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/Render/GraphicPipelineConfig.hpp>
#include <Engine/Render/PipelineLayout.hpp>
#include <Engine/Render/RenderPass.hpp>


class RenderPipelineMng
{
private:
    VkDevice&   device_;

    VkRenderPass&                       renderPass_;
    VkPipelineLayout&                   layout_;
    const GraphicPipelineConfig&        config_;

    Vector<VkPipelineShaderStageCreateInfo> shaderStages_;

    VkGraphicsPipelineCreateInfo createInfo_ {};

public:
    VkPipeline pipeline_ { VK_NULL_HANDLE };

public:
    RenderPipelineMng(
        VkDevice& p_device,
        VkRenderPass& p_renderPass,
        VkPipelineLayout& p_layout,
        const GraphicPipelineConfig& p_config,
        Vector<VkPipelineShaderStageCreateInfo> p_shaderStages ) noexcept;
    
    ~RenderPipelineMng();

    void
    bindPipelineAndDynamics( VkCommandBuffer& p_cmd, const VkSwapchainCreateInfoKHR& p_swapInfo );


private:

    void
    initCreateInfo();
    
    void
    createPipeline();

};
