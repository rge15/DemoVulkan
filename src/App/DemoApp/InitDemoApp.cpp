#include "InitDemoApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeviceMng.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"
#include "Engine/SwapchainMng.hpp"
#include "Engine/Sources/ShaderSrc.hpp"
#include "Engine/PipelineStructs/GraphicPipelineConfig.hpp"
#include "Engine/PipelineStructs/PipelineLayout.hpp"
#include "Engine/PipelineStructs/RenderPass.hpp"
#include "Engine/RenderPipelineMng.hpp"
#include "Engine/PipelineStructs/PipelineFrameBuffers.hpp"
#include "Engine/DrawerMng.hpp"
#include "Engine/Renderer.hpp"

void
InitDemoApp::run()
{
    auto windowMng   = std::make_unique<WindowMng>();
    auto instanceMng = std::make_unique<InstanceMng>();
    
    auto  instance   = instanceMng.get()->_vkInstance;
    auto& window     = windowMng.get()->getWindow();

    auto surfaceMng  = std::make_unique<SurfaceMng>( instance, window );
    auto surface     = surfaceMng.get()->getSurface();

    auto deviceMng   = std::make_unique<DeviceMng>( instance, surface);

    auto device      = deviceMng.get()->getDevice();
    auto swapDetails = deviceMng.get()->getSwapchainDetails();
    auto queueIds    = deviceMng.get()->getFamilyQueueIds();

    auto  swapMng    = std::make_unique<SwapchainMng>( device, surface, swapDetails, queueIds );
    auto& swapMngObj = *swapMng.get();
    auto  swapInfo   = swapMngObj.getSwapchainInfo(); 

    auto vertShaderSrc = std::make_unique<ShaderSrc>(device, "src/shaders/vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
    auto fragShaderSrc = std::make_unique<ShaderSrc>(device, "src/shaders/frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);
    
    auto vertexShaderStageInfo   = vertShaderSrc.get()->getShaderStageInfo();
    auto fragmentShaderStageInfo = fragShaderSrc.get()->getShaderStageInfo();
    using ShaderStagesVector     = Vector<VkPipelineShaderStageCreateInfo>;
    ShaderStagesVector shaders { vertexShaderStageInfo, fragmentShaderStageInfo };

    auto pipeConfig = GraphicPipelineConfig();
    
    auto pipeLayout = std::make_unique<PipelineLayout>( device );
    auto layoutObj  = pipeLayout.get()->getLayout();

    auto renderPass     = std::make_unique<RenderPass>( device, swapMngObj );
    auto renderPassObj  = renderPass.get()->getRenderPass();

    auto  renderPipelineMng  = std::make_unique<RenderPipelineMng>( device, renderPassObj, layoutObj, pipeConfig, shaders );
    auto& pipeline           = renderPipelineMng.get()->_pipeline;

    auto frameBuffers = std::make_unique<PipelineFrameBuffers>( device, renderPassObj, swapMngObj);

    auto drawerMng = std::make_unique<DrawerMng>( device, queueIds, renderPassObj, pipeline, layoutObj,swapInfo );

    auto& deviceMngObj      = *deviceMng.get();
    auto& draweMngObj       = *drawerMng.get();
    auto& framebufferMngObj = *frameBuffers.get();

    auto renderer       = std::make_unique<Renderer>( deviceMngObj, swapMngObj, draweMngObj, framebufferMngObj);
    auto& rendererObj    = *renderer.get();

    while( glfwGetKey(&window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(&window) )
    {
        glfwPollEvents();
        rendererObj.drawFrame();
    }

    vkDeviceWaitIdle(device);
}