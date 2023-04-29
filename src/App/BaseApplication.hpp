#pragma once
#include <iostream>

/**
 * @brief BaseApplication is an base app class for developing entry app points for main
 */

struct BaseApplication
{
    /**
     * @brief Pure virtual interface method for apps to override and execute the app code
     */
    virtual void run() = 0;
};