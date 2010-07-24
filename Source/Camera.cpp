//
//  Camera.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Camera.h"

namespace Degas {
    Ray Camera::viewRay(double x, double y)
    {
        double viewingPortY = m_tanHalfFOV * y;
        double viewingPortX = m_tanHalfFOV * m_aspect * x;
        Vector3 viewRayV(viewingPortX, viewingPortY, 1.0);
        viewRayV = m_xAxis * viewRayV.x() + m_yAxis * viewRayV.y() + m_zAxis * viewRayV.z();
        Ray viewRay(m_eye, viewRayV.normalize());
        return viewRay;
    }
}
