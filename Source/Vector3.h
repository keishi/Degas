//
//  Vector3.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Vector3_h
#define Vector3_h

#include <iostream>
#include <cmath>

namespace Degas {
    class Vector3 {
    public:
        Vector3()
        : m_x(0.0)
        , m_y(0.0)
        , m_z(0.0)
        {
        }
        Vector3(double value)
        {
            setVector(value, value, value);
        }
        Vector3(double x, double y, double z)
        {
            setVector(x, y, z);
        }
        Vector3(const Vector3& v) { *this = v; }
        
        void setVector(double x, double y, double z)
        {
            m_x = x;
            m_y = y;
            m_z = z;
        }
        
        double norm() const { return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z); }
        double normSq() const { return (m_x * m_x + m_y * m_y + m_z * m_z); }
        
        Vector3& normalize() 
        {
            double normInv = 1.0 / norm();
            (*this) *= normInv;
            return *this;
        }
        
        Vector3 normalized() const
        {
            return Vector3(*this).normalize();
        }
        
        double dot(const Vector3 &v) const { return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z; }
        Vector3 cross(const Vector3 &v) const
        {
            return Vector3(m_y * v.m_z - m_z * v.m_y,
                           m_z * v.m_x - m_x * v.m_z,
                           m_x * v.m_y - m_y * v.m_x);
        }
        
        Vector3 operator-() const { return Vector3(-m_x, -m_y, -m_z); }
        
        Vector3& operator+=(const Vector3& rhs)
        {
            m_x += rhs.m_x;
            m_y += rhs.m_y;
            m_z += rhs.m_z;
            return *this;
        }
        
        Vector3& operator-=(const Vector3& rhs)
        {
            m_x -= rhs.m_x;
            m_y -= rhs.m_y;
            m_z -= rhs.m_z;
            return *this;
        }
        
        Vector3& operator*=(const Vector3& rhs)
        {
            m_x *= rhs.m_x;
            m_y *= rhs.m_y;
            m_z *= rhs.m_z;
            return *this;
        }
        
        Vector3& operator*=(const double rhs)
        {
            m_x *= rhs;
            m_y *= rhs;
            m_z *= rhs;
            return *this;
        }
        
        Vector3& operator/=(const Vector3& rhs)
        {
            m_x /= rhs.m_x;
            m_y /= rhs.m_y;
            m_z /= rhs.m_z;
            return *this;
        }
        
        Vector3& operator/=(const double rhs)
        {
            m_x /= rhs;
            m_y /= rhs;
            m_z /= rhs;
            return *this;
        }
        
        bool operator==(const Vector3& other) const
        {
            return (m_x == other.m_x && 
                    m_y == other.m_y && 
                    m_z == other.m_z);
        }
        
        bool operator!=(const Vector3& other) const { return !(*this == other); }
        
        double x() const { return m_x; }
        double y() const { return m_y; }
        double z() const { return m_z; }
        
        void setX(const double x) { m_x = x; }
        void setY(const double y) { m_y = y; }
        void setZ(const double z) { m_z = z; }
        
    private:
        double m_x;
        double m_y;
        double m_z;
    };
    
    inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs) += rhs;
    }
    
    inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs) -= rhs;
    }
    
    inline Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs) *= rhs;
    }
    
    inline Vector3 operator*(const Vector3& lhs, double rhs)
    {
        return Vector3(lhs) *= rhs;
    }
    
    inline Vector3 operator/(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs) /= rhs;
    }
    
    inline Vector3 operator/(const Vector3& lhs, double rhs)
    {
        return Vector3(lhs) /= rhs;
    }
    
    std::ostream& operator<<(std::ostream& out, const Vector3& v);
}

#endif // Vector3_h
