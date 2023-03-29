#include "SwapchainMng.hpp"

SwapchainMng::SwapchainMng(VkDevice& p_device, VkSurfaceKHR& p_surface, const SwapchainDetails& p_details, const DeviceQueueFamilies& p_queueIds )
: device_ { p_device }, surface_ { p_surface }, swapDetails_ { p_details }, queueIds_ { p_queueIds }
{
    queueFamilies_.push_back( queueIds_._graphicQueueId.value() );
    queueFamilies_.push_back( queueIds_._presentQueueId.value() );
    initCreateInfo();
    createSwapchain();
    getSwapchainImages();
    getImageViews();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

SwapchainMng::~SwapchainMng()
{
    for(size_t i = 0 ; i < viewImages_.size(); i++)
    {
        vkDestroyImageView( device_, viewImages_[i], nullptr );
    }

    vkDestroySwapchainKHR( device_, swapchain_, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
SwapchainMng::initCreateInfo()
{
    createInfo_.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo_.pNext = nullptr;
    createInfo_.flags = 0;
    createInfo_.surface = surface_;

    selectImageCount();
    selectColorAndFormat();

    createInfo_.imageExtent = swapDetails_.capabilities.currentExtent;

    createInfo_.imageArrayLayers = 1;
    createInfo_.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    selectQueueFamiliesImages();

    createInfo_.preTransform = swapDetails_.capabilities.currentTransform;
    createInfo_.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    selectPresentMode();

    createInfo_.clipped = VK_TRUE;
    createInfo_.oldSwapchain = VK_NULL_HANDLE;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
SwapchainMng::createSwapchain()
{
    auto result = vkCreateSwapchainKHR( device_, &createInfo_, nullptr, &swapchain_ );

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
SwapchainMng::selectImageCount()
{
    uint32_t imageCount {0};

    imageCount = swapDetails_.capabilities.minImageCount + 1;
    
    if(imageCount > swapDetails_.capabilities.maxImageCount)
        imageCount = swapDetails_.capabilities.maxImageCount;
    
    createInfo_.minImageCount = imageCount;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
SwapchainMng::selectColorAndFormat()
{
    for(auto& format : swapDetails_.formats)
    {
        if( format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
        {
            createInfo_.imageFormat = format.format;
            createInfo_.imageColorSpace = format.colorSpace;
            return;
        }
    }
    createInfo_.imageFormat = swapDetails_.formats[0].format;
    createInfo_.imageColorSpace = swapDetails_.formats[0].colorSpace;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
SwapchainMng::selectQueueFamiliesImages()
{
    if( queueIds_._graphicQueueId == queueIds_._presentQueueId )
    {
        createInfo_.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo_.queueFamilyIndexCount = 0;
        createInfo_.pQueueFamilyIndices = nullptr;
    }else{
        createInfo_.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo_.queueFamilyIndexCount = (uint32_t)queueFamilies_.size();
        createInfo_.pQueueFamilyIndices =queueFamilies_.data();
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
SwapchainMng::selectPresentMode()
{
    for(auto& presentMode : swapDetails_.presentModes )
    {
        if(presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            createInfo_.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
            return;
        }
    }
    createInfo_.presentMode = swapDetails_.presentModes[0];
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
SwapchainMng::getSwapchainImages()
{
    uint32_t imageCount { 0 };
    vkGetSwapchainImagesKHR( device_, swapchain_, &imageCount, nullptr );
    swapImages_.resize(imageCount);
    viewImages_.resize(imageCount);
    vkGetSwapchainImagesKHR( device_, swapchain_, &imageCount, &swapImages_[0] );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
SwapchainMng::getImageViews()
{
    VkImageViewCreateInfo imageViewCreateInfo{};

    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.pNext = nullptr;
    imageViewCreateInfo.flags = 0;

    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    imageViewCreateInfo.format = createInfo_.imageFormat;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;

    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.layerCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;

    for(size_t i = 0; i < swapImages_.size() ; i++ )
    {
        imageViewCreateInfo.image = swapImages_[i];

        auto result = vkCreateImageView( device_, &imageViewCreateInfo, nullptr, &viewImages_[i] );

        assert(result == VK_SUCCESS);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------