#include "InstanceMng.hpp"


InstanceMng::InstanceMng(
    const char* p_appName, const char* p_engineName,
    const uint32_t p_appVersion, const uint32_t p_engineVersion
) noexcept
{
    appInfo_.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo_.pNext = nullptr;
    appInfo_.pApplicationName = p_appName;
    appInfo_.applicationVersion = p_appVersion;
    appInfo_.pEngineName = p_engineName;
    appInfo_.engineVersion = p_engineVersion;
    appInfo_.apiVersion = VK_MAKE_API_VERSION(0,1,0,0);

    fillInstanceInfo();
    createInstance();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

InstanceMng::~InstanceMng() noexcept
{
    vkDestroyInstance(vkInstance_, nullptr);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceMng::fillInstanceInfo() noexcept
{
    instanceInfo_.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo_.pNext = nullptr;
    instanceInfo_.pApplicationInfo = &appInfo_;
    instanceInfo_.flags = 0;

    checkLayer();

    uint32_t glfwCountExtension {0};
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwCountExtension);
    instanceInfo_.enabledExtensionCount = { glfwCountExtension };
    instanceInfo_.ppEnabledExtensionNames = { glfwExtensions };
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceMng::createInstance() noexcept
{
    auto result = vkCreateInstance(&instanceInfo_, nullptr, &vkInstance_);

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

    instanceInfo_.enabledLayerCount = { (uint32_t)_validationLayers.size() };
    instanceInfo_.ppEnabledLayerNames = { _validationLayers.data() };
}
