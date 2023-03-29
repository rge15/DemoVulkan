#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/utilStructs/SwapchainDetails.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

class DeviceMng
{
private:
	
	VkInstance&		instance_;
	VkSurfaceKHR&	surface_;

    VkPhysicalDeviceFeatures	phDeviceFeatures_ {};
	VkDeviceCreateInfo 			deviceInfo_ {};

	VkPhysicalDevice	physicalDevice_ { VK_NULL_HANDLE };
	VkDevice			logicalDevice_ 	{ VK_NULL_HANDLE };

	Vector<VkDeviceQueueCreateInfo> queuesCreateInfo_;

	VkQueue	graphicQueueHandler_ { VK_NULL_HANDLE };
	VkQueue	presentQueueHandler_ { VK_NULL_HANDLE };

	DeviceQueueFamilies queueIds_{};
	float	queuePriority_ { 1.f };

	SwapchainDetails swapchainSupportDetails_ {};

	const Vector<const char*> requiredDeviceExtensions_ =
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
		return queueIds_;
	}

	inline
	const SwapchainDetails&
	getSwapchainDetails() const noexcept
	{
		return swapchainSupportDetails_;
	}

	inline
	VkDevice&
	getDevice() noexcept
	{
		return logicalDevice_;
	}

	inline
	VkQueue&
	getGraphicQueueHandler() noexcept
	{
		return graphicQueueHandler_;
	}

	inline
	VkQueue&
	getPresentQueueHandler() noexcept
	{
		return presentQueueHandler_;
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