#pragma once
#include "BasePipelineLayout.hpp"
#include <utilities/Timer/Timer.hpp>

/**
 * @brief Image Pipeline Layout which have a single descriptor set & push constants.
 * 
 * It contains base push constants for each shader as:
 * 
 * - AbsoluteTime       : Total Time of execution of the program 
 * - RelativeTime       : Total Time of execution of the demo
 * - WindowResolution   : Resolution of the screen
 * 
 * The Descriptor set that contains manages 1 common image for reading/writing
 * between all fotograms of the app
 * 
 * This class PUBLIC inhers from @see BasePipelineLayout
 */
class ImagePipelineLayout : public BasePipelineLayout
{
private:
    //! Vector of Push Constant info
    Vector<VkPushConstantRange> pushConstantsInfo_;

    //! VkImage for the pipeline
    VkImage     image_      { VK_NULL_HANDLE };
    //! VkImageView of the image to pass
    VkImageView imageView_  { VK_NULL_HANDLE };

    //! Vulkan Device Memory to allocate Image
    VkDeviceMemory memory_  { VK_NULL_HANDLE };
    
    //! Descriptor Set Layout for the image
    VkDescriptorSetLayout descSetLayout_ { VK_NULL_HANDLE };
    
    //! Descriptor Pool Memory
    VkDescriptorPool    descPool_   { VK_NULL_HANDLE };
    //! Descriptor Set
    VkDescriptorSet     descSet_    { VK_NULL_HANDLE };

public:
    /**
     * @brief Construct a new Image Pipeline Layout object
     * 
     * @param p_device 
     * @param p_swapMng 
     */
    ImagePipelineLayout(VkDevice& p_device, const SwapchainMng& p_swapMng);
    
    /**
     * @brief Destroy the Image & ImageView of the manager
     */
    ~ImagePipelineLayout();

    //TODO : Change p_relTime
    /**
     * @brief Pure virtual overrided method for binding the information of the specific layout
     * 
     * @param p_cmd Reference to the command buffer to bind the info
     * @param p_relTime (This param is a bit hard-coded) Total time of a individual demo in execution
     */
    void
    bindLayoutCmdData( VkCommandBuffer& p_cmd, float p_relTime ) override final;

    /**
     * @brief COnfigures the pipeline barrier for changing the image layout
     * 
     * @param p_cmd Reference to the command buffer to record in the barrier
     */
    void
    setPipelineImageBarrier( VkCommandBuffer& p_cmd );

private:

    /**
     * @brief Sends all the push constant data to the command buffer
     * 
     * @param p_cmd Reference to the command buffer to bind the info
     * @param p_relTime (This param is a bit hard-coded) Total time of a individual demo in execution
     */
    void
    sendPushConstantData( 
        VkCommandBuffer& p_cmd, float p_relTime
    ) noexcept;

    /**
     * @brief Binds the descriptor set image to the command buffer
     * 
     * @param p_cmd Command buffer to bind the image
     */
    void
    bindDescriptorSetImages( VkCommandBuffer& p_cmd );

    /**
     * @brief Updates the base & common info from parent class
     * 
     * @see BasePipelineLayout
     */
    void
    updateDescSetValue() noexcept;

    /**
     * @brief Allocates the descriptor set into descripto memory pool
     */
    void
    allocateDescriptorSet() noexcept;

    /**
     * @brief Reserve & Allocates memory for the descriptro set
     * 
     * @see createDescriptorPool()
     * @see allocateDescriptorSet() 
     */
    void
    createDescriptorSetMemory() noexcept;

    /**
     * @brief Create the Descriptor Memory Pool
     */
    void
    createDescriptorPool() noexcept;

    /**
     * @brief Binds the created Image to the Memory allocated for
     */
    void
    bindImageMemory() noexcept;

    /**
     * @brief Checks the memory type for the image and allocats specific memory for the pipeline image
     */
    void
    allocateImageMemory() noexcept;

    /**
     * @brief Create the pipeline Image
     */
    void
    createImage() noexcept;

    /**
     * @brief Create the ImageView from the Pipeline Image
     */
    void
    createImageView() noexcept;

    /**
     * @brief Configure and create all the relative image resources
     * 
     * @see createImage()
     * @see allocateImageMemory()
     * @see bindImageMemory()
     * @see createImageView()
     */
    void
    setImageConfiguration() noexcept;

    /**
     * @brief Set the Descriptor Set Configuration object
     */
    void
    setDescriptorSetConfiguration() noexcept;

    /**
     * @brief Push constants specific info for this layout
     */
    void
    addPushConstantInfo() noexcept;

    /**
     * @brief Change the specific creation info for this pipeline layout  
     */
    void
    initCreateInfo() noexcept;

    /**
     * @brief Get the Push Constant Size object alligned for push constante data for shader
     * 
     * @tparam T Type of the data to align the size for the uniform block
     * @param p_data Vector of data to check allignment
     * @return uint32_t Allignment for the push constant block
     */
    template<typename T>
    uint32_t
    getPushConstantSize( const Vector<T>& p_data ) noexcept;

};