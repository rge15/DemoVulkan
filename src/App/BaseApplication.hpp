#pragma once
#include <iostream>

struct BaseApplication
{
    BaseApplication() = default;
    ~BaseApplication() = default;

    virtual void run() = 0;
};