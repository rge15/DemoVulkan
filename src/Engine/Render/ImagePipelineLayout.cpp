#include "ImagePipelineLayout.hpp"


ImagePipelineLayout::ImagePipelineLayout(VkDevice& p_device, const SwapchainMng& p_swapMng)
: BasePipelineLayout { p_device, p_swapMng }
{
    setImageConfiguration();
    setDescriptorSetConfiguration();

    addPushConstantInfo();
    initCreateInfo();
    createPipelineLayout();

    /////TODO : Allocate and prepare descriptor Set
    createDescriptorSetMemory();
    
    /////TODO : Update Desc Set value 
    updateDescSetValue();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

ImagePipelineLayout::~ImagePipelineLayout()
{
    if(imageView_ != VK_NULL_HANDLE )
        vkDestroyImageView( device_, imageView_, nullptr );

    if(image_ != VK_NULL_HANDLE)
        vkDestroyImage( device_, image_, nullptr );

    if(memory_ != VK_NULL_HANDLE)
        vkFreeMemory( device_, memory_, nullptr );

    if(descPool_ != VK_NULL_HANDLE)
        vkDestroyDescriptorPool( device_, descPool_, nullptr );

    if( descSetLayout_ != VK_NULL_HANDLE )
        vkDestroyDescriptorSetLayout( device_, descSetLayout_, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::setImageConfiguration() noexcept
{
    createImage();
    allocateImageMemory();
    bindImageMemory();
    createImageView();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::bindImageMemory() noexcept
{
    auto vkResult = vkBindImageMemory( device_, image_, memory_, 0 );
    assert(vkResult == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::allocateImageMemory() noexcept
{
    VkMemoryRequirements imgReq {};
    vkGetImageMemoryRequirements( device_, image_, &imgReq );

    uint32_t validMemoIndex = 0;
    for(int i = 0; i < 32 ; i++)
        if(  imgReq.memoryTypeBits & (1 << i) )
        {
            validMemoIndex = i;
            break;
        }

    VkMemoryAllocateInfo info {};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    info.pNext = nullptr;
    info.allocationSize = imgReq.size;
    info.memoryTypeIndex = validMemoIndex;

    auto vkResult = vkAllocateMemory( device_, &info, nullptr, &memory_ );
    assert(vkResult == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::createImage() noexcept
{
    VkImageCreateInfo   imgInfo {};
    VkExtent3D          imgExt  {};

    imgExt.depth    = 1;
    imgExt.height   = swapMng_.getSwapchainInfo().imageExtent.height;
    imgExt.width    = swapMng_.getSwapchainInfo().imageExtent.width;

    imgInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imgInfo.pNext = nullptr;
    imgInfo.flags = 0;
    imgInfo.imageType = VK_IMAGE_TYPE_2D;
    //TODO : Alomejor no es el formato correcto
    imgInfo.format = VK_FORMAT_R16_SFLOAT;
    imgInfo.extent = imgExt;
    imgInfo.mipLevels   = 1;
    imgInfo.arrayLayers = 1;
    imgInfo.samples     = VK_SAMPLE_COUNT_1_BIT;
    imgInfo.tiling      = VK_IMAGE_TILING_OPTIMAL;
    imgInfo.usage       = VK_IMAGE_USAGE_STORAGE_BIT;
    imgInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imgInfo.queueFamilyIndexCount = 0;
    imgInfo.pQueueFamilyIndices = nullptr;
    imgInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    auto vkResult = vkCreateImage( device_, &imgInfo, nullptr, &image_ ); 
    assert(vkResult == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::createImageView() noexcept
{
    VkImageViewCreateInfo info {};

    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;
    info.image = image_;
    info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    //TODO : Alomejor no es el formato correcto
    info.format = VK_FORMAT_R16_SFLOAT;
    info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    info.subresourceRange.baseArrayLayer = 0;
    info.subresourceRange.levelCount = 1;
    info.subresourceRange.baseMipLevel = 0;
    info.subresourceRange.layerCount = 1;

    auto vkResult = vkCreateImageView( device_, &info, nullptr, &imageView_ );
    assert(vkResult == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::updateDescSetValue() noexcept
{
    VkDescriptorImageInfo imageInfo {};

    imageInfo.imageView     = imageView_;
    imageInfo.imageLayout   = VK_IMAGE_LAYOUT_GENERAL;
    imageInfo.sampler       = VK_NULL_HANDLE;

    VkWriteDescriptorSet writeInfo {};

    writeInfo.sType     = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeInfo.pNext     = nullptr;
    writeInfo.dstSet    = descSet_;
    writeInfo.dstBinding    = 0;
    writeInfo.dstArrayElement   = 0;
    writeInfo.descriptorCount   = 1;
    writeInfo.descriptorType    = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    writeInfo.pImageInfo        = &imageInfo;
    writeInfo.pBufferInfo       = nullptr;
    writeInfo.pTexelBufferView  = nullptr;

    vkUpdateDescriptorSets( device_, 1, &writeInfo, 0, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::createDescriptorSetMemory() noexcept
{
    createDescriptorPool();
    allocateDescriptorSet();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::createDescriptorPool() noexcept
{
    VkDescriptorPoolSize poolSize {};

    poolSize.descriptorCount = 1;
    poolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;

    VkDescriptorPoolCreateInfo info {};

    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;
    info.maxSets = 1;
    info.poolSizeCount = 1;
    info.pPoolSizes = &poolSize;
    
    auto vkResult = vkCreateDescriptorPool( device_, &info, nullptr, &descPool_ );
    assert(vkResult == VK_SUCCESS);
    printf(" Descriptor Pool created succesfully ");

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::allocateDescriptorSet() noexcept
{
    VkDescriptorSetAllocateInfo info {};

    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    info.pNext = nullptr;
    info.descriptorPool = descPool_;
    info.descriptorSetCount = 1;
    info.pSetLayouts = &descSetLayout_;

    auto vkResult = vkAllocateDescriptorSets( device_, &info, &descSet_ );
    assert(vkResult == VK_SUCCESS);
    printf(" Descriptor Set allocated succesfully ");

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::setDescriptorSetConfiguration() noexcept
{
    VkDescriptorSetLayoutBinding layBindingInfo {};

    layBindingInfo.binding = 0;
    layBindingInfo.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    layBindingInfo.descriptorCount = 1;
    layBindingInfo.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    layBindingInfo.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo info {};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;
    info.bindingCount = 1;
    info.pBindings = &layBindingInfo;

    auto vkResult = vkCreateDescriptorSetLayout( device_, &info, nullptr, &descSetLayout_ );
    assert(vkResult == VK_SUCCESS);
    printf("Descriptor Layout created succesfully\n");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::initCreateInfo() noexcept
{
    createInfo_.pushConstantRangeCount = pushConstantsInfo_.size();
    createInfo_.pPushConstantRanges = pushConstantsInfo_.data();

    createInfo_.setLayoutCount = 1;
    createInfo_.pSetLayouts = &descSetLayout_;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::addPushConstantInfo() noexcept
{
    auto& resolutionCnst        = pushConstantsInfo_.emplace_back();
    resolutionCnst.stageFlags   = VK_SHADER_STAGE_FRAGMENT_BIT;
    resolutionCnst.offset       = 0;
    resolutionCnst.size         = sizeof( float ) * 4;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::bindLayoutCmdData( VkCommandBuffer& p_cmd, float p_relTime )
{
    //setPipelineImageBarrier( p_cmd );
    sendPushConstantData( p_cmd, p_relTime );
    bindDescriptorSetImages( p_cmd );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::setPipelineImageBarrier( VkCommandBuffer& p_cmd )
{
    VkImageMemoryBarrier imgBarrier {};

    imgBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imgBarrier.pNext = nullptr;
    imgBarrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
    imgBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    imgBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imgBarrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    imgBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imgBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imgBarrier.image = image_;
    imgBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imgBarrier.subresourceRange.baseMipLevel = 0;
    imgBarrier.subresourceRange.levelCount = 1;
    imgBarrier.subresourceRange.baseArrayLayer = 0;
    imgBarrier.subresourceRange.layerCount = 1;

    vkCmdPipelineBarrier(
        p_cmd, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
        0, 0, nullptr, 0, nullptr, 1, &imgBarrier 
    );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::bindDescriptorSetImages( VkCommandBuffer& p_cmd )
{
    vkCmdBindDescriptorSets(
        p_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, getLayout(),
        0, 1, &descSet_, 0, nullptr
    );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
ImagePipelineLayout::sendPushConstantData(
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
ImagePipelineLayout::getPushConstantSize( const Vector<T>& p_data ) noexcept
{
    auto dataSize   = p_data.size() * sizeof(p_data.data()[0]);
    auto multiple4  = (int)std::log2( dataSize );

    uint32_t perfectSize = pow(2,multiple4);
    uint32_t difference  = dataSize % perfectSize;

    uint32_t finalSize = (difference == 0) ? perfectSize : pow(2,multiple4+1);

    return finalSize;
}