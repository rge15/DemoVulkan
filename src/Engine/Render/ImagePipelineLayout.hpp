#pragma once
#include "BasePipelineLayout.hpp"
#include <utilities/Timer/Timer.hpp>


class ImagePipelineLayout : public BasePipelineLayout
{
private:
    Vector<VkPushConstantRange> pushConstantsInfo_;

    //Image RSC
    VkImage     image_      { VK_NULL_HANDLE };
    VkImageView imageView_  { VK_NULL_HANDLE };

    //Memory RSC
    VkDeviceMemory memory_  { VK_NULL_HANDLE };
    
    //Descriptor Set Layout
    VkDescriptorSetLayout descSetLayout_ { VK_NULL_HANDLE };
    
    //Descriptor Set Memory
    VkDescriptorPool    descPool_   { VK_NULL_HANDLE };
    VkDescriptorSet     descSet_    { VK_NULL_HANDLE };
    //TODO : Ver los tipos de datos que hacen falta para reservar memoria, Img, etc... 


public:
    ImagePipelineLayout(VkDevice& p_device, const SwapchainMng& p_swapMng);
    ~ImagePipelineLayout();

    void
    sendPushConstantData( 
        VkCommandBuffer& p_cmd, float p_relTime
    ) noexcept;

    void
    bindLayoutCmdData( VkCommandBuffer& p_cmd, float p_relTime ) override final;

private:

    void
    updateDescSetValue() noexcept;

    void
    allocateDescriptorSet() noexcept;

    void
    createDescriptorSetMemory() noexcept;

    void
    createDescriptorPool() noexcept;

    void
    bindImageMemory() noexcept;

    void
    allocateImageMemory() noexcept;

    void
    createImage() noexcept;

    void
    createImageView() noexcept;

    void
    setImageConfiguration() noexcept;

    void
    setDescriptorSetConfiguration() noexcept;

    void
    addPushConstantInfo() noexcept;

    void
    initCreateInfo() noexcept;

    template<typename T>
    uint32_t
    getPushConstantSize( const Vector<T>& p_data ) noexcept;


};