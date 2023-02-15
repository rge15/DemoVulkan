#pragma once
#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class ShaderSrc
{
private:

    VkDevice& _device;

    VkShaderStageFlagBits _shaderStage;
    
    VkShaderModuleCreateInfo _shaderCreateInfo {};
    VkPipelineShaderStageCreateInfo _shaderStageInfo {};

    Vector<uint32_t> _shaderCode;

    VkShaderModule _shaderModule { VK_NULL_HANDLE };

public:
    ShaderSrc(VkDevice& p_device, String&& p_filePath, VkShaderStageFlagBits p_shaderStage = VK_SHADER_STAGE_VERTEX_BIT ) noexcept;
    ~ShaderSrc();

    inline
    VkPipelineShaderStageCreateInfo
    getShaderStageInfo() { return _shaderStageInfo; };

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