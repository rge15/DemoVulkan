#include "PipelineLayout.hpp"

PipelineLayout::PipelineLayout( VkDevice& p_device )
: device_ { p_device }
{
    addPushConstantInfo();
    initCreateInfo();
    createLayout();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

PipelineLayout::~PipelineLayout()
{
    vkDestroyPipelineLayout( device_, pipeLayout_, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::initCreateInfo()
{
    layoutInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    layoutInfo_.pNext = nullptr;
    layoutInfo_.flags = 0;
    layoutInfo_.setLayoutCount = 0;
    layoutInfo_.pSetLayouts = nullptr;
    layoutInfo_.pushConstantRangeCount = pushConstantsInfo_.size();
    layoutInfo_.pPushConstantRanges = pushConstantsInfo_.data();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::createLayout()
{
    auto result = vkCreatePipelineLayout( device_, &layoutInfo_, nullptr, &pipeLayout_);

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::addPushConstantInfo()
{
    auto& resolutionCnst        = pushConstantsInfo_.emplace_back();
    resolutionCnst.stageFlags   = VK_SHADER_STAGE_FRAGMENT_BIT;
    resolutionCnst.offset       = 0;
    resolutionCnst.size         = sizeof( float ) * 4;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::sendPushConstantData( 
    VkCommandBuffer& p_cmd, float p_relTime, const VkSwapchainCreateInfoKHR& p_swapInfo
) noexcept
{
    auto width      = (float)p_swapInfo.imageExtent.width;
    auto heigth     = (float)p_swapInfo.imageExtent.height;
    auto absTime    = (float)Timer::getInstance().ellapsedSeconds();
    auto relTime    = p_relTime;

    Vector<float> pushCnstData { width, heigth, absTime, relTime };

    uint32_t finalSize = getPushConstantSize(pushCnstData);

    vkCmdPushConstants(
        p_cmd, pipeLayout_ , VK_SHADER_STAGE_FRAGMENT_BIT,
        0, finalSize, pushCnstData.data() 
    );

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
uint32_t
PipelineLayout::getPushConstantSize( const Vector<T>& p_data ) noexcept
{
    auto dataSize   = p_data.size() * sizeof(p_data.data()[0]) ;
    auto multiple4  = (int)std::log2( dataSize );
    
    uint32_t perfectSize = pow(2,multiple4);
    uint32_t difference  = dataSize % perfectSize ;

    uint32_t finalSize = (difference == 0) ? perfectSize : pow(2,multiple4+1);

    return finalSize;
}