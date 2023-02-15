#pragma once
#include <chrono>

using demoClock = std::chrono::high_resolution_clock;

using timePoint = std::chrono::time_point<demoClock>;