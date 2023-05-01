#pragma once
#include <Engine/Render/GraphicPipelineConfig.hpp>
#include <Engine/Sources/ShaderSrc.hpp>
#include <Engine/Driver.hpp>
#include <utilities/Engine/engineTypeAlias.hpp>
#include <Engine/Resources/RenderPipelineMng.hpp>
#include <Engine/Render/RendererCmp.hpp>

//TODO : Make it template and make the render layout selection on compiletime
//TODO : Make a Resource Manager and don't make the FX manage the shader
//TODO : Make to specify the shaders on constructor
/**
 * @brief Class for managing and effect runned by GPU
 * 
 * This class manages all the needed resources for execute a FX for GPU
 * It manages the renderpipeline used for record the draw command for the FX
 * 
 * Is needed to specify the pipeline layer in runtime with the pipeLayoutId
 * @see Renderer.hpp LayoutType 
 */
class DemoFX
{
private:
    //! Reference to the Driver Mng
    Driver& driver_;
    //! Reference to the Renderer
    RendererType& renderer_;

    //! Pipeline Layout Type Id
    LayoutTypes pipelineLayoutId;

    //! Graphic Pipeline Configuration
    GraphicPipelineConfig pipelineConfig {};
    //! Vertex Shader Rsc Manager
    UniqPtr<ShaderSrc> vertexShader_    { nullptr };
    //! Fragment Shader Rsc Manager
    UniqPtr<ShaderSrc> fragmentShader_  { nullptr };

    //! Render Pipeline Manager
    UniqPtr<RenderPipelineMng> renderPipeline_ { nullptr };

    //! Vector of shader stage data
    ShaderStagesVector shaderStages_ {};

public:
    /**
     * @brief Construct a new DemoFX
     * 
     * @param p_driver Reference to DriverMng of the engine that has to manage the demo render rsc
     * @param p_renderer Refenrence to the renderer rsc manager
     * @param p_layType Pipeline Layout Id 
     */
    explicit DemoFX(Driver& p_driver, RendererType& p_renderer, LayoutTypes p_layType) noexcept;
    /**
     * @brief Destroy the DemoFX
     */
    ~DemoFX() = default;

    /**
     * @brief Get the Render Pipeline Config object
     * 
     * @return GraphicPipelineConfig& 
     */
    inline GraphicPipelineConfig& getPipeConfig(){ return pipelineConfig; };

    /**
     * @brief Get the Render Pipeliene Mng object
     * 
     * First checks if it exists
     * 
     * @return RenderPipelineMng& 
     */
    RenderPipelineMng& getRenderPipelieneMng();

    /**
     * @brief Set & construct the Vertex Shader object givven the shader filepath
     * 
     * @param p_shaderPath Path to the vertex shader
     */
    void setVertexShader( std::string_view p_shaderPath ) noexcept;


    /**
     * @brief Set & construct the Fragment Shader object givven the shader filepath
     * 
     * @param p_shaderPath Path to the fragment shader
     */
    void setFragmentShader( std::string_view p_shaderPath ) noexcept;

    /**
     * @brief Cheks and configure all the FX render set up
     */
    void prepareToRender() noexcept;

    /**
     * @brief Get the Layout Id object
     * 
     * @return LayoutTypes 
     */
    LayoutTypes
    getLayoutId() const noexcept;

private:

    /**
     * @brief Prepares the shader stages for the render pipeline creation
     */
    void prepareShaderStages() noexcept;

    /**
     * @brief Create the FX Render Pipeline with the FX resources
     */
    void createRenderPipeline() noexcept;

};