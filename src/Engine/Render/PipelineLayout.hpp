#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

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

    inline
    VkPipelineLayout&
    getLayout(){ return pipeLayout_; };

private:

    void
    addPushConstants();

    void
    initCreateInfo();

    void
    createLayout();

};