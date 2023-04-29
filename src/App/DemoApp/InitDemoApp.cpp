#include "InitDemoApp.hpp"
#include <Engine/Resources/DemoFX.hpp>
#include <Engine/DemoEngine.hpp>

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
    auto timeFX = std::make_unique<DemoFX>( driver, renderer, LayoutTypes::BasicLayout );
    timeFX.get()->setVertexShader("src/shaders/vert.spv");
    timeFX.get()->setFragmentShader("src/shaders/time.spv");
    timeFX.get()->prepareToRender();
    //TimeFX -----------

    //BandTrans -----------
    auto bandTrans = std::make_unique<DemoFX>( driver, renderer, LayoutTypes::BasicLayout );
    bandTrans.get()->setVertexShader("src/shaders/vert.spv");
    bandTrans.get()->setFragmentShader("src/shaders/bandTrans.spv");
    bandTrans.get()->prepareToRender();
    //BandTrans -----------

    //ColorBands -----------
    auto colorBands = std::make_unique<DemoFX>( driver, renderer, LayoutTypes::BasicLayout );
    colorBands.get()->setVertexShader("src/shaders/vert.spv");
    colorBands.get()->setFragmentShader("src/shaders/colorBands.spv");
    colorBands.get()->prepareToRender();
    //ColorBands -----------

    //BlobsFX -----------
    auto blobsFX = std::make_unique<DemoFX>( driver, renderer, LayoutTypes::BasicLayout );
    blobsFX.get()->setVertexShader("src/shaders/vert.spv");
    blobsFX.get()->setFragmentShader("src/shaders/blob.spv");
    blobsFX.get()->prepareToRender();
    //BlobsFX -----------

    //TripFX -----------
    auto tripFX = std::make_unique<DemoFX>( driver, renderer, LayoutTypes::BasicLayout );
    tripFX.get()->setVertexShader("src/shaders/vert.spv");
    tripFX.get()->setFragmentShader("src/shaders/tripColor.spv");
    tripFX.get()->prepareToRender();
    //TripFX -----------

    //CircleMask -----------
    auto circleMask = std::make_unique<DemoFX>( driver, renderer, LayoutTypes::BasicLayout );
    circleMask.get()->setVertexShader("src/shaders/vert.spv");
    circleMask.get()->setFragmentShader("src/shaders/circleForms.spv");
    circleMask.get()->prepareToRender();
    //CircleMask -----------

    //TimeImage -----------
    auto imageMask = std::make_unique<DemoFX>( driver, renderer, LayoutTypes::ImageLayout );
    imageMask.get()->setVertexShader("src/shaders/vert.spv");
    imageMask.get()->setFragmentShader("src/shaders/timeImg.spv");
    imageMask.get()->prepareToRender();
    //TimeImage -----------


    //TODO : Create a demoFX that uses the other pipelinelayout and ckeck if it works


    //Drawer Class -----
    auto& drawerMng = demoEng.get()->getDrawer();

    auto& track = drawerMng.getTrack();

    track.addFXToTrack( *timeFX.get(), 0., 10. );

    //Duration 25s
    track.addFXToTrack( *imageMask.get(), 10., 30. );
    
    track.addFXToTrack( *bandTrans.get(), 40., 5. );
    
    //Duration 40s
    track.addFXToTrack( *colorBands.get(), 45., 40. );
    
    //Duration 20s
    track.addFXToTrack( *blobsFX.get(), 85., 20. );

    //Duration 25s
    track.addFXToTrack( *tripFX.get(), 105., 25. );

    //Duration 30s
    track.addFXToTrack( *circleMask.get(), 130., 60. );


    vkDeviceWaitIdle(device);
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