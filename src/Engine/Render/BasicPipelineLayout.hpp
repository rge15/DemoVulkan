#pragma once
#include "BasePipelineLayout.hpp"
#include <utilities/Timer/Timer.hpp>

/**
 * @brief Basic Pipeline Layout which doesn't have description sets.
 * 
 * It contains base push constants for each shader as:
 * 
 * - AbsoluteTime       : Total Time of execution of the program 
 * - RelativeTime       : Total Time of execution of the demo
 * - WindowResolution   : Resolution of the screen
 * 
 * This class PUBLIC inhers from @see BasePipelineLayout
 */
class BasicPipelineLayout : public BasePipelineLayout
{
private:
    //! Push constants vector
    Vector<VkPushConstantRange> pushConstantsInfo_;

public:
    /**
     * @brief Construct a new Basic Pipeline Layout object
     * 
     * @param p_device Vulkan Logical device to create the Layout from
     * @param p_swapMng Swapchain Mng for getting info relative for layout creation
     */
    BasicPipelineLayout( VkDevice& p_device, const SwapchainMng& p_swapMng );

    /**
     * @brief Destroy the Basic Pipeline Layout object
     * 
     * The parent class already manages the Vulkan Obj destruction
     */
    ~BasicPipelineLayout() = default;

    /**
     * @brief Method that sends push constant data to the command buffer
     * 
     * @param p_cmd Reference to the command buffer to bind the info
     * @param p_relTime (This param is a bit hard-coded) Total time of a individual demo in execution
     */
    void
    sendPushConstantData( 
        VkCommandBuffer& p_cmd, float p_relTime
    ) noexcept;

    //TODO : Change p_relTime
    /**
     * @brief Pure virtual overrided method for binding the information of the specific layout
     * 
     * @param p_cmd Reference to the command buffer to bind the info
     * @param p_relTime (This param is a bit hard-coded) Total time of a individual demo in execution
     */
    void
    bindLayoutCmdData( VkCommandBuffer& p_cmd, float p_relTime ) override final;

private:

    /**
     * @brief Push constants common info
     */
    void
    addPushConstantInfo();

    /**
     * @brief Change specific params on the pipeline layout creation info
     */
    void
    initCreateInfo();

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