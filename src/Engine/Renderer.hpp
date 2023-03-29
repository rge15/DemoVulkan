#pragma once
#include <Engine/Driver.hpp>
#include <Engine/Render/PipelineLayout.hpp>
#include <Engine/Render/RenderPass.hpp>
#include <Engine/Render/PipelineFrameBuffers.hpp>


class Renderer
{
private:
    Driver& driver_;

    UniqPtr<PipelineLayout>         pipeLayout_;
    UniqPtr<RenderPass>             renderPass_;
    UniqPtr<PipelineFrameBuffers>   framebuffer_;

public:
    Renderer( Driver& p_driver );
    
    ~Renderer() = default;

    inline PipelineLayout& getPipeLayout(){ return *pipeLayout_.get(); };

    inline RenderPass& getRenderPass(){ return *renderPass_.get(); };
    
    inline PipelineFrameBuffers& getFramebuffer(){ return *framebuffer_.get(); };

};
