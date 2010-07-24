//
//  Matrix4.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Matrix4_h
#define Matrix4_h

#include <cstring>

#include "Vector4.h"

namespace Degas {
    class Matrix4 {
    public:
        Matrix4() { makeIdentity(); }
        Matrix4(const Matrix4& m) { *this = m; }
        Matrix4(double m11, double m12, double m13, double m14,
                double m21, double m22, double m23, double m24,
                double m31, double m32, double m33, double m34,
                double m41, double m42, double m43, double m44)
        {
            setMatrix(m11, m12, m13, m14, 
                      m21, m22, m23, m24, 
                      m31, m32, m33, m34, 
                      m41, m42, m43, m44);
        }
        
        void setMatrix(double m11, double m12, double m13, double m14,
                       double m21, double m22, double m23, double m24,
                       double m31, double m32, double m33, double m34,
                       double m41, double m42, double m43, double m44)
        {
            m_matrix[0][0] = m11; m_matrix[0][1] = m12; m_matrix[0][2] = m13; m_matrix[0][3] = m14; 
            m_matrix[1][0] = m21; m_matrix[1][1] = m22; m_matrix[1][2] = m23; m_matrix[1][3] = m24; 
            m_matrix[2][0] = m31; m_matrix[2][1] = m32; m_matrix[2][2] = m33; m_matrix[2][3] = m34; 
            m_matrix[3][0] = m41; m_matrix[3][1] = m42; m_matrix[3][2] = m43; m_matrix[3][3] = m44;
        }
        
        void setMatrix(const Matrix4& m)
        {
            memcpy(m_matrix, m.m_matrix, sizeof(m_matrix));
        }
        
        Matrix4& makeIdentity()
        {
            setMatrix(1, 0, 0, 0, 
                      0, 1, 0, 0, 
                      0, 0, 1, 0, 
                      0, 0, 0, 1);
            return *this;
        }
        
        bool isIdentity() const
        {
            return m_matrix[0][0] == 1 && m_matrix[0][1] == 0 && m_matrix[0][2] == 0 && m_matrix[0][3] == 0 &&
                   m_matrix[1][0] == 0 && m_matrix[1][1] == 1 && m_matrix[1][2] == 0 && m_matrix[1][3] == 0 &&
                   m_matrix[2][0] == 0 && m_matrix[2][1] == 0 && m_matrix[2][2] == 1 && m_matrix[2][3] == 0 &&
                   m_matrix[3][0] == 0 && m_matrix[3][1] == 0 && m_matrix[3][2] == 0 && m_matrix[3][3] == 1;
        }
        
        void transpose()
        {
            double tmp;
            tmp = m_matrix[0][1]; m_matrix[0][1] = m_matrix[1][0]; m_matrix[1][0] = tmp;
            tmp = m_matrix[0][2]; m_matrix[0][2] = m_matrix[2][0]; m_matrix[2][0] = tmp;
            tmp = m_matrix[0][3]; m_matrix[0][3] = m_matrix[3][0]; m_matrix[3][0] = tmp;
            tmp = m_matrix[1][2]; m_matrix[1][2] = m_matrix[2][1]; m_matrix[2][1] = tmp;
            tmp = m_matrix[1][3]; m_matrix[1][3] = m_matrix[3][1]; m_matrix[3][1] = tmp;
            tmp = m_matrix[2][3]; m_matrix[2][3] = m_matrix[3][2]; m_matrix[3][2] = tmp;
        }
        
        bool isAffine() const
        {
            return (m13() == 0 && m14() == 0 && m23() == 0 && m24() == 0 && 
                    m31() == 0 && m32() == 0 && m33() == 1 && m34() == 0 && 
                    m43() == 0 && m44() == 1);
        }
        
        bool isInvertible() const;
        Matrix4 inverse() const;
        
