#pragma once
#include <Engine/Driver.hpp>
#include <Engine/Render/RendererCmp.hpp>
#include <Engine/Render/BasicPipelineLayout.hpp>
#include <Engine/Render/BasicRenderPass.hpp>
#include <Engine/Render/PipelineFrameBuffers.hpp>
#include <utilities/Engine/renderConcepts.hpp>

enum class LayoutTypes
{
    BasicLayout = 0,
    ImageLayout = 1
};

template<typename... Layouts>  
class Renderer
{
private:
    template<typename... LayoutTypes>
    using PipelineLayouts = Tuple< UniqPtr<LayoutTypes>... >;

    Driver& driver_;

    PipelineLayouts<Layouts...> renderLayoutTuple_;
    UniqPtr<BasicRenderPass> renderPass_ { nullptr };

    UniqPtr<PipelineFrameBuffers> framebuffer_ { nullptr };

public:
    Renderer( Driver& p_driver );
    
    ~Renderer() = default;

    void
    initRenderPass( uint32_t p_imageId, VkCommandBuffer& p_cmd) noexcept;

    void
    initializeLayouts();

    inline
    BasicRenderPass&
    getRenderPass(){ return *renderPass_.get(); };

    inline
    PipelineFrameBuffers&
    getFrameBuffer(){ return *framebuffer_.get(); };

    template<typename T>
    T& getPipeLayoutMng();

    VkPipelineLayout&
    getLayout( LayoutTypes p_type );

};

#include "Renderer.tpp"