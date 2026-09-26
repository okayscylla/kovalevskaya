#pragma once

#define assertEqual(i, j)           (std::fabs((i) - (j)) < EPSILON)
#define notZero(i)                  (std::fabs(i) > EPSILON)
#define klog(...)                   (std::print("KOV: " __VA_ARGS__))