        double m11() const { return m_matrix[0][0]; }
        void setM11(double f) { m_matrix[0][0] = f; }
        double m12() const { return m_matrix[0][1]; }
        void setM12(double f) { m_matrix[0][1] = f; }
        double m13() const { return m_matrix[0][2]; }
        void setM13(double f) { m_matrix[0][2] = f; }
        double m14() const { return m_matrix[0][3]; }
        void setM14(double f) { m_matrix[0][3] = f; }
        double m21() const { return m_matrix[1][0]; }
        void setM21(double f) { m_matrix[1][0] = f; }
        double m22() const { return m_matrix[1][1]; }
        void setM22(double f) { m_matrix[1][1] = f; }
        double m23() const { return m_matrix[1][2]; }
        void setM23(double f) { m_matrix[1][2] = f; }
        double m24() const { return m_matrix[1][3]; }
        void setM24(double f) { m_matrix[1][3] = f; }
        double m31() const { return m_matrix[2][0]; }
        void setM31(double f) { m_matrix[2][0] = f; }
        double m32() const { return m_matrix[2][1]; }
        void setM32(double f) { m_matrix[2][1] = f; }
        double m33() const { return m_matrix[2][2]; }
        void setM33(double f) { m_matrix[2][2] = f; }
        double m34() const { return m_matrix[2][3]; }
        void setM34(double f) { m_matrix[2][3] = f; }
        double m41() const { return m_matrix[3][0]; }
        void setM41(double f) { m_matrix[3][0] = f; }
        double m42() const { return m_matrix[3][1]; }
        void setM42(double f) { m_matrix[3][1] = f; }
        double m43() const { return m_matrix[3][2]; }
        void setM43(double f) { m_matrix[3][2] = f; }
        double m44() const { return m_matrix[3][3]; }
        void setM44(double f) { m_matrix[3][3] = f; }
        
        bool operator==(const Matrix4& other) const
        {
            return (m_matrix[0][0] == other.m_matrix[0][0] &&
                    m_matrix[0][1] == other.m_matrix[0][1] &&
                    m_matrix[0][2] == other.m_matrix[0][2] &&
                    m_matrix[0][3] == other.m_matrix[0][3] &&
                    m_matrix[1][0] == other.m_matrix[1][0] &&
                    m_matrix[1][1] == other.m_matrix[1][1] &&
                    m_matrix[1][2] == other.m_matrix[1][2] &&
                    m_matrix[1][3] == other.m_matrix[1][3] &&
                    m_matrix[2][0] == other.m_matrix[2][0] &&
                    m_matrix[2][1] == other.m_matrix[2][1] &&
                    m_matrix[2][2] == other.m_matrix[2][2] &&
                    m_matrix[2][3] == other.m_matrix[2][3] &&
                    m_matrix[3][0] == other.m_matrix[3][0] &&
                    m_matrix[3][1] == other.m_matrix[3][1] &&
                    m_matrix[3][2] == other.m_matrix[3][2] &&
                    m_matrix[3][3] == other.m_matrix[3][3]);
        }
        
        bool operator!=(const Matrix4& other) const { return !(*this == other); }
        
        Matrix4& operator+=(const Matrix4& rhs)
        {
            m_matrix[0][0] += rhs.m_matrix[0][0];
            m_matrix[0][1] += rhs.m_matrix[0][1];
            m_matrix[0][2] += rhs.m_matrix[0][2];
            m_matrix[0][3] += rhs.m_matrix[0][3];
            m_matrix[1][0] += rhs.m_matrix[1][0];
            m_matrix[1][1] += rhs.m_matrix[1][1];
            m_matrix[1][2] += rhs.m_matrix[1][2];
            m_matrix[1][3] += rhs.m_matrix[1][3];
            m_matrix[2][0] += rhs.m_matrix[2][0];
            m_matrix[2][1] += rhs.m_matrix[2][1];
            m_matrix[2][2] += rhs.m_matrix[2][2];
            m_matrix[2][3] += rhs.m_matrix[2][3];
            m_matrix[3][0] += rhs.m_matrix[3][0];
            m_matrix[3][1] += rhs.m_matrix[3][1];
            m_matrix[3][2] += rhs.m_matrix[3][2];
            m_matrix[3][3] += rhs.m_matrix[3][3];
            
            return *this;
        }
        
        Matrix4& operator-=(const Matrix4& rhs)
        {
            m_matrix[0][0] -= rhs.m_matrix[0][0];
            m_matrix[0][1] -= rhs.m_matrix[0][1];
            m_matrix[0][2] -= rhs.m_matrix[0][2];
            m_matrix[0][3] -= rhs.m_matrix[0][3];
            m_matrix[1][0] -= rhs.m_matrix[1][0];
            m_matrix[1][1] -= rhs.m_matrix[1][1];
            m_matrix[1][2] -= rhs.m_matrix[1][2];
            m_matrix[1][3] -= rhs.m_matrix[1][3];
            m_matrix[2][0] -= rhs.m_matrix[2][0];
            m_matrix[2][1] -= rhs.m_matrix[2][1];
            m_matrix[2][2] -= rhs.m_matrix[2][2];
            m_matrix[2][3] -= rhs.m_matrix[2][3];
            m_matrix[3][0] -= rhs.m_matrix[3][0];
            m_matrix[3][1] -= rhs.m_matrix[3][1];
            m_matrix[3][2] -= rhs.m_matrix[3][2];
            m_matrix[3][3] -= rhs.m_matrix[3][3];
            
            return *this;
        }
        
