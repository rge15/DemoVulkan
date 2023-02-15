#pragma once
#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/utilStructs/SwapchainDetails.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

class DeviceMng
{
private:
	
	VkInstance&		_instance;
	VkSurfaceKHR&	_surface;

    VkPhysicalDeviceFeatures	_phDeviceFeatures {};
	VkDeviceCreateInfo 			_deviceInfo {};

	VkPhysicalDevice	_physicalDevice { VK_NULL_HANDLE };
	VkDevice			_logicalDevice 	{ VK_NULL_HANDLE };

	Vector<VkDeviceQueueCreateInfo> _queuesCreateInfo;

	VkQueue	_graphicQueueHandler { VK_NULL_HANDLE };
	VkQueue	_presentQueueHandler { VK_NULL_HANDLE };

	DeviceQueueFamilies _queueIds{};
	float	_queuePriority { 1.f };

	SwapchainDetails _swapchainSupportDetails {};

	const Vector<const char*> _requiredDeviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

public:
    DeviceMng(VkInstance& p_instance, VkSurfaceKHR& p_surface) noexcept;
	~DeviceMng();

	inline
	const DeviceQueueFamilies&
	getFamilyQueueIds() const noexcept
	{
		return _queueIds;
	}

	inline
	const SwapchainDetails&
	getSwapchainDetails() const noexcept
	{
		return _swapchainSupportDetails;
	}

	inline
	VkDevice&
	getDevice() noexcept
	{
		return _logicalDevice;
	}

	inline
	VkQueue&
	getGraphicQueueHandler() noexcept
	{
		return _graphicQueueHandler;
	}

	inline
	VkQueue&
	getPresentQueueHandler() noexcept
	{
		return _presentQueueHandler;
	}


private:

	void
	getSuitableDevice() noexcept;

	bool
	checkDeviceSuitability( VkPhysicalDevice& p_phDevice ) noexcept;

	void
	initQueueCreateInfo() noexcept;
	
	void
    initLogicalDeviceInfo() noexcept;

	void
	createLogicalDevice() noexcept;

	void
	getQueueHandlers() noexcept;

	bool
	checkQueueSuitability( VkPhysicalDevice p_device, VkQueueFamilyProperties p_queueFamily, uint32_t p_id ) noexcept;

	bool
	checkExtensions( VkPhysicalDevice& p_phDevice ) noexcept;

	bool
	checkQueues( VkPhysicalDevice& p_phDevice ) noexcept;

	bool
	checkSwapchain( VkPhysicalDevice& p_phDevice ) noexcept;

	void
	getSwapchainSupportDetails( VkPhysicalDevice& p_phDevice ) noexcept;

};