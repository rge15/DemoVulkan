#include "Driver.hpp"


Driver::Driver()
{
    windowMng_      = std::make_unique<WindowMng>();
    instanceMng_    = std::make_unique<InstanceMng>();

    auto&   instance    = instanceMng_.get()->vkInstance_;
    auto&   window      = windowMng_.get()->getWindow();

    surfaceMng_     = std::make_unique<SurfaceMng>(instance, window);
    
    auto& surface    = surfaceMng_.get()->getSurface();

    deviceMng_  = std::make_unique<DeviceMng>(instance, surface);
    
    auto& device         = deviceMng_.get()->getDevice();
    auto& swapDetails    = deviceMng_.get()->getSwapchainDetails();
    auto& queueIds       = deviceMng_.get()->getFamilyQueueIds();


    swapchainMng_   = std::make_unique<SwapchainMng>(device, surface, swapDetails, queueIds);

}