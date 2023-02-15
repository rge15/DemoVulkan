#include "InstanceMng.hpp"


InstanceMng::InstanceMng(
    const char* p_appName, const char* p_engineName,
    const uint32_t p_appVersion, const uint32_t p_engineVersion
) noexcept
{
    _appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    _appInfo.pNext = nullptr;
    _appInfo.pApplicationName = p_appName;
    _appInfo.applicationVersion = p_appVersion;
    _appInfo.pEngineName = p_engineName;
    _appInfo.engineVersion = p_engineVersion;
    _appInfo.apiVersion = VK_MAKE_API_VERSION(0,1,0,0);

    fillInstanceInfo();
    createInstance();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

InstanceMng::~InstanceMng() noexcept
{
    vkDestroyInstance(_vkInstance, nullptr);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceMng::fillInstanceInfo() noexcept
{
    _instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    _instanceInfo.pNext = nullptr;
    _instanceInfo.pApplicationInfo = &_appInfo;
    _instanceInfo.flags = 0;

    checkLayer();

    uint32_t glfwCountExtension {0};
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwCountExtension);
    _instanceInfo.enabledExtensionCount = { glfwCountExtension };
    _instanceInfo.ppEnabledExtensionNames = { glfwExtensions };
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceMng::createInstance() noexcept
{
    auto result = vkCreateInstance(&_instanceInfo, nullptr, &_vkInstance);

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceMng::checkLayer() noexcept
{
    uint32_t layerCount { 0 };
	vkEnumerateInstanceLayerProperties( &layerCount, nullptr);
	Vector<VkLayerProperties> layers( layerCount );
	vkEnumerateInstanceLayerProperties( &layerCount, layers.data());

    bool layerFound { false };
    for(auto& neededLayer : _validationLayers)
    {
        layerFound = false;
        for(auto& availibleLayer : layers)
        {
            if( std::strcmp( neededLayer, availibleLayer.layerName ) == 0 )
            {
                layerFound = true;
                break;
            }
        }

        assert( layerFound );
    }

    _instanceInfo.enabledLayerCount = { (uint32_t)_validationLayers.size() };
    _instanceInfo.ppEnabledLayerNames = { _validationLayers.data() };
}
