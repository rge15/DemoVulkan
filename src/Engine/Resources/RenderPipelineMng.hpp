#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/Render/GraphicPipelineConfig.hpp>
#include <Engine/Render/BasePipelineLayout.hpp>
#include <Engine/Render/BaseRenderPass.hpp>

/**
 * @brief Class tha manages all the renderpipeline information
 * 
 * Each DemoFX will hold and create his specific renderpipeline
 * @see DemoFX
 */
class RenderPipelineMng
{
private:
    //! Reference to Vulkan Device to execute the pipleline
    VkDevice&   device_;

    //! Reference to the RenderPass that configures the render pipeline passes
    VkRenderPass&                       renderPass_;
    //! Reference to the PipelineLAyout that configures the render pipeline layout
    VkPipelineLayout&                   layout_;
    //! Reference to the Pipeline Stages Config obj
    const GraphicPipelineConfig&        config_;

    //! Reference to the FX shaders to play  
    Vector<VkPipelineShaderStageCreateInfo>& shaderStages_;

    //! Creation info of the pipeline
    VkGraphicsPipelineCreateInfo createInfo_ {};

public:
    //! Vulkan Handler of the Render Pipeline Obj 
    VkPipeline pipeline_ { VK_NULL_HANDLE };

public:
    /**
     * @brief Construct a new Render Pipeline Mng object
     * 
     * Inits the creation info structure and creates the Vulkan Pipeline Obj
     * 
     * @param p_device Vulkan Device to create the pipeline with and to execute the pipeline 
     * @param p_renderPass Renderpass to set the pipeline passes
     * @param p_layout Pipeline Layout to set the REnder Pipeline data layout
     * @param p_config States Configuration of the pipeline 
     * @param p_shaderStages ShaderStages of the FX to draw with this pipeline
     */
    RenderPipelineMng(
        VkDevice& p_device,
        VkRenderPass& p_renderPass,
        VkPipelineLayout& p_layout,
        const GraphicPipelineConfig& p_config,
        Vector<VkPipelineShaderStageCreateInfo>& p_shaderStages ) noexcept;
    
    /**
     * @brief Destroy the Render Pipeline Mng
     * 
     * Handles the pipeline destruction
     */
    ~RenderPipelineMng();

    /**
     * @brief Binds the dynamic states of the pipeline configuration
     * 
     * This method is little bit hardcoded for these dynamic config stages
     * @see GraphicPipelineConfig
     * 
     * @param p_cmd Command buffer to execute this pipeline with
     * @param p_swapInfo Swpachain info to get data for the dynamic stages
     */
    void
    bindPipelineAndDynamics( VkCommandBuffer& p_cmd, const VkSwapchainCreateInfoKHR& p_swapInfo );

private:

    /**
     * @brief Fills the creation info for the pipeline construction
     */
    void
    initCreateInfo();

    /**
     * @brief Create the Vulkan Graphics Pipeline object
     */
    void
    createPipeline();

};
