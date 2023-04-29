#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

/**
 * @brief Class for handling Vulkan Commands both for memory and for recording and sending work
 */
class CommandMng
{
private:

    //! Ref to the Vulkan logical device 
    VkDevice&                   device_;

    //! Ref to a const queues ids mng with the ids of the logical device queues to execute on the GPU 
    const DeviceQueueFamilies&  queueFamilyId_;

    //! Vulkan Command memory pool handler 
    VkCommandPool   pool_       { VK_NULL_HANDLE };
    //! Vulkan Command Buffer handler 
    VkCommandBuffer cmdBuffer_  { VK_NULL_HANDLE };

    //! Begin Command Recording Info 
    VkCommandBufferBeginInfo beginRecordInfo_ {};

public:

    /**
     * @brief Construct a new Command Mng object
     * 
     * @param p_device Reference to Vulkan Logical Device in which execute the work submited by this class
     * @param p_queueFamilyId Reference to get the device queue Ids for each queue type
     */
    explicit CommandMng( 
        VkDevice& p_device, const DeviceQueueFamilies& p_queueFamilyId
    ) noexcept;

    /**
     * @brief Destroy the Command Mng object, frees the Command Memory Pool and destroys the Command Buffer
     */
    ~CommandMng();

    /**
     * @brief Get the Cmd Buffer object that handles this instance of CommandMng
     * 
     * @return VkCommandBuffer& 
     */
    inline
    VkCommandBuffer&
    getCmdBuffer() { return cmdBuffer_; };

    /**
     * @brief Starts a single Vulkan recording process
     */
    void
    beginRecording() noexcept;

    /**
     * @brief Ends a Vulkan recording process
     */
    void
    endRecording() noexcept;

    /**
     * @brief Submits a single time command on the specifies queue with no addition command info 
     * 
     * @param p_queue Vulkan Queue Handler to execute the command on
     */
    void
    submitSingle( VkQueue& p_queue ) noexcept;

private:

    /**
     * @brief Create the Command Pool handler for the class
     */
    void
    createCommandPool() noexcept;

    /**
     * @brief Allocates the command buffer object once created the command pool
     */
    void
    allocateCommandBuffer() noexcept;

    /**
     * @brief Fills the common information on recording command info 
     */
    void
    initCommandBufferRecordingInfo() noexcept;

};