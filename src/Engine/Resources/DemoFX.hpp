#pragma once
#include <Engine/Render/GraphicPipelineConfig.hpp>
#include <Engine/Sources/ShaderSrc.hpp>
#include <Engine/Driver.hpp>
#include <utilities/Engine/engineTypeAlias.hpp>
#include <Engine/Resources/RenderPipelineMng.hpp>
#include <Engine/Render/RendererCmp.hpp>

class DemoFX
{
private:
    Driver& driver_;
    RendererType& renderer_;

    LayoutTypes pipelineLayoutId;

    GraphicPipelineConfig pipelineConfig {};
    UniqPtr<ShaderSrc> vertexShader_    { nullptr };
    UniqPtr<ShaderSrc> fragmentShader_  { nullptr };

    UniqPtr<RenderPipelineMng> renderPipeline_ { nullptr };

    ShaderStagesVector shaderStages_ {};

public:
    explicit DemoFX(Driver& p_driver, RendererType& p_renderer, LayoutTypes p_layType) noexcept;
    ~DemoFX() = default;

    inline GraphicPipelineConfig& getPipeConfig(){ return pipelineConfig; };

    RenderPipelineMng& getRenderPipelieneMng();

    void setVertexShader( std::string_view p_shaderPath ) noexcept;

    void setFragmentShader( std::string_view p_shaderPath ) noexcept;

    void prepareToRender() noexcept;

    inline
    RendererType&
    getDemoRenderer(){ return renderer_; };

    LayoutTypes
    getLayoutId() const noexcept;

private:

    void prepareShaderStages() noexcept;

    void createRenderPipeline() noexcept;

};