//
//  Material.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include "Color.h"

namespace Degas {
    class Material {
    public:
        Material()
        : m_color(kColorWhite)
        , m_ambient(Color(0.2f))
        , m_diffuse(Color(0.8f))
        , m_specular(Color(0.0f))
        , m_shininess(0.0f)
        , m_reflectivity(0.0f)
        , m_transparency(0.0f)
        , m_refractiveIndex(1.0f)
        {}
        
        const Color& color() const { return m_color; }
        const Color& diffuse() const { return m_diffuse; }
        const Color& ambient() const { return m_ambient; }
        const Color& specular() const { return m_specular; }
        float shininess() const { return m_shininess; }
        float reflectivity() const { return m_reflectivity; }
        float transparency() const { return m_transparency; }
        float refractiveIndex() const { return m_refractiveIndex; }
        
        void setColor(const Color& color) { m_color = color; }
        void setDiffuse(const Color& diffuse) { m_diffuse = diffuse; }
        void setAmbient(const Color& ambient) { m_ambient = ambient; }
        void setSpecular(const Color& specular) { m_specular = specular; }
        void setShininess(float shininess) { m_shininess = shininess; }
        void setReflectivity(float reflectivity) { m_reflectivity = reflectivity; }
        void setTransparency(float transparency) { m_transparency = transparency; }
        void setRefractiveIndex(float ri) { m_refractiveIndex = ri; }
        
    private:
        Color m_color;
        Color m_diffuse;
        Color m_ambient;
        Color m_specular;
        float m_shininess; // specular exponent
        float m_reflectivity;
        float m_transparency;
        float m_refractiveIndex;
    };
}

#endif
