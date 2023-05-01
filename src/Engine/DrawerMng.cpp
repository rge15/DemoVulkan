#include "DrawerMng.hpp"

DrawerMng::DrawerMng( Driver& p_driver, RendererType& p_renderer ) noexcept
: driver_ { p_driver }, renderer_ { p_renderer }
{
    initCommander();
    initWorker();
    //Todo : esto en la inicialización por defecto 
    track_ = std::make_unique<DemoTrack>();



    //TODO : Single Time begin/record pipeline barrier for p_renderer.getLayoutMng<ImageLayout>();
    //TODO : and submit that cmd
    auto& imgLayout = renderer_.getPipeLayoutMng<ImagePipelineLayout>(); 
    
    command_.get()->beginRecording();

    auto& cmd = command_.get()->getCmdBuffer();

    imgLayout.setPipelineImageBarrier( cmd );

    command_.get()->endRecording();

    auto& deviceMng = driver_.getDeviceManager();
    auto& graphicQueueHandler = deviceMng.getGraphicQueueHandler();

    command_.get()->submitSingle(graphicQueueHandler);

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void 
DrawerMng::initCommander()
{
    auto& deviceMng     = driver_.getDeviceManager(); 
    auto& device        = deviceMng.getDevice();
    auto& queueFamily   = deviceMng.getFamilyQueueIds();

    command_ = std::make_unique<CommandMng>( device, queueFamily );

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void 
DrawerMng::initWorker()
{
    auto& deviceMng     = driver_.getDeviceManager(); 
    auto& device        = deviceMng.getDevice();

    work_ = std::make_unique<WorkMng>( device );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::drawFrame() noexcept
{
    uint32_t frameId = getReadyToRecord();
    
    command_.get()->beginRecording();

    auto playingDemos = track_.get()->getPlayingFXs();
    
    recordCommand( frameId, playingDemos );

    command_.get()->endRecording();

    //SubmitCmd
    submitCommands(frameId);

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

uint32_t
DrawerMng::getReadyToRecord() noexcept
{
    //Get FrameBuffer Id
    uint32_t frameId = getFrameBufferId();

    //Sync Cmnd
    work_.get()->waitBufferSync();

    return frameId;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

uint32_t
DrawerMng::getFrameBufferId() noexcept
{
    auto& swap = driver_.getSwapchainManager().getSwapchain();

    uint32_t imgId = work_.get()->getImageBufferIndex( swap );

    return imgId;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::recordCommand( uint32_t p_imageId, Vector<PlayingClip>& p_demos ) noexcept
{
    if( p_demos.empty() )
        return;
    
    auto& cmd       = command_.get()->getCmdBuffer();
    auto& swapInfo  = driver_.getSwapchainManager().getSwapchainInfo();
    
    renderer_.initRenderPass( p_imageId, cmd );

    for(auto& demoClip : p_demos)
    {
        auto& demoFx            = std::get<DemoFX&>( demoClip );
        float relativeTime      = std::get<float>( demoClip );
        auto& renderPipelineMng = demoFx.getRenderPipelieneMng();
        auto layoutType         = demoFx.getLayoutId();

        renderPipelineMng.bindPipelineAndDynamics( cmd, swapInfo );

        bindLayoutData( cmd, layoutType, relativeTime );

        vkCmdDraw( cmd, 6, 1, 0, 0);
    }

    vkCmdEndRenderPass( cmd );

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::submitCommands( uint32_t p_imageId ) noexcept
{
    auto& swapchain = driver_.getSwapchainManager().getSwapchain();
    auto& deviceMng = driver_.getDeviceManager();
    auto& workMng   = *work_.get();

    VkPipelineStageFlags    stageFlags { VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT };
    VkSubmitInfo            _subInfo {};

    _subInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    _subInfo.pNext = nullptr;
    _subInfo.waitSemaphoreCount = 1;
    _subInfo.pWaitSemaphores    = &workMng.getImgAvailableSemaphore();
    _subInfo.pWaitDstStageMask  = &stageFlags;
    _subInfo.commandBufferCount = 1;
    
    _subInfo.pCommandBuffers        = &command_.get()->getCmdBuffer();
    _subInfo.signalSemaphoreCount   = 1;
    _subInfo.pSignalSemaphores      = &workMng.getImgRenderedSemaphore();

    auto graphicQueueHandler = deviceMng.getGraphicQueueHandler();
    vkQueueSubmit( graphicQueueHandler, 1, &_subInfo, workMng.getCmdAvailableFence() );

    VkPresentInfoKHR presentInfo {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = nullptr;

    presentInfo.waitSemaphoreCount  = 1;
    presentInfo.pWaitSemaphores     = &workMng.getImgRenderedSemaphore();

    presentInfo.swapchainCount  = 1;
    presentInfo.pSwapchains     = &swapchain;
    presentInfo.pImageIndices   = &p_imageId;
    presentInfo.pResults = nullptr;

    vkQueuePresentKHR( deviceMng.getPresentQueueHandler(), &presentInfo );

}


void
DrawerMng::bindLayoutData( VkCommandBuffer& p_cmd, LayoutTypes p_type, float p_relativeTime )
{
    //TODO : Poner aquí el resto de valores del IF
    if(p_type == LayoutTypes::BasicLayout )
    {
        auto& layout = renderer_.getPipeLayoutMng<BasicPipelineLayout>();
        layout.bindLayoutCmdData(p_cmd, p_relativeTime);
        return;
    }else if( p_type == LayoutTypes::ImageLayout )
    {
        auto& layout = renderer_.getPipeLayoutMng<ImagePipelineLayout>();
        layout.bindLayoutCmdData(p_cmd, p_relativeTime);
        return;
    }else{
        printf("There's no available layoutMng of that kind");
        assert(false);
    }
}