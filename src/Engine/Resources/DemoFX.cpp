#include "DemoFX.hpp"

DemoFX::DemoFX(Driver& p_driver, RendererType& p_renderer, LayoutTypes p_layType) noexcept
: driver_ { p_driver }, renderer_ { p_renderer }, pipelineLayoutId { p_layType }
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void 
DemoFX::setVertexShader( std::string_view p_shaderPath ) noexcept
{
    auto& device = driver_.getDeviceManager().getDevice();
    
    vertexShader_ = std::make_unique<ShaderSrc>( device, p_shaderPath.data() );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void 
DemoFX::setFragmentShader( std::string_view p_shaderPath ) noexcept
{
    auto& device = driver_.getDeviceManager().getDevice();
    
    fragmentShader_ = std::make_unique<ShaderSrc>( device, p_shaderPath.data(), VK_SHADER_STAGE_FRAGMENT_BIT );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void 
DemoFX::prepareToRender() noexcept
{
    if( vertexShader_ == nullptr )
        std::cout << "There isn't a vertex shader available, call 'setVertexShader(...)' \n";
    else if (fragmentShader_ == nullptr)
        std::cout << "There isn't a fragment shader available, call 'setFragmentShader(...)' \n";
    else
    {
        prepareShaderStages();
        createRenderPipeline();
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void 
DemoFX::prepareShaderStages() noexcept
{
    shaderStages_.clear();

    auto vertexShaderStage = vertexShader_.get()->getShaderStageInfo();
    auto fragmentShaderStage = fragmentShader_.get()->getShaderStageInfo();

    shaderStages_.push_back(vertexShaderStage);
    shaderStages_.push_back(fragmentShaderStage);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void 
DemoFX::createRenderPipeline() noexcept
{
    auto& device        = driver_.getDeviceManager().getDevice();

    auto& renderPass    = renderer_.getRenderPass().getRenderPass();    
    auto& pipeLayout    = renderer_.getLayout(pipelineLayoutId);

    renderPipeline_ = std::make_unique<RenderPipelineMng>(device, renderPass, pipeLayout, pipelineConfig, shaderStages_);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

RenderPipelineMng&
DemoFX::getRenderPipelieneMng()
{
    assert( renderPipeline_ != nullptr );

    return *renderPipeline_.get();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

LayoutTypes
DemoFX::getLayoutId() const noexcept
{
    return pipelineLayoutId;
}

