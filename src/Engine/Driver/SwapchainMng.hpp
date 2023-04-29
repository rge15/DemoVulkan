#pragma once
#include "utilities/typeAliases.hpp"
#include <Engine/utilStructs/SwapchainDetails.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

/**
 * @brief Class for Swapchain Management
 */
class SwapchainMng
{
private:
    //! Swapchain Handler
    VkSwapchainKHR swapchain_ { VK_NULL_HANDLE };

    //! Vulkan Logical device for swap creation 
    VkDevice& device_;
    //! Vulkan Surface to get swap support 
    VkSurfaceKHR& surface_;
    //! Logical Device support data
    const SwapchainDetails& swapDetails_;
    //! Logical Device Queues Ids
    const DeviceQueueFamilies& queueIds_;
    //! Logical Device Families queues Ids 
    Vector<uint32_t> queueFamilies_;

    //! SWapchain Creation Info
    VkSwapchainCreateInfoKHR createInfo_{};

    //! Swapchain Images
    Vector<VkImage> swapImages_;
    //! Image Views from Swapchain Images
    Vector<VkImageView> viewImages_;

public:
    /**
     * @brief Construct a new Swapchain Mng object, creates and manage all the swapchain data
     * 
     * @param p_device Vulkan Logical device for swapchain creation
     * @param p_surface Vulkan Surface to get swapchain data
     * @param p_details Logical Device swapchain support details
     * @param p_queueIds Logical Device Queues Ids info
     */
    SwapchainMng(VkDevice& p_device, VkSurfaceKHR& p_surface, const SwapchainDetails& p_details, const DeviceQueueFamilies& p_queueIds );
    /**
     * @brief Destroy the Swapchain Mng object, the swapchain handler and all the image rsc 
     */
    ~SwapchainMng();

    /**
     * @brief Get the Swapchain Info object
     * 
     * @return const VkSwapchainCreateInfoKHR& 
     */
    inline
    const VkSwapchainCreateInfoKHR&
    getSwapchainInfo() const { return createInfo_; };

    /**
     * @brief Get the Swapchain Image Views vector
     * 
     * @return const Vector<VkImageView>& 
     */
    inline
    const Vector<VkImageView>&
    getSwapchainImageViews() const { return viewImages_; };

    /**
     * @brief Get the Swapchain Handler
     * 
     * @return VkSwapchainKHR& 
     */
    inline
    VkSwapchainKHR&
    getSwapchain() { return swapchain_; };

private:
    /**
     * @brief Inits the Swapchain Creation Info struct
     */
    void
    initCreateInfo();

    /**
     * @brief Create a Swapchain object
     */
    void
    createSwapchain();

    /**
     * @brief Selects the swapchain total images to create with
     */
    void
    selectImageCount();

    /**
     * @brief Selects the color and format for the swapchain imgs
     */
    void
    selectColorAndFormat();

    /**
     * @brief Selects the sharing mode of the swap imgs between device queues
     */
    void
    selectQueueFamiliesImages();

    /**
     * @brief Selects the present mode of the swapchain imgs onto surface
     */
    void
    selectPresentMode();

    /**
     * @brief Once the swap is created it obtain their images
     */
    void
    getSwapchainImages();

    /**
     * @brief Get the Image Views objects from each one of the swapchain imgs
     */
    void
    getImageViews();

};