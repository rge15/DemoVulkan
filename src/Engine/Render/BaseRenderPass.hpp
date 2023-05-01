#pragma once
#include "BaseRenderRSC.hpp"
#include <Engine/Driver/SwapchainMng.hpp>


/**
 * @brief Base class for Render Pass Managers to inherit from
 * 
 * It inhers from Base Renser Resource class
 * Manages the common creation parts of all the Render Passes
 * 
 * Modify the base creation info from child classes before creation
 * 
 * In this engine version there is just 1 REnderPassMng obj
 * 
 * @see BaseRenderRSC
 * @see BasicRenderPass
 */

class BaseRenderPass : public BaseRenderRSC
{
protected:
    //! Reference to the Vulkan Logical Device
    VkDevice& device_;
    //! Reference to const Swapchain Manager
    const SwapchainMng& swapMng_;
    
    //! Render Pass attachment description
    VkAttachmentDescription attachmentDesc_ {};
    //! Render Pass attachment references
    VkAttachmentReference   attachmentReference_ {};
    //! Render Pass sub-passes description
    VkSubpassDescription    subpassDesc_ {};
    //! Creation info for the RenderPass
    VkRenderPassCreateInfo  createInfo_ {};

    //! Vulkan Render Pass handler
    VkRenderPass renderPass_ { VK_NULL_HANDLE };

    /**
     * @brief Construct a new Base Render Pass object
     * 
     * This constructor inits common info between all render pass objects
     * 
     * @param p_device Vulkan Logical device to create the Render Pass from
     * @param p_swapMng Swapchain Mng for getting info relative for Render Pass creation
     */
    BaseRenderPass( VkDevice& p_device, const SwapchainMng& p_swapMng ) noexcept;

    /**
     * @brief Create the Render Pass object
     */
    void
    createRenderPass() noexcept;

    /**
     * @brief Inits the base & common creation info for all types of Render Pass
     */
    void
    initBaseCreateInfo() noexcept;

    /**
     * @brief Inits the base attachment info for all Render Passes
     */
    void
    initBaseAttachementInfo() noexcept;

    /**
     * @brief Inits the base subpass info such as dependencies for all the Render Passes
     */
    void
    initBaseSupbassInfo() noexcept;

public:

    /**
     * @brief Destroy the Base Render Pass object
     */
    ~BaseRenderPass();

    /**
     * @brief Get the Vulkan Render Pass handler
     * 
     * @return VkRenderPass& 
     */
    inline
    VkRenderPass&
    getRenderPass(){ return renderPass_; };

};