#include "InitDemoApp.hpp"
#include <Engine/Resources/DemoFX.hpp>
#include <Engine/DemoEngine.hpp>

//Let this darkness be
//Orders of magnitude
//The tale of blue bird and the dragon

void
InitDemoApp::run()
{
    auto demoEng = std::make_unique<DemoEngine>();

    //Driver -----------
    auto& driver = demoEng.get()->getDriver();
    auto& device = driver.getDeviceManager().getDevice();
    auto& window = driver.getWindowManager().getWindow();
    //Driver -----------
    
    //Renderer ---------
    auto& renderer = demoEng.get()->getRenderer();
    //Renderer ---------

    //DemoFX1 -----------
    auto demoFX = std::make_unique<DemoFX>( driver, renderer );
    demoFX.get()->setVertexShader("src/shaders/vert.spv");
    demoFX.get()->setFragmentShader("src/shaders/frag.spv");
    demoFX.get()->prepareToRender();
    //DemoFX1 -----------
    
    //DemoFX2 -----------
    auto demoFX2 = std::make_unique<DemoFX>( driver, renderer );
    demoFX2.get()->setVertexShader("src/shaders/vert.spv");
    demoFX2.get()->setFragmentShader("src/shaders/time.spv");
    demoFX2.get()->prepareToRender();
    //DemoFX2 -----------


    //Drawer Class -----
    auto& drawerMng = demoEng.get()->getDrawer();

    auto& track = drawerMng.getTrack();

    track.addFXToTrack( *demoFX2.get(), 0., 5. );
    track.addFXToTrack( *demoFX.get(), 5., 5. );

    auto& timer = Timer::getInstance();
    timer.reset();

    while( glfwGetKey(&window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(&window) && timer.ellapsedSeconds() < track.getMaxPlayTime() )
    {
        if(timer.update())
        {
            glfwPollEvents();
            drawerMng.drawFrame();
        }
    }

    vkDeviceWaitIdle(device);
}