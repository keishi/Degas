//
//  deg2rad.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef deg2rad_h
#define deg2rad_h

#ifndef M_PI
#define M_PI 3.141592653589793238462643
#endif

double d_rad2deg(double rad)
{
    return (180.0 * rad / M_PI);
}

double d_deg2rad(double deg)
{
    return (M_PI * deg / 180.0);
}

#endif // deg2rad_h
