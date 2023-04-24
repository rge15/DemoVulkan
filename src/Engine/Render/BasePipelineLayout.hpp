#pragma once
#include "BaseRenderRSC.hpp"
#include <Engine/Driver/SwapchainMng.hpp>

class BasePipelineLayout : public BaseRenderRSC
{
protected:
    VkDevice& device_;
    const SwapchainMng& swapMng_;

    VkPipelineLayoutCreateInfo createInfo_ {};
    VkPipelineLayout pipeLayout_ { VK_NULL_HANDLE };

    BasePipelineLayout( VkDevice& p_device, const SwapchainMng& p_swapMng ) noexcept;

    void
    initBaseCreateInfo() noexcept;

    virtual
    void bindLayoutCmdData( VkCommandBuffer& p_cmd, float p_relTime ) = 0;

public:

    ~BasePipelineLayout();

    inline
    VkPipelineLayout&
    getLayout(){ return pipeLayout_; };

    void
    createPipelineLayout() noexcept;

};