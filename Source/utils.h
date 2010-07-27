//
//  utils.h
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <cmath>

const double kSmallValue = 0.00001;

inline double rad2deg(double rad)
{
    return (180.0 * rad / M_PI);
}

inline double deg2rad(double deg)
{
    return (M_PI * deg / 180.0);
}

inline double min(double a, double b)
{
    return a < b ? a : b;
}

inline double max(double a, double b)
{
    return a > b ? a : b;
}

#endif // utils_h