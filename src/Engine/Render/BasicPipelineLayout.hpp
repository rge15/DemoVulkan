#pragma once
#include "BasePipelineLayout.hpp"
#include <utilities/Timer/Timer.hpp>

class BasicPipelineLayout : public BasePipelineLayout
{
private:
    Vector<VkPushConstantRange> pushConstantsInfo_;

public:
    BasicPipelineLayout( VkDevice& p_device, const SwapchainMng& p_swapMng );

    ~BasicPipelineLayout() = default;

    void
    sendPushConstantData( 
        VkCommandBuffer& p_cmd, float p_relTime
    ) noexcept;

    void
    bindLayoutCmdData( VkCommandBuffer& p_cmd, float p_relTime ) override final;

private:

    void
    addPushConstantInfo();

    void
    initCreateInfo();

    template<typename T>
    uint32_t
    getPushConstantSize( const Vector<T>& p_data ) noexcept;

};