#pragma once
#include "utilities/graphicInclude.hpp"
#include "utilities/typeAliases.hpp"
#include <Engine/utilStructs/SwapchainDetails.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

class SwapchainMng
{
private:
    VkSwapchainKHR _swapchain { VK_NULL_HANDLE };

    VkDevice& _device;
    VkSurfaceKHR& _surface;
    const SwapchainDetails& _swapDetails;
    const DeviceQueueFamilies& _queueIds;
    Vector<uint32_t> _queueFamilies;

    VkSwapchainCreateInfoKHR _createInfo{};

    Vector<VkImage> _swapImages;
    Vector<VkImageView> _viewImages;

public:
    SwapchainMng(VkDevice& p_device, VkSurfaceKHR& p_surface, const SwapchainDetails& p_details, const DeviceQueueFamilies& p_queueIds );
    ~SwapchainMng();

    inline
    const VkSwapchainCreateInfoKHR&
    getSwapchainInfo() const { return _createInfo; };

    inline
    const Vector<VkImageView>&
    getSwapchainImageViews() const { return _viewImages; };

    inline
    VkSwapchainKHR&
    getSwapchain() { return _swapchain; };

private:
    void
    initCreateInfo();
    
    void
    createSwapchain();

    void
    selectImageCount();

    void
    selectColorAndFormat();

    void
    selectQueueFamiliesImages();

    void
    selectPresentMode();

    void
    getSwapchainImages();

    void
    getImageViews();

};