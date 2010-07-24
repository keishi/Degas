//
//  Ray.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Ray_h
#define Ray_h

#include "Vector3.h"

namespace Degas {
    class Ray {
    public:
        Ray() { }
        Ray(const Vector3& origin, const Vector3& direction);
        
        const Vector3& origin() const { return m_origin; }
        const Vector3& direction() const { return m_direction; }
        
        Vector3 pointAtDistance(double distance) const { return m_origin + m_direction * distance; }
        
    private:
        Vector3 m_origin;
        Vector3 m_direction;
    };
    
    std::ostream& operator<<(std::ostream& out, const Ray& a);
}

#endif
