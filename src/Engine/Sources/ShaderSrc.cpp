#include "ShaderSrc.hpp"

ShaderSrc::ShaderSrc(VkDevice& p_device, String&& p_filePath, VkShaderStageFlagBits p_shaderStage) noexcept
: device_ { p_device }, shaderStage_ { p_shaderStage }
{
    readFile( p_filePath );
    initShaderModuleInfo();
    createShaderModule();
    initPipelineStageInfo();
}

ShaderSrc::~ShaderSrc()
{
    if(shaderModule_ != VK_NULL_HANDLE)
        vkDestroyShaderModule( device_, shaderModule_, nullptr );
}

void
ShaderSrc::readFile(String& p_file)
{
    std::ifstream file( p_file, std::ios::ate | std::ios::binary | std::ios::in );

    assert( file.is_open() );

    size_t fileSize = (size_t)file.tellg();

    Vector<char> code;

    code.resize( fileSize );
    shaderCode_.resize( fileSize >> 2 );

    file.seekg(0);
    file.read( code.data(), fileSize );

    memcpy( shaderCode_.data(), code.data(), fileSize );

    file.close();
}

void
ShaderSrc::createShaderModule()
{
    auto result = vkCreateShaderModule( device_, &shaderCreateInfo_, nullptr, &shaderModule_ );

    assert(result == VK_SUCCESS);
}

void
ShaderSrc::initShaderModuleInfo()
{
    shaderCreateInfo_.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderCreateInfo_.pNext = nullptr;
    shaderCreateInfo_.flags = 0;
    shaderCreateInfo_.codeSize = shaderCode_.size() << 2;
    shaderCreateInfo_.pCode = shaderCode_.data();
}

void
ShaderSrc::initPipelineStageInfo()
{
    shaderStageInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfo_.pNext = nullptr;
    shaderStageInfo_.flags = 0;
    shaderStageInfo_.module = shaderModule_;
    shaderStageInfo_.pName = "main";
    shaderStageInfo_.stage = shaderStage_;
    shaderStageInfo_.pSpecializationInfo = nullptr;
}
