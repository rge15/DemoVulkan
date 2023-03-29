#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/Driver/DeviceMng.hpp>
#include <Engine/Driver/InstanceMng.hpp>
#include <Engine/Driver/SurfaceMng.hpp>
#include <Engine/Driver/SwapchainMng.hpp>
#include <Engine/Driver/WindowMng.hpp>

class Driver
{
private:
    UniqPtr<InstanceMng>    instanceMng_   { nullptr };
    UniqPtr<WindowMng>      windowMng_     { nullptr };
    UniqPtr<SurfaceMng>     surfaceMng_    { nullptr };
    UniqPtr<DeviceMng>      deviceMng_     { nullptr };
    UniqPtr<SwapchainMng>   swapchainMng_  { nullptr };

public:
    explicit Driver();
    ~Driver() = default;

    inline InstanceMng& getInstanceManager() { return *instanceMng_.get(); };
    
    inline DeviceMng& getDeviceManager() { return *deviceMng_.get(); };
    
    inline WindowMng& getWindowManager() { return *windowMng_.get(); };
    
    inline SurfaceMng& getSurfaceManager() { return *surfaceMng_.get(); };
    
    inline SwapchainMng& getSwapchainManager() { return *swapchainMng_.get(); };
};