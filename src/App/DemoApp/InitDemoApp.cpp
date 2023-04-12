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
    
    //TimeFX -----------
    auto timeFX = std::make_unique<DemoFX>( driver, renderer );
    timeFX.get()->setVertexShader("src/shaders/vert.spv");
    timeFX.get()->setFragmentShader("src/shaders/time.spv");
    timeFX.get()->prepareToRender();
    //TimeFX -----------

    //BandTrans -----------
    auto bandTrans = std::make_unique<DemoFX>( driver, renderer );
    bandTrans.get()->setVertexShader("src/shaders/vert.spv");
    bandTrans.get()->setFragmentShader("src/shaders/bandTrans.spv");
    bandTrans.get()->prepareToRender();
    //BandTrans -----------

    //ColorBands -----------
    auto colorBands = std::make_unique<DemoFX>( driver, renderer );
    colorBands.get()->setVertexShader("src/shaders/vert.spv");
    colorBands.get()->setFragmentShader("src/shaders/colorBands.spv");
    colorBands.get()->prepareToRender();
    //ColorBands -----------

    //BlobsFX -----------
    auto blobsFX = std::make_unique<DemoFX>( driver, renderer );
    blobsFX.get()->setVertexShader("src/shaders/vert.spv");
    blobsFX.get()->setFragmentShader("src/shaders/blob.spv");
    blobsFX.get()->prepareToRender();
    //BlobsFX -----------

    //Drawer Class -----
    auto& drawerMng = demoEng.get()->getDrawer();

    auto& track = drawerMng.getTrack();

    //track.addFXToTrack( *timeFX.get(), 0., 5. );
    
    //track.addFXToTrack( *bandTrans.get(), 0., 5. );
    
    track.addFXToTrack( *colorBands.get(), 0., 30. );
    
    //track.addFXToTrack( *blobsFX.get(), 10., 5. );

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