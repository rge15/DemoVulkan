#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class ShaderSrc
{
private:

    VkDevice& device_;

    VkShaderStageFlagBits shaderStage_;
    
    VkShaderModuleCreateInfo shaderCreateInfo_ {};
    VkPipelineShaderStageCreateInfo shaderStageInfo_ {};

    Vector<uint32_t> shaderCode_;

    VkShaderModule shaderModule_ { VK_NULL_HANDLE };

public:
    ShaderSrc(VkDevice& p_device, String&& p_filePath, VkShaderStageFlagBits p_shaderStage = VK_SHADER_STAGE_VERTEX_BIT ) noexcept;
    ~ShaderSrc();

    inline
    VkPipelineShaderStageCreateInfo
    getShaderStageInfo() { return shaderStageInfo_; };

private:

    void
    readFile(String& p_file);

    void
    createShaderModule();

    void
    initShaderModuleInfo();

    void
    initPipelineStageInfo();

};