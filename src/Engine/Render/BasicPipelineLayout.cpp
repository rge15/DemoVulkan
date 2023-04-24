#include "BasicPipelineLayout.hpp"

BasicPipelineLayout::BasicPipelineLayout( VkDevice& p_device, const SwapchainMng& p_swapMng )
: BasePipelineLayout { p_device, p_swapMng }
{
    addPushConstantInfo();
    initCreateInfo();
    createPipelineLayout();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
BasicPipelineLayout::initCreateInfo()
{
    createInfo_.pushConstantRangeCount = pushConstantsInfo_.size();
    createInfo_.pPushConstantRanges = pushConstantsInfo_.data();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
BasicPipelineLayout::addPushConstantInfo()
{
    auto& resolutionCnst        = pushConstantsInfo_.emplace_back();
    resolutionCnst.stageFlags   = VK_SHADER_STAGE_FRAGMENT_BIT;
    resolutionCnst.offset       = 0;
    resolutionCnst.size         = sizeof( float ) * 4;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
BasicPipelineLayout::bindLayoutCmdData( VkCommandBuffer& p_cmd, float p_relTime )
{
    sendPushConstantData( p_cmd, p_relTime );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//TODO : Ver esto de meterlo de alguna forma en el baseLayout
void
BasicPipelineLayout::sendPushConstantData(
    VkCommandBuffer& p_cmd, float p_relTime
) noexcept
{
    auto& swap      = swapMng_.getSwapchainInfo();
    auto width      = (float)swap.imageExtent.width;
    auto heigth     = (float)swap.imageExtent.height;
    auto absTime    = (float)Timer::getInstance().ellapsedSeconds();
    auto relTime    = (float)p_relTime;

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
BasicPipelineLayout::getPushConstantSize( const Vector<T>& p_data ) noexcept
{
    auto dataSize   = p_data.size() * sizeof(p_data.data()[0]);
    auto multiple4  = (int)std::log2( dataSize );

    uint32_t perfectSize = pow(2,multiple4);
    uint32_t difference  = dataSize % perfectSize;

    uint32_t finalSize = (difference == 0) ? perfectSize : pow(2,multiple4+1);

    return finalSize;
}