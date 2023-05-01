#pragma once
#include <utilities/typeAliases.hpp>

/**
 * @brief Struct for managing the Device Queues Ids
 */
struct DeviceQueueFamilies
{
    //! Optional value with the Device Graphic Queue Id
    Optional<uint32_t> _graphicQueueId;
    //! Optional value with the Device Present Queue Id
    Optional<uint32_t> _presentQueueId;

    /**
     * @brief Method that resets the optional values of the struct
     */
    void reset() noexcept;
};