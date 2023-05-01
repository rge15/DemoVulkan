#pragma once
#include "BaseRenderRSC.hpp"
#include <Engine/Driver/SwapchainMng.hpp>

/**
 * @brief Base class for Pipeline Layout Managers to inherit from
 * 
 * It inhers from Base Render Resource class
 * Manages the common creation parts of all the Pipeline Layouts
 * 
 * Modify the base creation info from child classes before creation  
 * 
 * @see BaseRenderRSC
 * @see BasicPipelineLayout
 * @see ImagePipelineLayout
 */

class BasePipelineLayout : public BaseRenderRSC
{
protected:
    //! Reference to the Vulkan Logical Device
    VkDevice& device_;
    //! Reference to const Swapchain Manager
    const SwapchainMng& swapMng_;

    //! Creation info for the PipelineLayout
    VkPipelineLayoutCreateInfo createInfo_ {};
    //! Handler of the pipeline layout
    VkPipelineLayout pipeLayout_ { VK_NULL_HANDLE };

    /**
     * @brief Construct a new Base Pipeline Layout object
     * 
     * This constructor inits common info between all pipeline layout objects
     * 
     * @param p_device Vulkan Logical device to create the Layout from
     * @param p_swapMng Swapchain Mng for getting info relative for layout creation
     */
    BasePipelineLayout( VkDevice& p_device, const SwapchainMng& p_swapMng ) noexcept;

    /**
     * @brief Inits the base & common creation info for all types of PipelineLayouts
     */
    void
    initBaseCreateInfo() noexcept;

    //TODO : Change p_relTime
    /**
     * @brief Pure virtual method for binding the information of the specific layout
     * 
     * @param p_cmd Reference to the command buffer to bind the info
     * @param p_relTime (This param is a bit hard-coded) Total time of a individual demo in execution
     */
    virtual
    void bindLayoutCmdData( VkCommandBuffer& p_cmd, float p_relTime ) = 0;

    /**
     * @brief Create the Pipeline Layout object
     */
    void
    createPipelineLayout() noexcept;

public:

    /**
     * @brief Destroy the Base Pipeline Layout object
     */
    ~BasePipelineLayout();

    /**
     * @brief Get the Vulkan Pipeline Layout handler
     * 
     * @return VkPipelineLayout&
     */
    inline
    VkPipelineLayout&
    getLayout(){ return pipeLayout_; };
};