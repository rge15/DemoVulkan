#pragma once
#include <Engine/Driver.hpp>
#include <Engine/Render/RendererCmp.hpp>
#include <Engine/DrawerMng/CommandMng.hpp>
#include <Engine/DrawerMng/WorkMng.hpp>
#include <Engine/Resources/DemoTrack.hpp> 

class DrawerMng
{
private:
    Driver&     driver_;
    RendererType&   renderer_;

    UniqPtr<CommandMng> command_    { nullptr };
    UniqPtr<WorkMng>    work_       { nullptr };
    UniqPtr<DemoTrack>  track_      { nullptr };

public:
    explicit DrawerMng(Driver& p_driver, RendererType& p_renderer) noexcept;
    ~DrawerMng() = default;

    void
    drawFrame() noexcept;

    inline
    DemoTrack& getTrack(){ return *track_.get(); };

private:

    void initCommander();
    
    void initWorker();

    uint32_t
    getReadyToRecord() noexcept;

    uint32_t
    getFrameBufferId() noexcept;

    void
    recordCommand( uint32_t p_imageId, Vector<PlayingClip>& p_demos ) noexcept;

    void
    submitCommands( uint32_t p_imageId ) noexcept;

    void
    bindLayoutData( VkCommandBuffer& p_cmd, LayoutTypes p_type, float p_relativeTime );

};
