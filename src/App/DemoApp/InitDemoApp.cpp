#include "InitDemoApp.hpp"
#include <Engine/Driver.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/Resources/DemoFX.hpp>
#include <Engine/DrawerMng.hpp>

//Let this darkness be
//Orders of magnitude
//The tale of blue bird and the dragon

void
InitDemoApp::run()
{
    
    //Driver -----------
    auto driver = std::make_unique<Driver>();

    auto&   deviceMng   = driver.get()->getDeviceManager();   
    auto&   device      = deviceMng.getDevice();
    
    auto&   window = driver.get()->getWindowManager().getWindow();
    //Driver -----------
    
    //Renderer ---------
    auto renderer = std::make_unique<Renderer>( *driver.get() );
    //Renderer ---------


    //DemoFX1 -----------
    auto demoFX = std::make_unique<DemoFX>( *driver.get(), *renderer.get() );
    demoFX.get()->setVertexShader("src/shaders/vert.spv");
    demoFX.get()->setFragmentShader("src/shaders/frag.spv");
    demoFX.get()->prepareToRender();
    //DemoFX1 -----------
    
    //DemoFX2 -----------
    auto demoFX2 = std::make_unique<DemoFX>( *driver.get(), *renderer.get() );
    demoFX2.get()->setVertexShader("src/shaders/vert.spv");
    demoFX2.get()->setFragmentShader("src/shaders/time.spv");
    demoFX2.get()->prepareToRender();
    //DemoFX2 -----------


    //Drawer Class -----
    auto drawerMng = std::make_unique<DrawerMng>( *driver.get(), *renderer.get() );

    auto& track = drawerMng.get()->getTrack();

    track.addFXToTrack( *demoFX2.get(), 0., 5. );
    track.addFXToTrack( *demoFX.get(), 5., 5. );

    auto& timer = Timer::getInstance();
    timer.reset();

    while( glfwGetKey(&window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(&window) && timer.ellapsedSeconds() < track.getMaxPlayTime() )
    {
        if(timer.update())
        {
            glfwPollEvents();
            drawerMng.get()->drawFrame();
        }
    }

    vkDeviceWaitIdle(device);
}