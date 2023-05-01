#pragma once
#include <Engine/Driver.hpp>
#include <Engine/Render/RendererCmp.hpp>
#include <Engine/Render/BasicPipelineLayout.hpp>
#include <Engine/Render/ImagePipelineLayout.hpp>
#include <Engine/Render/BasicRenderPass.hpp>
#include <Engine/Render/PipelineFrameBuffers.hpp>
#include <utilities/Engine/renderConcepts.hpp>

//! Enum class of the different types of layouts
enum class LayoutTypes
{
    BasicLayout = 0,
    ImageLayout = 1
};

/**
 * @brief Renderer class that holds all the render components that the engine can use fo rendering process
 * 
 * Right now thee is just available 1 type of renderpass 
 * 
 * @tparam Layouts Types of Render Layouts
 */
template<typename... Layouts>  
class Renderer
{
private:
    //! Typedef for a pipline layouts obj
    template<typename... LayoutTypes>
    using PipelineLayouts = Tuple< UniqPtr<LayoutTypes>... >;

    //! Driver Mng for getting all the Vulkan Drivers
    Driver& driver_;

    //! Tuple with all the Pipeline Layout objs availables
    PipelineLayouts<Layouts...> renderLayoutTuple_;
    
    //! Render pass
    UniqPtr<BasicRenderPass> renderPass_ { nullptr };

    //! Pipeline Farmebuffer manager
    UniqPtr<PipelineFrameBuffers> framebuffer_ { nullptr };

public:
    /**
     * @brief Construct a new Renderer object
     * 
     * Inits all the render pass, pipeline layout objs and the framebuffer
     * 
     * @param p_driver Reference to the Vulkan drivers manager
     */
    Renderer( Driver& p_driver );
    
    /**
     * @brief Destroy the Renderer object and all his components
     */
    ~Renderer() = default;

    /**
     * @brief Records the init renderpass process on a command buffer 
     * 
     * @param p_imageId Spawcahin Image Id to render the init pass on
     * @param p_cmd Command Buffer to record into the begin renderpass
     */
    void
    initRenderPass( uint32_t p_imageId, VkCommandBuffer& p_cmd) noexcept;

    /**
     * @brief Inits all the pipeline layout obj types
     */
    void
    initializeLayouts();

    /**
     * @brief Get the Render Pass object
     * 
     * @return BasicRenderPass& 
     */
    inline
    BasicRenderPass&
    getRenderPass(){ return *renderPass_.get(); };

    /**
     * @brief Get the Frame Buffer object
     * 
     * @return PipelineFrameBuffers& 
     */
    inline
    PipelineFrameBuffers&
    getFrameBuffer(){ return *framebuffer_.get(); };

    /**
     * @brief Get the Pipe Layout Mng object
     * 
     * @tparam T 
     * @return T& 
     */
    template<typename T>
    T& getPipeLayoutMng();

    /**
     * @brief Get the Layout object
     * 
     * @param p_type 
     * @return VkPipelineLayout& 
     */
    VkPipelineLayout&
    getLayout( LayoutTypes p_type );

};

#include "Renderer.tpp"