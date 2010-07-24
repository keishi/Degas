//
//  Ray.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Ray.h"

namespace Degas {
    
    Ray::Ray(const Vector3& origin, const Vector3& direction)
    {
        m_origin = origin;
        m_direction = direction.normalized();
    }
    
    std::ostream& operator<<(std::ostream& out, const Ray& a)
    {
        out << "Ray(origin:";
        out << a.origin();
        out << ", direction:";
        out << a.direction();
        out << ")";
        return out;
    }
    
}
