#include "DeviceQueueFamilies.hpp"

void
DeviceQueueFamilies::reset() noexcept
{
    _graphicQueueId.reset();
    _presentQueueId.reset();
}