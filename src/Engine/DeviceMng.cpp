#include "DeviceMng.hpp"

DeviceMng::DeviceMng(VkInstance& p_instance, VkSurfaceKHR& p_surface) noexcept
: _instance { p_instance }, _surface { p_surface }
{
    getSuitableDevice();
    initLogicalDeviceInfo();
    createLogicalDevice();
    getQueueHandlers();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DeviceMng::~DeviceMng() noexcept
{
    if(_logicalDevice != VK_NULL_HANDLE)
    {
		VkResult result = vkDeviceWaitIdle( _logicalDevice );

        assert(result == VK_SUCCESS);

        vkDestroyDevice( _logicalDevice, nullptr );
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::getSuitableDevice() noexcept
{
    uint32_t phDevicesCount { 0 };
    Vector<VkPhysicalDevice> phDevices;
    vkEnumeratePhysicalDevices( _instance, &phDevicesCount, nullptr );
    phDevices.resize( phDevicesCount );
    vkEnumeratePhysicalDevices( _instance, &phDevicesCount, &phDevices[0] );

    for(auto& device : phDevices)
    {
        _queueIds.reset();
        if(checkDeviceSuitability(device))
        {
            _physicalDevice = device;
            break;
        }
    }

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
DeviceMng::checkDeviceSuitability( VkPhysicalDevice& p_phDevice ) noexcept
{

    bool queueSuitability = checkQueues( p_phDevice );

    bool extensionSuitability = checkExtensions( p_phDevice );

    bool swapchainSuitability = checkSwapchain( p_phDevice );

    if( queueSuitability && extensionSuitability && swapchainSuitability )
        return true;

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
DeviceMng::checkSwapchain( VkPhysicalDevice& p_phDevice ) noexcept
{
    getSwapchainSupportDetails( p_phDevice );

    if( !_swapchainSupportDetails.formats.empty() && !_swapchainSupportDetails.presentModes.empty() )
        return true;

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::getSwapchainSupportDetails( VkPhysicalDevice& p_phDevice ) noexcept
{
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR( p_phDevice, _surface, &_swapchainSupportDetails.capabilities );

    uint32_t presentCount { 0 };
    vkGetPhysicalDeviceSurfacePresentModesKHR( p_phDevice, _surface, &presentCount, nullptr );
    _swapchainSupportDetails.presentModes.resize(presentCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR( p_phDevice, _surface, &presentCount, &_swapchainSupportDetails.presentModes[0] );

    uint32_t formatCount { 0 };
    vkGetPhysicalDeviceSurfaceFormatsKHR( p_phDevice, _surface, &formatCount, nullptr);
    _swapchainSupportDetails.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR( p_phDevice, _surface, &formatCount, &_swapchainSupportDetails.formats[0]);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
DeviceMng::checkExtensions( VkPhysicalDevice& p_phDevice ) noexcept
{
    uint32_t extensionCount { 0 };
    Vector<VkExtensionProperties> availableExtensions;
    vkEnumerateDeviceExtensionProperties( p_phDevice, nullptr, &extensionCount, nullptr );
    availableExtensions.resize(extensionCount);
    vkEnumerateDeviceExtensionProperties( p_phDevice, nullptr, &extensionCount, &availableExtensions[0] );

    Set<std::string> requiredExtensionsSet( _requiredDeviceExtensions.begin(), _requiredDeviceExtensions.end() );

    for(auto& extension : availableExtensions)
    {
        requiredExtensionsSet.erase( extension.extensionName );
    }

    return requiredExtensionsSet.empty();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
DeviceMng::checkQueues( VkPhysicalDevice& p_phDevice ) noexcept
{
    uint32_t countQueueFamilies { 0 };
    Vector<VkQueueFamilyProperties> queueFamilies {};

    vkGetPhysicalDeviceQueueFamilyProperties( p_phDevice, &countQueueFamilies, nullptr );
    queueFamilies.resize(countQueueFamilies);
    vkGetPhysicalDeviceQueueFamilyProperties( p_phDevice, &countQueueFamilies, &queueFamilies[0] );

    int i = 0;
    for(auto& queueFamily : queueFamilies )
    {
        if(checkQueueSuitability( p_phDevice, queueFamily, i++))
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
DeviceMng::checkQueueSuitability( VkPhysicalDevice p_device, VkQueueFamilyProperties p_queueFamily, uint32_t p_id ) noexcept
{
    VkBool32 presentSupport = VK_FALSE;

    if(p_queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT && !(_queueIds._graphicQueueId.has_value()))
        _queueIds._graphicQueueId = p_id;

    vkGetPhysicalDeviceSurfaceSupportKHR( p_device, p_id, _surface, &presentSupport );
    if( presentSupport == VK_TRUE && !(_queueIds._presentQueueId.has_value()) )
        _queueIds._presentQueueId = p_id;
    
    if( _queueIds._presentQueueId.has_value() && _queueIds._graphicQueueId.has_value() )
        return true;

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::createLogicalDevice() noexcept
{
    auto result = vkCreateDevice( _physicalDevice, &_deviceInfo, nullptr, &_logicalDevice );

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::initLogicalDeviceInfo() noexcept
{
    initQueueCreateInfo();
    vkGetPhysicalDeviceFeatures( _physicalDevice, &_phDeviceFeatures );

    _deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    _deviceInfo.pNext = nullptr;
    _deviceInfo.flags = 0;
    _deviceInfo.queueCreateInfoCount = (uint32_t)_queuesCreateInfo.size();
    _deviceInfo.pQueueCreateInfos = _queuesCreateInfo.data();
    _deviceInfo.enabledLayerCount = 0;
    _deviceInfo.ppEnabledLayerNames = nullptr;
    _deviceInfo.enabledExtensionCount = (uint32_t)_requiredDeviceExtensions.size() ;
    _deviceInfo.ppEnabledExtensionNames = _requiredDeviceExtensions.data();
    _deviceInfo.pEnabledFeatures = &_phDeviceFeatures;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::initQueueCreateInfo() noexcept
{
    Set<uint32_t> queuesIds { _queueIds._graphicQueueId.value() , _queueIds._presentQueueId.value() };

    for(auto id : queuesIds)
    {
        VkDeviceQueueCreateInfo queueInfo;
        
        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.pNext = nullptr;
        queueInfo.flags = 0;
        queueInfo.queueCount = 1;
        queueInfo.queueFamilyIndex = id;
        queueInfo.pQueuePriorities = &_queuePriority;

        _queuesCreateInfo.push_back(queueInfo);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::getQueueHandlers() noexcept
{
    vkGetDeviceQueue( _logicalDevice, _queueIds._graphicQueueId.value(), 0, &_graphicQueueHandler );
    vkGetDeviceQueue( _logicalDevice, _queueIds._presentQueueId.value(), 0, &_presentQueueHandler );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------