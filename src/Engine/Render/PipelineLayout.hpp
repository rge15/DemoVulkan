#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <utilities/Timer/Timer.hpp>

class PipelineLayout
{
private:
    
    VkDevice& device_;

    VkPipelineLayoutCreateInfo layoutInfo_ {};

    VkPipelineLayout pipeLayout_ { VK_NULL_HANDLE };

    Vector<VkPushConstantRange> pushConstantsInfo_;

public:
    PipelineLayout( VkDevice& p_device );

    ~PipelineLayout();

    void
    sendPushConstantData() noexcept;

    void
    sendPushConstantData( 
        VkCommandBuffer& p_cmd, float p_relTime, const VkSwapchainCreateInfoKHR& p_swapInfo
    ) noexcept;

    inline
    VkPipelineLayout&
    getLayout(){ return pipeLayout_; };

private:

    void
    addPushConstantInfo();

    void
    initCreateInfo();

    void
    createLayout();

    template<typename T>
    uint32_t
    getPushConstantSize( const Vector<T>& p_data ) noexcept;

};