//
//  Image.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Image_h
#define Image_h

#include <cmath>

#include "Color.h"

namespace Degas {
    typedef struct {
        unsigned char r, g, b;
    } Pixel;
    
    class Image {
    public:
        Image()
        : m_width(0)
        , m_height(0)
        , m_pixels(0)
        {}
        Image(unsigned int width, unsigned int height);
        virtual ~Image();
        
        void resize(unsigned int width, unsigned int height);
        
        const unsigned int width() const { return m_width; }
        const unsigned int height() const { return m_height; }
        const unsigned int pixelCount() const { return m_width * m_height; }
        
        void drawImageAtPoint(Image* image, int x, int y);
        
        Pixel pixelAt(int x, int y) const
        {
            return m_pixels[x + y * m_width];
        }
        Color pixelColorAt(int x, int y) const
        {
            if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
                return kColorBlack;
            }
            Pixel p = pixelAt(x, y);
            return Color(p.r / 255.0f, p.g / 255.0f, p.b / 255.0f);
        }
        Color sampleColorAt(double x, double y) const
        {
            // TODO: Implement bilinear interpolation
            return pixelColorAt(round(x), round(y));
        }
        
        void setPixel(int x, int y, const Pixel& p) {
            if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
                std::cerr << "ERR: Image::setPixel out of bounds." << std::endl;
                std::cerr << "Tried to set " << x << ", " << y << "." << std::endl;
                return;
            }
            m_pixels[x + y * m_width] = p; }
        void setPixelColor(int x, int y, const Color& c)
        {
            if (!(x >= 0 && x < m_width && y >= 0 && y < m_height)) {
                return;
            }
            Color d = c.clipped();
            Pixel p = {d.red() * 255, d.green() * 255, d.blue() * 255};
            m_pixels[x + y * m_width] = p;
        }
        
        void thresholdFilter(double th);
        bool equalsImage(Image* i);
        
        void loadBMPFile(const char *filename);
        void writeBMPFile(const char *filename) const;
        
    private:
        unsigned int m_width;
        unsigned int m_height;
        Pixel* m_pixels;
    };
    
    std::ostream& operator<<(std::ostream& out, const Image& image);
}

#endif // Image_h
