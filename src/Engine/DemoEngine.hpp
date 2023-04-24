#pragma once
#include <Engine/Driver.hpp>
#include <Engine/DrawerMng.hpp>
#include <Engine/Render/RendererCmp.hpp>

class DemoEngine
{
private:
    UniqPtr<Driver>         driver_     { std::make_unique<Driver>() };
    
    UniqPtr<RendererType>   renderer_   { std::make_unique<RendererType>( *driver_.get() ) };
    
    UniqPtr<DrawerMng>      drawer_     { std::make_unique<DrawerMng>( *driver_.get(), *renderer_.get() ) };

public:
    explicit DemoEngine() = default;
    ~DemoEngine() = default;

    inline
    Driver& getDriver() { return *driver_.get(); };

    inline
    RendererType& getRenderer() { return *renderer_.get(); };

    inline
    DrawerMng& getDrawer() { return *drawer_.get(); };

};