        Matrix4& operator*=(double rhs)
        {
            m_matrix[0][0] -= rhs;
            m_matrix[0][1] -= rhs;
            m_matrix[0][2] -= rhs;
            m_matrix[0][3] -= rhs;
            m_matrix[1][0] -= rhs;
            m_matrix[1][1] -= rhs;
            m_matrix[1][2] -= rhs;
            m_matrix[1][3] -= rhs;
            m_matrix[2][0] -= rhs;
            m_matrix[2][1] -= rhs;
            m_matrix[2][2] -= rhs;
            m_matrix[2][3] -= rhs;
            m_matrix[3][0] -= rhs;
            m_matrix[3][1] -= rhs;
            m_matrix[3][2] -= rhs;
            m_matrix[3][3] -= rhs;
            
            return *this;
        }
        
        Matrix4& operator/=(double rhs)
        {
            double rhsInv = 1.0 / rhs;
            *this *= rhsInv;
            return *this;
        }
        
        Matrix4& operator*=(const Matrix4& rhs)
        {
            Matrix4 tmp;

            tmp.m_matrix[0][0] = (m_matrix[0][0] * rhs.m_matrix[0][0] + m_matrix[0][1] * rhs.m_matrix[1][0]
                                + m_matrix[0][2] * rhs.m_matrix[2][0] + m_matrix[0][3] * rhs.m_matrix[3][0]);
            tmp.m_matrix[0][1] = (m_matrix[0][0] * rhs.m_matrix[0][1] + m_matrix[0][1] * rhs.m_matrix[1][1]
                                + m_matrix[0][2] * rhs.m_matrix[2][1] + m_matrix[0][3] * rhs.m_matrix[3][1]);
            tmp.m_matrix[0][2] = (m_matrix[0][0] * rhs.m_matrix[0][2] + m_matrix[0][1] * rhs.m_matrix[1][2]
                                + m_matrix[0][2] * rhs.m_matrix[2][2] + m_matrix[0][3] * rhs.m_matrix[3][2]);
            tmp.m_matrix[0][3] = (m_matrix[0][0] * rhs.m_matrix[0][3] + m_matrix[0][1] * rhs.m_matrix[1][3]
                                + m_matrix[0][2] * rhs.m_matrix[2][3] + m_matrix[0][3] * rhs.m_matrix[3][3]);

            tmp.m_matrix[1][0] = (m_matrix[1][0] * rhs.m_matrix[0][0] + m_matrix[1][1] * rhs.m_matrix[1][0]
                                + m_matrix[1][2] * rhs.m_matrix[2][0] + m_matrix[1][3] * rhs.m_matrix[3][0]);
            tmp.m_matrix[1][1] = (m_matrix[1][0] * rhs.m_matrix[0][1] + m_matrix[1][1] * rhs.m_matrix[1][1]
                                + m_matrix[1][2] * rhs.m_matrix[2][1] + m_matrix[1][3] * rhs.m_matrix[3][1]);
            tmp.m_matrix[1][2] = (m_matrix[1][0] * rhs.m_matrix[0][2] + m_matrix[1][1] * rhs.m_matrix[1][2]
                                + m_matrix[1][2] * rhs.m_matrix[2][2] + m_matrix[1][3] * rhs.m_matrix[3][2]);
            tmp.m_matrix[1][3] = (m_matrix[1][0] * rhs.m_matrix[0][3] + m_matrix[1][1] * rhs.m_matrix[1][3]
                                + m_matrix[1][2] * rhs.m_matrix[2][3] + m_matrix[1][3] * rhs.m_matrix[3][3]);

            tmp.m_matrix[2][0] = (m_matrix[2][0] * rhs.m_matrix[0][0] + m_matrix[2][1] * rhs.m_matrix[1][0]
                                + m_matrix[2][2] * rhs.m_matrix[2][0] + m_matrix[2][3] * rhs.m_matrix[3][0]);
            tmp.m_matrix[2][1] = (m_matrix[2][0] * rhs.m_matrix[0][1] + m_matrix[2][1] * rhs.m_matrix[1][1]
                                + m_matrix[2][2] * rhs.m_matrix[2][1] + m_matrix[2][3] * rhs.m_matrix[3][1]);
            tmp.m_matrix[2][2] = (m_matrix[2][0] * rhs.m_matrix[0][2] + m_matrix[2][1] * rhs.m_matrix[1][2]
                                + m_matrix[2][2] * rhs.m_matrix[2][2] + m_matrix[2][3] * rhs.m_matrix[3][2]);
            tmp.m_matrix[2][3] = (m_matrix[2][0] * rhs.m_matrix[0][3] + m_matrix[2][1] * rhs.m_matrix[1][3]
                                + m_matrix[2][2] * rhs.m_matrix[2][3] + m_matrix[2][3] * rhs.m_matrix[3][3]);

            tmp.m_matrix[3][0] = (m_matrix[3][0] * rhs.m_matrix[0][0] + m_matrix[3][1] * rhs.m_matrix[1][0]
                                + m_matrix[3][2] * rhs.m_matrix[2][0] + m_matrix[3][3] * rhs.m_matrix[3][0]);
            tmp.m_matrix[3][1] = (m_matrix[3][0] * rhs.m_matrix[0][1] + m_matrix[3][1] * rhs.m_matrix[1][1]
                                + m_matrix[3][2] * rhs.m_matrix[2][1] + m_matrix[3][3] * rhs.m_matrix[3][1]);
            tmp.m_matrix[3][2] = (m_matrix[3][0] * rhs.m_matrix[0][2] + m_matrix[3][1] * rhs.m_matrix[1][2]
                                + m_matrix[3][2] * rhs.m_matrix[2][2] + m_matrix[3][3] * rhs.m_matrix[3][2]);
            tmp.m_matrix[3][3] = (m_matrix[3][0] * rhs.m_matrix[0][3] + m_matrix[3][1] * rhs.m_matrix[1][3]
                                + m_matrix[3][2] * rhs.m_matrix[2][3] + m_matrix[3][3] * rhs.m_matrix[3][3]);

            setMatrix(tmp);
            return *this;
        }
        
