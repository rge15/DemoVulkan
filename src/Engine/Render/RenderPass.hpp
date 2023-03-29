#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/Driver/SwapchainMng.hpp>

class RenderPass
{
private:
    VkDevice& device_;
    const SwapchainMng& swapMng_;

    VkAttachmentDescription attachmentDesc_ {};

    VkAttachmentReference   attachmentReference_ {};
    VkSubpassDescription    subpassDesc_ {};
    
    VkRenderPassCreateInfo  renderPassInfo_ {};

    VkRenderPass renderPass_ { VK_NULL_HANDLE }; 

public:
    RenderPass( VkDevice& p_device, const SwapchainMng& p_swapMng );
    ~RenderPass();

    inline
    VkRenderPass&
    getRenderPass(){ return renderPass_; };

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