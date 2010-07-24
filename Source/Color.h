//
//  Color.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Color_h
#define Color_h

#include <iostream>

namespace Degas {
    class Color {
    public:
        Color()
        : m_red(0.0)
        , m_green(0.0)
        , m_blue(0.0)
        {}
        Color(double level)
        : m_red(level)
        , m_green(level)
        , m_blue(level)
        {}
        Color(double red, double green, double blue)
        : m_red(red)
        , m_green(green)
        , m_blue(blue)
        {}
        
        double luminance() { return 0.2126 * m_red + 0.7152 * m_green + 0.0722 * m_blue; }
        
        void setRGB(double red, double green, double blue) { m_red = red; m_green = green; m_blue = blue; }
        
        Color clip()
        {
            m_red = m_red > 1.0 ? 1.0 :
                    m_red < 0.0 ? 0.0 :
                    m_red;
            m_green = m_green > 1.0 ? 1.0 :
                      m_green < 0.0 ? 0.0 :
                      m_green;
            m_blue = m_blue > 1.0 ? 1.0 :
                     m_blue < 0.0 ? 0.0 :
                     m_blue;
            return *this;
        }
        Color clipped() const
        {
            return Color(*this).clip();
        }
        
        int operator==(const Color& other) const
        {
            return m_red == other.m_red && m_green == other.m_green && m_blue == other.m_blue;
        }
        
        bool operator!=(const Color& other) const { return !(*this == other); }
        
        double red() const { return m_red; }
        double green() const { return m_green; }
        double blue() const { return m_blue; }
        void setRed(double red) { m_red = red; }
        void setGreen(double green) { m_green = green; }
        void setBlue(double blue) { m_blue = blue; }
        
    private:
        double m_red;
        double m_green;
        double m_blue;
    };
    
    
    
    std::ostream& operator<<(std::ostream& out, const Color& c);
    
    const Color kColorBlack   = Color(0.0, 0.0, 0.0);
    const Color kColorGray    = Color(0.5, 0.5, 0.5);
    const Color kColorWhite   = Color(1.0, 1.0, 1.0);
    const Color kColorRed     = Color(1.0, 0.0, 0.0);
    const Color kColorGreen   = Color(0.0, 1.0, 0.0);
    const Color kColorBlue    = Color(0.0, 0.0, 1.0);
    const Color kColorCyan    = Color(0.0, 1.0, 1.0);
    const Color kColorYellow  = Color(1.0, 1.0, 0.0);
    const Color kColorMagenta = Color(1.0, 0.0, 1.0);
}

#endif // Color_h
