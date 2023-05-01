#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

/**
 * @brief Class resource for managing all the information of each shader file
 */
class ShaderSrc
{
private:
    //! VUlkan device to execute with the code
    VkDevice& device_;

    //! Shader stage flags
    VkShaderStageFlagBits shaderStage_;
    
    //! Vulkan Shader Module creation info
    VkShaderModuleCreateInfo shaderCreateInfo_ {};
    //! Vulkan Pipeline Shader Stage info
    VkPipelineShaderStageCreateInfo shaderStageInfo_ {};

    //! Vector with the shader code parsed in uin32_t data
    Vector<uint32_t> shaderCode_;

    //! Vulkan Shader Module Handlder
    VkShaderModule shaderModule_ { VK_NULL_HANDLE };

public:
    /**
     * @brief Construct a new Shader Src object
     * 
     * @param p_device Device to create the shader with
     * @param p_filePath Path to the SPIR-V file with the shader binary
     * @param p_shaderStage Corresponding Shader Stage of the shader RSC (Vertex Shader by default)
     */
    ShaderSrc(VkDevice& p_device, String&& p_filePath, VkShaderStageFlagBits p_shaderStage = VK_SHADER_STAGE_VERTEX_BIT ) noexcept;
    
    /**
     * @brief Destroy the Shader Src object and destroys the shader module obj
     */
    ~ShaderSrc();

    /**
     * @brief Get the Shader Stage Info object
     * 
     * @return VkPipelineShaderStageCreateInfo 
     */
    inline
    VkPipelineShaderStageCreateInfo
    getShaderStageInfo() { return shaderStageInfo_; };

private:

    /**
     * @brief Reads the entire file of the shader
     * 
     * @param p_pathFile Path to the shader file
     */
    void
    readFile(String& p_pathFile);

    /**
     * @brief Creates the Vulkan Shader Module object
     */
    void
    createShaderModule();

    /**
     * @brief Fills the shader module creation info struct data relative to the shader code
     */
    void
    initShaderModuleInfo();

    /**
     * @brief Fills the info about the pipeline stage of the shader
     */
    void
    initPipelineStageInfo();

};