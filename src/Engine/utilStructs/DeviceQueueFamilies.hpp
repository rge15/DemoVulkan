#pragma once
#include <utilities/typeAliases.hpp>

struct DeviceQueueFamilies
{
    Optional<uint32_t> _graphicQueueId;
    Optional<uint32_t> _presentQueueId;

    void reset() noexcept;
};