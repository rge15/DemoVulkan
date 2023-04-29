#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/DrawerMng/CommandMng.hpp>
#include <Engine/Render/PipelineFrameBuffers.hpp>
#include <Engine/Driver/SwapchainMng.hpp>
#include <Engine/Driver/DeviceMng.hpp>

class WorkMng
{
private:
    
    //! Reference to the Vulkan Logical Device for sync object creation
    VkDevice&               device_;
    
    //! Vulkan Fence for cmd buffer availability
    VkFence     cmdBufferAvailable_ { VK_NULL_HANDLE };
    //! Vulkan Semaphore for img availability to render
    VkSemaphore imgAvailable_       { VK_NULL_HANDLE };
    //! Vulkan Semaphore for notifying that a img have been rendered
    VkSemaphore imgRendered_        { VK_NULL_HANDLE };

public:

    /**
     * @brief Construct a new Work Mng object
     * 
     * @param p_deviceMng Reference to the Vulkan Logical Device to synchronize
     */
    explicit WorkMng(VkDevice& p_deviceMng ) noexcept;

    /**
     * @brief Destroy the Work Mng object. It destroys all the sync objets ( fence & semaphores )
     */
    ~WorkMng();

    /**
     * @brief Get the next Swapchain Img Index for rendering into 
     * 
     * @param p_swap Vulkan Swapchain obj
     * @return uint32_t Swapchain Image id to render
     */
    uint32_t
    getImageBufferIndex( VkSwapchainKHR& p_swap );

    /**
     * @brief Method that syncs and waits for the fence objects
     */
    void
    waitBufferSync() noexcept;

    /**
     * @brief Get the Img Available Semaphore object
     * 
     * @return VkSemaphore& 
     */
    inline
    VkSemaphore& getImgAvailableSemaphore(){ return imgAvailable_; };

    /**
     * @brief Get the Img Rendered Semaphore object
     * 
     * @return VkSemaphore& 
     */
    inline
    VkSemaphore& getImgRenderedSemaphore(){ return imgRendered_; };

    /**
     * @brief Get the Cmd Available Fence object
     * 
     * @return VkFence& 
     */
    inline
    VkFence& getCmdAvailableFence(){ return cmdBufferAvailable_; };

private:
    /**
     * @brief Create all the Vulkan Sync Objects 
     */
    void
    createSyncObjects();

};
