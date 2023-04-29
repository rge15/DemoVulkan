#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/utilStructs/SwapchainDetails.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>


/**
 * @brief Manager for Vulkan physical device selection and logical device management
 */
class DeviceMng
{
private:

	//! Reference to the Vulkan Instance
	VkInstance&		instance_;
	//! Reference to the Vulkan Suface obj(KHR extension)
	VkSurfaceKHR&	surface_;

	//! Selected physical device features
    VkPhysicalDeviceFeatures	phDeviceFeatures_ {};
	//! Selected physical device info for logical device creation
	VkDeviceCreateInfo 			deviceInfo_ {};

	//! Handler of the Vulkan Physical Device
	VkPhysicalDevice	physicalDevice_ { VK_NULL_HANDLE };
	//! Handler oof the Vulkan Logical Device
	VkDevice			logicalDevice_ 	{ VK_NULL_HANDLE };

	//! Vector for each device queue creation info
	Vector<VkDeviceQueueCreateInfo> queuesCreateInfo_;

	//! Device Queues Ids for handlers
	DeviceQueueFamilies queueIds_{};
	//! Queue Priority value (same priority right now for each queue)
	float	queuePriority_ { 1.f };

	//! Handler of the Device Graphics Queue
	VkQueue	graphicQueueHandler_ { VK_NULL_HANDLE };
	//! Handler of the Device Present Queue (KHR ext)
	VkQueue	presentQueueHandler_ { VK_NULL_HANDLE };

	//! Swapchain Device support details
	SwapchainDetails swapchainSupportDetails_ {};

	//! Vector of required Extensions to be supported
	const Vector<const char*> requiredDeviceExtensions_ =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

public:
	/**
	 * @brief Construct a new Device Mng object and creates the logical device 
	 * 
	 * It selects the best device of the system which supports all the required extensions, queues and memory stuff.
	 * Next to this it creates the device and gets all the handlers for the queues.
	 * 
	 * @param p_instance Reference to the Vulkan Instance to look for the supported physical devices
	 * @param p_surface Reference to the VkSurface to check for Swapchain support
	 */
    DeviceMng(VkInstance& p_instance, VkSurfaceKHR& p_surface) noexcept;
	
	/**
	 * @brief Destroy the Device Mng object and destroy the logical device handler
	 */
	~DeviceMng();

	/**
	 * @brief Get the Family Queue Ids object
	 * 
	 * @return const DeviceQueueFamilies& 
	 */
	inline
	const DeviceQueueFamilies&
	getFamilyQueueIds() const noexcept
	{
		return queueIds_;
	}

	/**
	 * @brief Get the Logical Device Swapchain Details object
	 * 
	 * @return const SwapchainDetails& 
	 */
	inline
	const SwapchainDetails&
	getSwapchainDetails() const noexcept
	{
		return swapchainSupportDetails_;
	}

	/**
	 * @brief Get the Vulkan Device Handler
	 * 
	 * @return VkDevice& 
	 */
	inline
	VkDevice&
	getDevice() noexcept
	{
		return logicalDevice_;
	}

	/**
	 * @brief Get the Graphic Queue Handler object
	 * 
	 * @return VkQueue& 
	 */
	inline
	VkQueue&
	getGraphicQueueHandler() noexcept
	{
		return graphicQueueHandler_;
	}

	/**
	 * @brief Get the Present Queue Handler object
	 * 
	 * @return VkQueue& 
	 */
	inline
	VkQueue&
	getPresentQueueHandler() noexcept
	{
		return presentQueueHandler_;
	}


private:

	/**
	 * @brief Get the most suitable physical device available from the Instance Object
	 * 
	 * @see checkDeviceSuitability( VkPhysicalDevice& p_phDevice )
	 */
	void
	getSuitableDevice() noexcept;

	/**
	 * @brief Checks if the received physical device supports all the execution requeriments
	 * 
	 * @param p_phDevice Physical device to check
	 * @return true If it support all the requeriment
	 * @return false If it doesn't support all the requeriment
	 * 
	 * @see checkQueues( VkPhysicalDevice& p_phDevice )
	 * @see checkQueues( VkPhysicalDevice& p_phDevice )
	 * @see checkSwapchain( VkPhysicalDevice& p_phDevice )
	 */
	bool
	checkDeviceSuitability( VkPhysicalDevice& p_phDevice ) noexcept;

	/**
	 * @brief Inits the creation info struct fo each queue to be created
	 */
	void
	initQueueCreateInfo() noexcept;

	/**
	 * @brief Inits the logical device creation info
	 */
	void
    initLogicalDeviceInfo() noexcept;

	/**
	 * @brief Create a Vulkan Logical Device object from the physical device selected
	 */
	void
	createLogicalDevice() noexcept;

	/**
	 * @brief Gets the Queue Handlers objects for each required queue from the logical device
	 */
	void
	getQueueHandlers() noexcept;

	/**
	 * @brief Checks if the passed physical device suits the queue requeriments in the queue family passed
	 * 
	 * Right now it just checks if the Queue Family supports all the required queue types 
	 * 
	 * @param p_device Physical device to check with
	 * @param p_queueFamily Vulkan Queue Family properties to check with
	 * @param p_id Queue Family id at the physical device
	 * @return true If it suits the requeriments
	 * @return false If it doesn't suits the requeriments
	 */
	bool
	checkQueueSuitability( VkPhysicalDevice& p_device, VkQueueFamilyProperties& p_queueFamily, uint32_t p_id ) noexcept;

	/**
	 * @brief Checks if the physical device supports all the required extensions
	 * 
	 * @param p_phDevice Physical device to check with
	 * @return true If it supports all the extensions
	 * @return false If it doensn't supports all the extensions
	 * 
	 * @see requiredDeviceExtensions_
	 */
	bool
	checkExtensions( VkPhysicalDevice& p_phDevice ) noexcept;

	/**
	 * @brief Checks if the physical device have some queue family that fits the queue requeriments
	 * 
	 * @param p_phDevice Physical device to get the queue families from and to check with
	 * @return true If the device have some queue family that fits the requeriments
	 * @return false If the device don't have some queue family that fits the requeriments
	 * 
	 * @see checkQueueSuitability( VkPhysicalDevice& p_device, VkQueueFamilyProperties& p_queueFamily, uint32_t p_id )
	 */
	bool
	checkQueues( VkPhysicalDevice& p_phDevice ) noexcept;

	/**
	 * @brief Checks if the device supports the swapcgain requeriments
	 * 
	 * Right now just checks if it has some format and present mode available to use 
	 * 
	 * @param p_phDevice Physical device to check the swapchain support
	 * @return true If it supports the Swapchain requeriments
	 * @return false If it doesn't supports the Swapchain requeriments
	 */
	bool
	checkSwapchain( VkPhysicalDevice& p_phDevice ) noexcept;

	/**
	 * @brief Get the Swapchain Support Details object form the physical device
	 * 
	 * @param p_phDevice Physical device to get the support info from
	 */
	void
	getSwapchainSupportDetails( VkPhysicalDevice& p_phDevice ) noexcept;

};