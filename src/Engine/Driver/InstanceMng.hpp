#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

/**
 * @brief Class for Vulkan INstance creation and management
 */
class InstanceMng
{
public:
	//! Vulkan Instance handler
	VkInstance	vkInstance_ {VK_NULL_HANDLE};

private:
	//! Vulkan Instance creation info struct
	VkInstanceCreateInfo    instanceInfo_ {};
	//! Application info struct
    VkApplicationInfo		appInfo_ {};

	//! Vector with all the layers that the Vulkan Instance have to support
    const Vector<const char*> _validationLayers = 
    {
        "VK_LAYER_KHRONOS_validation"
    };

public:
	/**
	 * @brief Construct a new Instance Mng object
	 * 
	 * @param p_appName Application name
	 * @param p_engineName Engine name
	 * @param p_appVersion Version of the App
	 * @param p_engineVersion Version of the Engine
	 */
    InstanceMng(
		const char* p_appName = "App", const char* p_engineName = "Engine",
		const uint32_t p_appVersion = 1, const uint32_t p_engineVersion = 1
	) noexcept;

	/**
	 * @brief Destroy the Instance Mng object and his Vulkan Instance Handler
	 */
    ~InstanceMng() noexcept;

private:
	/**
	 * @brief Fills all the instance creation info structure
	 */
	void
	fillInstanceInfo() noexcept;

	/**
	 * @brief Create the Vulkan Instance Obj
	 */
	void
	createInstance() noexcept;

	/**
	 * @brief Checks if the Instance supports the required layers
	 */
	void
	checkLayer() noexcept;

};