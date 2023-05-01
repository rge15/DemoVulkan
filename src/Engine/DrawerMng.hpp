#pragma once
#include <Engine/Driver.hpp>
#include <Engine/Render/RendererCmp.hpp>
#include <Engine/DrawerMng/CommandMng.hpp>
#include <Engine/DrawerMng/WorkMng.hpp>
#include <Engine/Resources/DemoTrack.hpp> 

/**
 * @brief DrawerMng that controls all the drawing process and syncronization between commands
 */
class DrawerMng
{
private:
    //! Driver manager for set the DrawerMng components
    Driver&     driver_;
    //! Renderer manager for set the DrawerMng components
    RendererType&   renderer_;

    //! Ptr Command Manager
    UniqPtr<CommandMng> command_    { nullptr };
    //! Ptr Work Manager
    UniqPtr<WorkMng>    work_       { nullptr };
    //! Ptr Demotrack
    UniqPtr<DemoTrack>  track_      { nullptr };

public:
    /**
     * @brief Construct a new Drawer Mng object
     * 
     * @param p_driver Driver manager to use for components of the class
     * @param p_renderer Renderer manager to use for components of the class
     */
    explicit DrawerMng(Driver& p_driver, RendererType& p_renderer) noexcept;
    ~DrawerMng() = default;

    /**
     * @brief Manages the draw process of an entire fotogram
     */
    void
    drawFrame() noexcept;

    /**
     * @brief Get the DemoTrack
     * 
     * @return DemoTrack& 
     */
    inline
    DemoTrack& getTrack(){ return *track_.get(); };

private:

    /**
     * @brief Inits the Command Buffer manager
     */
    void initCommander();

    /**
     * @brief Inits the Worker manager
     */
    void initWorker();

    /**
     * @brief Get the necesary data and syncronize the command recording process
     * 
     * @return uint32_t Id of the swapchain image to render
     */
    uint32_t
    getReadyToRecord() noexcept;

    /**
     * @brief Gets the Swapchain Image Id
     * 
     * @return uint32_t Id of the swapchain image to render
     */
    uint32_t
    getFrameBufferId() noexcept;

    /**
     * @brief Records the buffer command with the current playing demos
     * 
     * @param p_imageId Swapchain Image Id to init the render pass with 
     * @param p_demos Current Playing FX to draw 
     */
    void
    recordCommand( uint32_t p_imageId, Vector<PlayingClip>& p_demos ) noexcept;

    /**
     * @brief Submit the recorded command to the GPU for his execution
     * 
     * @param p_imageId Swapchain Image Id to indicate the image to use on submission
     */
    void
    submitCommands( uint32_t p_imageId ) noexcept;

    /**
     * @brief Binds the layout data to the graphics pipeline 
     * 
     * This method can be optimized with the changes at @see DemoFX
     * 
     * @param p_cmd Command buffer to bind the data to
     * @param p_type Layout Type of the pipeline to use 
     * @param p_relativeTime Relative Demo execution time
     */
    void
    bindLayoutData( VkCommandBuffer& p_cmd, LayoutTypes p_type, float p_relativeTime );

};
