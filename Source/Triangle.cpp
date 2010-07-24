//
//  Triangle.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Triangle.h"

namespace Degas {
    
    const double kSmallValue = -0.000001;
    
    Triangle::Triangle(Vector3& v1, Vector3& v2, Vector3& v3)
    : m_v1(v1)
    , m_v2(v2)
    , m_v3(v3)
    , m_material(NULL)
    , m_isDoubleSided(true)
    {
        // clockwise
        Vector3 v12 = v2 - v1;
        Vector3 v13 = v3 - v1;
        m_normal = v13.cross(v12).normalize();
        
        // updateBoundingBox();
    }
    
    bool Triangle::hit(const Ray& ray, HitInfo *hitInfo)
    {
        //if (!m_boundingBox.doesHit(ray)) {
        //    return false;
        //}
        float vn = ray.direction().dot(m_normal);
        bool isRightSide = vn < 0;
        if (fabs(vn) < kSmallValue)
            return false;
        if (!isRightSide && !m_isDoubleSided) {
            return false;
        }
        Vector3 v0r = ray.origin() - m_v1;
        float xpn = m_normal.dot(v0r);
        float distance = -xpn / vn;
        if (distance < 0)
            return false;
        Vector3 hitPosition = ray.pointAtDistance(distance);
        
        Vector3 v1h = hitPosition - m_v1;
        Vector3 v12 = m_v2 - m_v1;
        Vector3 cross1 = v1h.cross(v12);
        if (cross1.dot(m_normal) < kSmallValue) {
            return false;
        }
        Vector3 v2h = hitPosition - m_v2;
        Vector3 v23 = m_v3 - m_v2;
        Vector3 cross2 = v2h.cross(v23);
        if (cross2.dot(m_normal) < kSmallValue) {
            return false;
        }
        Vector3 v3h = hitPosition - m_v3;
        Vector3 v31 = m_v1 - m_v3;
        Vector3 cross3 = v3h.cross(v31);
        if (cross3.dot(m_normal) < kSmallValue) {
            return false;
        }
        
        hitInfo->distance = distance;
        hitInfo->material = m_material;
        hitInfo->normal = m_normal;
        hitInfo->position = hitPosition;
        hitInfo->ray = ray;
        hitInfo->surface = this;
        return true;
    }
    void Triangle::drawGL()
    {
        //GLfloat diffuseColor[] = {m_material->color().red(), m_material->color().green(), m_material->color().blue(), 1.0};
        GLfloat diffuseColor[] = {0.0, 1.0, 0.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
        glBegin(GL_TRIANGLES);
        glNormal3dv((GLdouble*)&m_normal);
        glVertex3dv((GLdouble*)&m_v1);
        glVertex3dv((GLdouble*)&m_v2);
        glVertex3dv((GLdouble*)&m_v3);
        glEnd();
    }
    void Triangle::applyTransformation(const Matrix4& t)
    {
        //m_v1 = t.mapPoint(m_v1);
        //m_v2 = t.mapPoint(m_v2);
        //m_v3 = t.mapPoint(m_v3);
        // updateBoundingBox();
    }
}
