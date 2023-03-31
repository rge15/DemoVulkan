#pragma once
#include <Engine/Driver.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/DrawerMng/CommandMng.hpp>
#include <Engine/DrawerMng/WorkMng.hpp>
#include <Engine/Resources/DemoTrack.hpp> 

class DrawerMng
{
private:
    Driver&     driver_;
    //TODO : Creo que el renderer no debe ir aquí sino acceder desde el DemoFX que se ejecute (2º Iteración)
    Renderer&   render_;

    UniqPtr<CommandMng> command_    { nullptr };
    UniqPtr<WorkMng>    work_       { nullptr };
    UniqPtr<DemoTrack>  track_      { nullptr };

public:
    explicit DrawerMng(Driver& p_driver, Renderer& p_render) noexcept;
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

};
