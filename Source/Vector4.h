//
//  Vector4.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Vector4_h
#define Vector4_h

#include <iostream>
#include <cmath>

namespace Degas {
    class Vector4 {
    public:
        Vector4()
        : m_x(0.0)
        , m_y(0.0)
        , m_z(0.0)
        , m_w(0.0)
        {
        }
        Vector4(double value)
        {
            setVector(value, value, value, value);
        }
        Vector4(double x, double y, double z, double w)
        {
            setVector(x, y, z, w);
        }
        Vector4(const Vector4& v) { *this = v; }
        
        void setVector(double x, double y, double z, double w)
        {
            m_x = x;
            m_y = y;
            m_z = z;
            m_w = w;
        }
        
        double norm() const { return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w); }
        double normSq() const { return (m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w); }
        
        Vector4& normalize() 
        {
            double normInv = 1.0 / norm();
            (*this) *= normInv;
            return *this;
        }
        
        Vector4 normalized() const
        {
            return Vector4(*this).normalize();
        }
        
        double dot(const Vector4 &v) const { return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z; }
        
        Vector4& operator+=(const Vector4& rhs)
        {
            m_x += rhs.m_x;
            m_y += rhs.m_y;
            m_z += rhs.m_z;
            m_w += rhs.m_w;
            return *this;
        }
        
        Vector4& operator-=(const Vector4& rhs)
        {
            m_x -= rhs.m_x;
            m_y -= rhs.m_y;
            m_z -= rhs.m_z;
            m_w -= rhs.m_w;
            return *this;
        }
        
        Vector4& operator*=(const Vector4& rhs)
        {
            m_x *= rhs.m_x;
            m_y *= rhs.m_y;
            m_z *= rhs.m_z;
            m_w *= rhs.m_w;
            return *this;
        }
        
        Vector4& operator*=(const double rhs)
        {
            m_x *= rhs;
            m_y *= rhs;
            m_z *= rhs;
            m_w *= rhs;
            return *this;
        }
        
        Vector4& operator/=(const Vector4& rhs)
        {
            m_x /= rhs.m_x;
            m_y /= rhs.m_y;
            m_z /= rhs.m_z;
            m_w /= rhs.m_w;
            return *this;
        }
        
        Vector4& operator/=(const double rhs)
        {
            m_x /= rhs;
            m_y /= rhs;
            m_z /= rhs;
            m_w /= rhs;
            return *this;
        }
        
        bool operator==(const Vector4& other) const
        {
            return (m_x == other.m_x && 
                    m_y == other.m_y && 
                    m_z == other.m_z &&
                    m_w == other.m_w);
        }
        
        bool operator!=(const Vector4& other) const { return !(*this == other); }
        
        double x() const { return m_x; }
        double y() const { return m_y; }
        double z() const { return m_z; }
        double w() const { return m_w; }
        
        void setX(const double x) { m_x = x; }
        void setY(const double y) { m_y = y; }
        void setZ(const double z) { m_z = z; }
        void setW(const double w) { m_w = w; }
        
    private:
        double m_x;
        double m_y;
        double m_z;
        double m_w;
    };
    
    inline Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs) += rhs;
    }
    
    inline Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs) -= rhs;
    }
    
    inline Vector4 operator*(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs) *= rhs;
    }
    
    inline Vector4 operator*(const Vector4& lhs, double rhs)
    {
        return Vector4(lhs) *= rhs;
    }
    
    inline Vector4 operator/(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs) /= rhs;
    }
    
    inline Vector4 operator/(const Vector4& lhs, double rhs)
    {
        return Vector4(lhs) /= rhs;
    }
    
    std::ostream& operator<<(std::ostream& out, const Vector4& v);
}

#endif // Vector4_h
