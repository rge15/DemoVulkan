template<typename... Layouts>
Renderer<Layouts...>::Renderer(Driver& p_driver)
: driver_ { p_driver }
{
    auto& device    = driver_.getDeviceManager().getDevice();
    auto& swapMng   = driver_.getSwapchainManager();

    renderPass_ = std::make_unique<BasicRenderPass>( device, swapMng );
    auto& rndPass = renderPass_.get()->getRenderPass();
    framebuffer_ = std::make_unique<PipelineFrameBuffers>( device, rndPass, swapMng);

    initializeLayouts();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... Layouts>
void
Renderer<Layouts...>::initializeLayouts()
{
    auto& device    = driver_.getDeviceManager().getDevice();
    auto& swapMng   = driver_.getSwapchainManager();

    auto initLayout = [&] <typename T> ()
    {
        std::get<UniqPtr<T>>(renderLayoutTuple_) = std::make_unique<T>(device,swapMng);
    };

    (initLayout.template operator()<Layouts>(),...);
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... Layouts>
void
Renderer<Layouts...>::initRenderPass( uint32_t p_imageId, VkCommandBuffer& p_cmd ) noexcept
{
    auto& vkRenderPass  = renderPass_.get()->getRenderPass();
    auto& frameBuffer   = framebuffer_.get()->getFramebufferByIndex( p_imageId );

    auto& swapInfo = driver_.getSwapchainManager().getSwapchainInfo();

    VkRenderPassBeginInfo _beginInfo {};

    _beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    _beginInfo.pNext = nullptr;
    
    _beginInfo.renderPass = vkRenderPass;
    _beginInfo.framebuffer = frameBuffer;

    _beginInfo.renderArea.offset = { 0, 0 };
    _beginInfo.renderArea.extent = swapInfo.imageExtent;

    _beginInfo.clearValueCount = 1;
    VkClearValue blackColor {0.f,0.f,0.f,1.f};
    _beginInfo.pClearValues = &blackColor;

    vkCmdBeginRenderPass( p_cmd, &_beginInfo, VK_SUBPASS_CONTENTS_INLINE );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... Layouts>
template<typename T>
T&
Renderer<Layouts...>::getPipeLayoutMng()
{
    return *std::get<UniqPtr<T>>(renderLayoutTuple_).get();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... Layouts>
VkPipelineLayout&
Renderer<Layouts...>::getLayout( LayoutTypes p_type )
{
    if(p_type == LayoutTypes::BasicLayout)
    {
        auto& layoutMng = getPipeLayoutMng<BasicPipelineLayout>();
        return layoutMng.getLayout();
    }else
    {
        printf("There's no valid Layout of that type");
        assert(false);
    }
}
