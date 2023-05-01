#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/Driver/DeviceMng.hpp>
#include <Engine/Driver/InstanceMng.hpp>
#include <Engine/Driver/SurfaceMng.hpp>
#include <Engine/Driver/SwapchainMng.hpp>
#include <Engine/Driver/WindowMng.hpp>

/**
 * @brief Class that manages all the Vulkan use and driver conexion
 */
class Driver
{
private:
    //! Ptr Intance Mng
    UniqPtr<InstanceMng>    instanceMng_   { nullptr };
    //! Ptr Window Mng
    UniqPtr<WindowMng>      windowMng_     { nullptr };
    //! Ptr Surface Mng
    UniqPtr<SurfaceMng>     surfaceMng_    { nullptr };
    //! Ptr Device Mng
    UniqPtr<DeviceMng>      deviceMng_     { nullptr };
    //! Ptr Swapchain Mng
    UniqPtr<SwapchainMng>   swapchainMng_  { nullptr };

public:
    /**
     * @brief Construct a new Driver object and inits all the contining managers
     */
    explicit Driver();

    /**
     * @brief Destroy the Driver object
     */
    ~Driver() = default;

    /**
     * @brief Get the Instance Manager object
     * 
     * @return InstanceMng& 
     */
    inline InstanceMng& getInstanceManager() { return *instanceMng_.get(); };
    
    /**
     * @brief Get the Device Manager object
     * 
     * @return DeviceMng& 
     */
    inline DeviceMng& getDeviceManager() { return *deviceMng_.get(); };
    
    /**
     * @brief Get the Window Manager object
     * 
     * @return WindowMng& 
     */
    inline WindowMng& getWindowManager() { return *windowMng_.get(); };
    
    /**
     * @brief Get the Surface Manager object
     * 
     * @return SurfaceMng& 
     */
    inline SurfaceMng& getSurfaceManager() { return *surfaceMng_.get(); };
    
    /**
     * @brief Get the Swapchain Manager object
     * 
     * @return SwapchainMng& 
     */
    inline SwapchainMng& getSwapchainManager() { return *swapchainMng_.get(); };
};