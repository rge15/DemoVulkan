#pragma once
#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/SwapchainMng.hpp>

class RenderPass
{
private:
    VkDevice& _device;
    const SwapchainMng& _swapMng;

    VkAttachmentDescription _attachmentDesc {};

    VkAttachmentReference   _attachmentReference {};
    VkSubpassDescription    _subpassDesc {};
    
    VkRenderPassCreateInfo  _renderPassInfo {};

    VkRenderPass _renderPass { VK_NULL_HANDLE }; 

public:
    RenderPass( VkDevice& p_device, const SwapchainMng& p_swapMng );
    ~RenderPass();

    inline
    VkRenderPass&
    getRenderPass(){ return _renderPass; };

private:

    void
    initInfo() noexcept;

    void
    createRenderPass() noexcept;

    void
    initAttachmentInfo() noexcept;

    void
    initSubpassInfo() noexcept;

};