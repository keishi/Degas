//
//  Camera.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Ray.h"

namespace Degas {
    class Camera {
    public:
        double aspect() const { return m_aspect; }
        void setAspect(double aspect) { m_aspect = aspect; }
        
        const Vector3& eye() const { return m_eye; }
        void setEye(const Vector3& pos) 
        {
            m_eye = pos;
            m_zAxis = (m_lookat - m_eye).normalized();
            m_xAxis = m_yAxis.cross(m_zAxis).normalize();
        }
        
        const Vector3& lookat() const { return m_lookat; }
        void setLookat(const Vector3& v)
        {
            m_lookat = v;
            m_zAxis = (m_lookat - m_eye).normalized();
            m_xAxis = m_yAxis.cross(m_zAxis).normalize();
        }
        
        const Vector3& up() const { return m_yAxis; }
        void setUp(const Vector3& v) 
        {
            m_yAxis = v.normalized();
            m_xAxis = m_yAxis.cross(m_zAxis).normalize();
        }
        
        const Vector3& xAxis() const { return m_xAxis; }
        const Vector3& yAxis() const { return m_yAxis; }
        const Vector3& zAxis() const { return m_zAxis; }
        
        double FOV() const { return m_FOV; }
        void setFOV(double angle) { m_FOV = angle; m_tanHalfFOV = tan(m_FOV / 2.0); }
        
        Ray viewRay(double x, double y);
        
    private:
        double m_aspect; // viewport aspect ratio ( = width / height)
        Vector3 m_eye;
        Vector3 m_lookat;
        Vector3 m_xAxis;
        Vector3 m_yAxis;
        Vector3 m_zAxis;
        double m_FOV; // Angle in the y direction that is visible.
        double m_tanHalfFOV;
    };
}

#endif // Camera_h