        inline Matrix4 operator-()
        {
            return Matrix4(m_matrix[0][0], m_matrix[0][1], m_matrix[0][2], m_matrix[0][3],
                           m_matrix[1][0], m_matrix[1][1], m_matrix[1][2], m_matrix[1][3],
                           m_matrix[2][0], m_matrix[2][1], m_matrix[2][2], m_matrix[2][3],
                           m_matrix[3][0], m_matrix[3][1], m_matrix[3][2], m_matrix[3][3]);
        }
        
    private:
        double m_matrix[4][4];
    };
    
    inline Matrix4 operator+(const Matrix4& lhs, const Matrix4& rhs)
    {
        return Matrix4(lhs) += rhs;
    }
    
    inline Matrix4 operator-(const Matrix4& lhs, const Matrix4& rhs)
    {
        return Matrix4(lhs) -= rhs;
    }
    
    inline Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
    {
        return Matrix4(lhs) *= rhs;
    }
    
    inline Vector4 operator*(const Matrix4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs.m11() * rhs.x() + lhs.m12() * rhs.y() + lhs.m13() * rhs.z() + lhs.m14() * rhs.w(),
                       lhs.m21() * rhs.x() + lhs.m22() * rhs.y() + lhs.m23() * rhs.z() + lhs.m42() * rhs.w(),
                       lhs.m31() * rhs.x() + lhs.m32() * rhs.y() + lhs.m33() * rhs.z() + lhs.m43() * rhs.w(),
                       lhs.m41() * rhs.x() + lhs.m42() * rhs.y() + lhs.m43() * rhs.z() + lhs.m44() * rhs.w()); 
    }
    
    inline Matrix4 operator*(const Matrix4& lhs, double rhs)
    {
        return Matrix4(lhs) *= rhs;
    }
    
    inline Matrix4 operator/(const Matrix4& lhs, double rhs)
    {
        return Matrix4(lhs) /= rhs;
    }
    
    std::ostream& operator<<(std::ostream& out, const Matrix4& m);
}

#endif // Matrix4_h