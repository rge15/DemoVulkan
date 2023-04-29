#pragma once
#include <Engine/Driver.hpp>
#include <Engine/DrawerMng.hpp>
#include <Engine/Render/RendererCmp.hpp>

/**
 * @brief DemoEngine class that holds and mantain entire engine components.
 */
class DemoEngine
{
private:

    //! Ptr to the DriverMng of the Engine
    UniqPtr<Driver>         driver_     { std::make_unique<Driver>() };
    
    //! Ptr to the Renderer specified for the Engine
    UniqPtr<RendererType>   renderer_   { std::make_unique<RendererType>( *driver_.get() ) };
    
    //! Ptr to the DrawerMng of the Engine
    UniqPtr<DrawerMng>      drawer_     { std::make_unique<DrawerMng>( *driver_.get(), *renderer_.get() ) };

public:

    /**
     * @brief Construct a new Demo Engine object which inits 
     * all the uniquPtrs components 
     */
    explicit DemoEngine() = default;
    /**
     * @brief Destroy the Demo Engine object
     */
    ~DemoEngine() = default;

    /**
     * @brief Get the Driver Manager object
     * 
     * @return Driver& Reference to the engine driver manager
     */
    inline
    Driver& getDriver() { return *driver_.get(); };

    /**
     * @brief Get the Renderer object
     * 
     * @return RendererType& Reference to the Renderer with render components specified for the engine
     * @see RendererCmp.hpp
     */
    inline
    RendererType& getRenderer() { return *renderer_.get(); };

    /**
     * @brief Get the Drawer object
     * 
     * @return DrawerMng& Reference to the engine Drawer manager 
     */
    inline
    DrawerMng& getDrawer() { return *drawer_.get(); };

};