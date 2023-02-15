#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class PipelineLayout
{
private:
    
    VkDevice& _device;

    VkPipelineLayoutCreateInfo _layoutInfo {};

    VkPipelineLayout _pipeLayout { VK_NULL_HANDLE };

    Vector<VkPushConstantRange> _pushConstantsInfo;

public:
    PipelineLayout( VkDevice& p_device );

    ~PipelineLayout();

    inline
    VkPipelineLayout&
    getLayout(){ return _pipeLayout; };

private:

    void
    addPushConstants();

    void
    initCreateInfo();

    void
    createLayout();

};