#pragma once
#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class InstanceMng
{
public:
	VkInstance	_vkInstance {VK_NULL_HANDLE};

private:    
	VkInstanceCreateInfo    _instanceInfo {};
    VkApplicationInfo		_appInfo {};

    const Vector<const char*> _validationLayers = 
    {
        "VK_LAYER_KHRONOS_validation"
    };

public:
    InstanceMng(
		const char* p_appName = "App", const char* p_engineName = "Engine",
		const uint32_t p_appVersion = 1, const uint32_t p_engineVersion = 1
	) noexcept;

    ~InstanceMng() noexcept;

private:
	void
	fillInstanceInfo() noexcept;

	void
	createInstance() noexcept;

	void
	checkLayer() noexcept;

};