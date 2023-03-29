#pragma once
#include <Engine/Render/GraphicPipelineConfig.hpp>
#include <Engine/Sources/ShaderSrc.hpp>
#include <Engine/Driver.hpp>
#include <Engine/Renderer.hpp>
#include <utilities/Engine/engineTypeAlias.hpp>
#include <Engine/RenderPipelineMng.hpp>

class DemoFX
{
private:
    Driver& driver_;
    Renderer& renderer_;

    GraphicPipelineConfig pipelineConfig {};
    UniqPtr<ShaderSrc> vertexShader_    { nullptr };
    UniqPtr<ShaderSrc> fragmentShader_  { nullptr };

    UniqPtr<RenderPipelineMng> renderPipeline_ { nullptr };

    ShaderStagesVector shaderStages_ {};

public:
    explicit DemoFX(Driver& p_driver, Renderer& p_renderer) noexcept;
    ~DemoFX() = default;

    inline GraphicPipelineConfig& getPipeConfig(){ return pipelineConfig; };

    RenderPipelineMng& getRenderPipelieneMng();

    void setVertexShader( std::string_view p_shaderPath ) noexcept;

    void setFragmentShader( std::string_view p_shaderPath ) noexcept;

    void prepareToRender() noexcept;

private:

    void prepareShaderStages() noexcept;

    void createRenderPipeline() noexcept;

};