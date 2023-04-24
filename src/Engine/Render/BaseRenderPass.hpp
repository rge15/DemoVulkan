#pragma once
#include "BaseRenderRSC.hpp"
#include <Engine/Driver/SwapchainMng.hpp>

class BaseRenderPass : public BaseRenderRSC
{
protected:
    VkDevice& device_;
    const SwapchainMng& swapMng_;
    
    VkAttachmentDescription attachmentDesc_ {};
    VkAttachmentReference   attachmentReference_ {};
    VkSubpassDescription    subpassDesc_ {};
    VkRenderPassCreateInfo  createInfo_ {};

    VkRenderPass renderPass_ { VK_NULL_HANDLE };

    BaseRenderPass( VkDevice& p_device, const SwapchainMng& p_swapMng ) noexcept;

    void
    createRenderPass() noexcept;

    void
    initBaseCreateInfo() noexcept;

    void
    initBaseAttachementInfo() noexcept;

    void
    initBaseSupbassInfo() noexcept;

public:

    ~BaseRenderPass();

    inline
    VkRenderPass&
    getRenderPass(){ return renderPass_; };

};