#include "DeviceMng.hpp"

DeviceMng::DeviceMng(VkInstance& p_instance, VkSurfaceKHR& p_surface) noexcept
: instance_ { p_instance }, surface_ { p_surface }
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
    if(logicalDevice_ != VK_NULL_HANDLE)
    {
		VkResult result = vkDeviceWaitIdle( logicalDevice_ );

        assert(result == VK_SUCCESS);

        vkDestroyDevice( logicalDevice_, nullptr );
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::getSuitableDevice() noexcept
{
    uint32_t phDevicesCount { 0 };
    Vector<VkPhysicalDevice> phDevices;
    vkEnumeratePhysicalDevices( instance_, &phDevicesCount, nullptr );
    phDevices.resize( phDevicesCount );
    vkEnumeratePhysicalDevices( instance_, &phDevicesCount, &phDevices[0] );

    for(auto& device : phDevices)
    {
        queueIds_.reset();
        if(checkDeviceSuitability(device))
        {
            physicalDevice_ = device;
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

    if( !swapchainSupportDetails_.formats.empty() && !swapchainSupportDetails_.presentModes.empty() )
        return true;

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::getSwapchainSupportDetails( VkPhysicalDevice& p_phDevice ) noexcept
{
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR( p_phDevice, surface_, &swapchainSupportDetails_.capabilities );

    uint32_t presentCount { 0 };
    vkGetPhysicalDeviceSurfacePresentModesKHR( p_phDevice, surface_, &presentCount, nullptr );
    swapchainSupportDetails_.presentModes.resize(presentCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR( p_phDevice, surface_, &presentCount, &swapchainSupportDetails_.presentModes[0] );

    uint32_t formatCount { 0 };
    vkGetPhysicalDeviceSurfaceFormatsKHR( p_phDevice, surface_, &formatCount, nullptr);
    swapchainSupportDetails_.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR( p_phDevice, surface_, &formatCount, &swapchainSupportDetails_.formats[0]);
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

    Set<std::string> requiredExtensionsSet( requiredDeviceExtensions_.begin(), requiredDeviceExtensions_.end() );

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

    if(p_queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT && !(queueIds_._graphicQueueId.has_value()))
        queueIds_._graphicQueueId = p_id;

    vkGetPhysicalDeviceSurfaceSupportKHR( p_device, p_id, surface_, &presentSupport );
    if( presentSupport == VK_TRUE && !(queueIds_._presentQueueId.has_value()) )
        queueIds_._presentQueueId = p_id;
    
    if( queueIds_._presentQueueId.has_value() && queueIds_._graphicQueueId.has_value() )
        return true;

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::createLogicalDevice() noexcept
{
    auto result = vkCreateDevice( physicalDevice_, &deviceInfo_, nullptr, &logicalDevice_ );

    assert(result == VK_SUCCESS);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::initLogicalDeviceInfo() noexcept
{
    initQueueCreateInfo();
    vkGetPhysicalDeviceFeatures( physicalDevice_, &phDeviceFeatures_ );

    deviceInfo_.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo_.pNext = nullptr;
    deviceInfo_.flags = 0;
    deviceInfo_.queueCreateInfoCount = (uint32_t)queuesCreateInfo_.size();
    deviceInfo_.pQueueCreateInfos = queuesCreateInfo_.data();
    deviceInfo_.enabledLayerCount = 0;
    deviceInfo_.ppEnabledLayerNames = nullptr;
    deviceInfo_.enabledExtensionCount = (uint32_t)requiredDeviceExtensions_.size() ;
    deviceInfo_.ppEnabledExtensionNames = requiredDeviceExtensions_.data();
    deviceInfo_.pEnabledFeatures = &phDeviceFeatures_;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::initQueueCreateInfo() noexcept
{
    Set<uint32_t> queuesIds { queueIds_._graphicQueueId.value() , queueIds_._presentQueueId.value() };

    for(auto id : queuesIds)
    {
        VkDeviceQueueCreateInfo queueInfo;
        
        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.pNext = nullptr;
        queueInfo.flags = 0;
        queueInfo.queueCount = 1;
        queueInfo.queueFamilyIndex = id;
        queueInfo.pQueuePriorities = &queuePriority_;

        queuesCreateInfo_.push_back(queueInfo);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng::getQueueHandlers() noexcept
{
    vkGetDeviceQueue( logicalDevice_, queueIds_._graphicQueueId.value(), 0, &graphicQueueHandler_ );
    vkGetDeviceQueue( logicalDevice_, queueIds_._presentQueueId.value(), 0, &presentQueueHandler_ );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------