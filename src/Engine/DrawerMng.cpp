#include "DrawerMng.hpp"

DrawerMng::DrawerMng(Driver& p_driver, Renderer& p_render) noexcept
: driver_ { p_driver }, render_ { p_render }
{
    initCommander();
    initWorker();
    track_ = std::make_unique<DemoTrack>();
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

    uint32_t imgId = work_.get()->getFrameBufferIndex( swap );

    return imgId;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::recordCommand( uint32_t p_imageId, Vector<PlayingClip>& p_demos ) noexcept
{
    auto& cmd       = command_.get()->getCmdBuffer();
    auto& swapInfo  = driver_.getSwapchainManager().getSwapchainInfo();
    auto& layoutMng = render_.getPipeLayout();

    render_.initRenderPass( p_imageId, cmd );

    for(auto& demoClip : p_demos)
    {
        auto& demoFx            = std::get<DemoFX&>( demoClip );
        float relativeTime      = std::get<float>( demoClip );
        auto& renderPipelineMng = demoFx.getRenderPipelieneMng();

        renderPipelineMng.bindPipelineAndDynamics( cmd, swapInfo );

        layoutMng.sendPushConstantData( cmd, relativeTime, swapInfo );

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