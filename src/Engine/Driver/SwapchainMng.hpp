#pragma once
#include "utilities/typeAliases.hpp"
#include <Engine/utilStructs/SwapchainDetails.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

class SwapchainMng
{
private:
    VkSwapchainKHR swapchain_ { VK_NULL_HANDLE };

    VkDevice& device_;
    VkSurfaceKHR& surface_;
    const SwapchainDetails& swapDetails_;
    const DeviceQueueFamilies& queueIds_;
    Vector<uint32_t> queueFamilies_;

    VkSwapchainCreateInfoKHR createInfo_{};

    Vector<VkImage> swapImages_;
    Vector<VkImageView> viewImages_;

public:
    SwapchainMng(VkDevice& p_device, VkSurfaceKHR& p_surface, const SwapchainDetails& p_details, const DeviceQueueFamilies& p_queueIds );
    ~SwapchainMng();

    inline
    const VkSwapchainCreateInfoKHR&
    getSwapchainInfo() const { return createInfo_; };

    inline
    const Vector<VkImageView>&
    getSwapchainImageViews() const { return viewImages_; };

    inline
    VkSwapchainKHR&
    getSwapchain() { return swapchain_; };

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