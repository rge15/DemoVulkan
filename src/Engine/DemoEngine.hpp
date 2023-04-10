#pragma once
#include <Engine/Driver.hpp>
#include <Engine/DrawerMng.hpp>
#include <Engine/Renderer.hpp>


class DemoEngine
{
private:
    UniqPtr<Driver>     driver_     { std::make_unique<Driver>() };
    UniqPtr<Renderer>   renderer_   { std::make_unique<Renderer>( *driver_.get() ) };
    UniqPtr<DrawerMng>  drawer_     { std::make_unique<DrawerMng>( *driver_.get(), *renderer_.get() ) };

public:
    explicit DemoEngine() = default;
    ~DemoEngine() = default;

    inline
    Driver& getDriver() { return *driver_.get(); };

    inline
    Renderer& getRenderer() { return *renderer_.get(); };

    inline
    DrawerMng& getDrawer() { return *drawer_.get(); };

};