#include "InitDemoApp.hpp"
#include <Engine/Driver.hpp>
#include <Engine/Renderer.hpp>

#include <Engine/Sources/ShaderSrc.hpp>
#include <Engine/RenderPipelineMng.hpp>
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
    

    // RenderMng DATA Start    
    /**

    auto pipeLayout = std::make_unique<PipelineLayout>( device );
    auto layoutObj  = pipeLayout.get()->getLayout();

    auto renderPass     = std::make_unique<RenderPass>( device, swapMngObj );
    auto renderPassObj  = renderPass.get()->getRenderPass();
    
    auto frameBuffers = std::make_unique<PipelineFrameBuffers>( device, renderPassObj, swapMngObj);
    */
    // RenderMng DATA End

    auto renderer = std::make_unique<Renderer>( *driver.get() );

    auto& renderPass = renderer.get()->getRenderPass().getRenderPass();
    auto& pipeLayout = renderer.get()->getPipeLayout().getLayout();
    auto& framebuff  = renderer.get()->getFramebuffer();

    // DemoFX DATA Start
    auto pipeConfig = GraphicPipelineConfig();

    auto vertShaderSrc = std::make_unique<ShaderSrc>(device, "src/shaders/vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
    auto fragShaderSrc = std::make_unique<ShaderSrc>(device, "src/shaders/frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);

    auto vertexShaderStageInfo   = vertShaderSrc.get()->getShaderStageInfo();
    auto fragmentShaderStageInfo = fragShaderSrc.get()->getShaderStageInfo();
    using ShaderStagesVector     = Vector<VkPipelineShaderStageCreateInfo>;
    ShaderStagesVector shaders { vertexShaderStageInfo, fragmentShaderStageInfo };

    auto  renderPipelineMng  = std::make_unique<RenderPipelineMng>( device, renderPass, pipeLayout, pipeConfig, shaders );
    auto& pipeline           = renderPipelineMng.get()->pipeline_;
    // DemoFX DATA End
    

    auto drawerMng = std::make_unique<DrawerMng>( device, queueIds, renderPass, pipeline, pipeLayout,swapInfo );
    //TODO : El drawer no tendrá una pipeline a piñon.

    //TODO : Hacer una clase Track que contenga los DemoFX que tenga que ejecutar con su tiempo de entrada y tiempo de visión
    //TODO : tmbn tendrá un clock para cronometrar el tiempo total y el tiempo relativo de cada FX para poder pasar los valores como push constant

    //TODO : Hacer clase DemoFX que contenga los shaders que deba mostrar por pantalla, una renderpipeline con esos shaders y un método que grabe ese efecto

    auto& draweMngObj       = *drawerMng.get();

    auto workMng       = std::make_unique<WorkMng>( deviceMng, swapMngObj, draweMngObj, framebuff);
    auto& workMngObj    = *workMng.get();

    while( glfwGetKey(&window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(&window) )
    {
        glfwPollEvents();
        workMngObj.drawFrame();
    }

    vkDeviceWaitIdle(device);
}