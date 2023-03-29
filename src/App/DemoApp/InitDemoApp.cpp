#include "InitDemoApp.hpp"
#include <Engine/Driver.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/DemoFX.hpp>

#include <Engine/DrawerMng.hpp>
#include <Engine/WorkMng.hpp>

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
    auto&   queueIds    = deviceMng.getFamilyQueueIds();
    
    auto&   swapMngObj  = driver.get()->getSwapchainManager();
    auto&   swapInfo    = swapMngObj.getSwapchainInfo();

    auto&   window = driver.get()->getWindowManager().getWindow();
    //Driver -----------
    
    //Renderer ---------
    auto renderer = std::make_unique<Renderer>( *driver.get() );

    auto& renderPass = renderer.get()->getRenderPass().getRenderPass();
    auto& pipeLayout = renderer.get()->getPipeLayout().getLayout();
    auto& framebuff  = renderer.get()->getFramebuffer();
    //Renderer ---------

    //TODO : -------------< DemoFX Class > --------------------
    //TODO : Crear DemoFX class para pasar poder tener un FX
    //TODO : Recibirá Un Driver y un Renderer obligatorio
    //TODO : Se le deberá configurar el vertex y fragment
    //TODO : Se le deberá crear la pipeline



    //TODO : -------------< Track Class > --------------------
    //TODO : Tendrá un vector de tuplas<DemoFX&, initTime, durationTime>
    //TODO : A medida que vaya haciendo falta ir implementadndo funcionalidad

    //DemoFX -----------
    auto demoFX = std::make_unique<DemoFX>( *driver.get(), *renderer.get() );
    demoFX.get()->setVertexShader("src/shaders/vert.spv");
    demoFX.get()->setFragmentShader("src/shaders/frag.spv");
    demoFX.get()->prepareToRender();
    auto& pipeline = demoFX.get()->getRenderPipelieneMng().pipeline_;
    //DemoFX -----------
    
    //TODO : -------------< Drawer Class     > --------------------
    //TODO : Tendrá un commandMng y workMng y los usará para dibuajar
    //TODO : También tendrá una clase track que ejecutará los FX

    //TODO : -------------< CommandMng Class > --------------------
    //TODO : Clase encargada de manejar todo paripé de commands

    auto drawerMng = std::make_unique<DrawerMng>( device, queueIds, renderPass, pipeline, pipeLayout,swapInfo );

    auto& draweMngObj = *drawerMng.get();

    //TODO : -------------< WorkMng Class   > --------------------
    //TODO : Clase encargada de manejar todo paripé de sincronización

    auto workMng       = std::make_unique<WorkMng>( deviceMng, swapMngObj, draweMngObj, framebuff);
    auto& workMngObj    = *workMng.get();

    while( glfwGetKey(&window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(&window) )
    {
        glfwPollEvents();
        workMngObj.drawFrame();
    }

    vkDeviceWaitIdle(device);
}