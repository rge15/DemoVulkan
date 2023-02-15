#include "ShaderSrc.hpp"

ShaderSrc::ShaderSrc(VkDevice& p_device, String&& p_filePath, VkShaderStageFlagBits p_shaderStage) noexcept
: _device { p_device }, _shaderStage { p_shaderStage }
{
    readFile( p_filePath );
    initShaderModuleInfo();
    createShaderModule();
    initPipelineStageInfo();
}

ShaderSrc::~ShaderSrc()
{
    if(_shaderModule != VK_NULL_HANDLE)
        vkDestroyShaderModule( _device, _shaderModule, nullptr );
}

void
ShaderSrc::readFile(String& p_file)
{
    std::ifstream file( p_file, std::ios::ate | std::ios::binary | std::ios::in );

    assert( file.is_open() );

    size_t fileSize = (size_t)file.tellg();

    Vector<char> code;

    code.resize( fileSize );
    _shaderCode.resize( fileSize >> 2 );

    file.seekg(0);
    file.read( code.data(), fileSize );

    memcpy( _shaderCode.data(), code.data(), fileSize );

    file.close();
}

void
ShaderSrc::createShaderModule()
{
    auto result = vkCreateShaderModule( _device, &_shaderCreateInfo, nullptr, &_shaderModule );

    assert(result == VK_SUCCESS);
}

void
ShaderSrc::initShaderModuleInfo()
{
    _shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    _shaderCreateInfo.pNext = nullptr;
    _shaderCreateInfo.flags = 0;
    _shaderCreateInfo.codeSize = _shaderCode.size() << 2;
    _shaderCreateInfo.pCode = _shaderCode.data();
}

void
ShaderSrc::initPipelineStageInfo()
{
    _shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    _shaderStageInfo.pNext = nullptr;
    _shaderStageInfo.flags = 0;
    _shaderStageInfo.module = _shaderModule;
    _shaderStageInfo.pName = "main";
    _shaderStageInfo.stage = _shaderStage;
    _shaderStageInfo.pSpecializationInfo = nullptr;
}
