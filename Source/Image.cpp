//
//  Image.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Image.h"

#include <fstream>
#include <cassert>
#include <OpenGL/OpenGL.h>

namespace Degas {
    Image::Image(unsigned int width, unsigned int height)
    : m_pixels(NULL)
    {
        resize(width, height);
    }
    
    Image::~Image()
    {
        if (m_pixels)
            delete [] m_pixels;
        m_pixels = NULL;
    }
    
    void Image::resize(unsigned int width, unsigned int height)
    {
        if (width == m_width && height == m_height)
            return;
        
        if (m_pixels) {
            delete [] m_pixels;
            m_pixels = NULL;
        }
        
        m_width = width;
        m_height = height;
        m_pixels = new Pixel[pixelCount()];
        memset(m_pixels, 0, pixelCount() * sizeof(m_pixels[0]));
    }
    
    void Image::drawImageAtPoint(Image* image, int x, int y)
    {
        for (int j = 0; j < image->height(); j++) {
            for (int i = 0; i < image->width(); i++) {
                setPixel(i + x, j + y, image->pixelAt(i, j));
            }
        }
    }
    
    void Image::loadGLBuffer()
    {
        glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_pixels);
    }
    
    static int toInt(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}
    
    static short toShort(const char* bytes) {
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}
    
    static int readInt(std::ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}
    
    static short readShort(std::ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}
    
    void Image::loadBMPFile(const char *filename)
    {
        std::ifstream input;
        input.open(filename, std::ifstream::binary);
        if (input.fail()) {
            std::cerr << "Could not open file. " << filename << std::endl;
            return;
        }
        char buffer[2];
        input.read(buffer, 2);
        assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
        input.ignore(8);
        int dataOffset = readInt(input);
        
        //Read the header
        int headerSize = readInt(input);
        int width;
        int height;
        switch(headerSize) {
            case 40:
                //V3
                width = readInt(input);
                height = readInt(input);
                input.ignore(2);
                assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
                assert(readShort(input) == 0 || !"Image is compressed");
                break;
            case 12:
                //OS/2 V1
                width = readShort(input);
                height = readShort(input);
                input.ignore(2);
                assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
                break;
            case 64:
                //OS/2 V2
                assert(!"Can't load OS/2 V2 bitmaps");
                break;
            case 108:
                //Windows V4
                assert(!"Can't load Windows V4 bitmaps");
                break;
            case 124:
                //Windows V5
                assert(!"Can't load Windows V5 bitmaps");
                break;
            default:
                assert(!"Unknown bitmap format");
        }
        
        //Read the data
        int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
        int size = bytesPerRow * height;
        char *data = new char[size];
        input.seekg(dataOffset, std::ios_base::beg);
        input.read(data, size);
        
        resize(width, height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                unsigned int offset = bytesPerRow * y + 3 * x;
                Pixel p = {data[offset + 2], data[offset + 1], data[offset]};
                setPixel(x, y, p);
            }
        }
        
        input.close();
    }
    
    void Image::writeBMPFile(const char *filename) const
    {
        std::ofstream fs (filename, std::ios::out | std::ios::binary);
        if (!fs)
            fprintf(stderr, "Couldn't open BMP file %s for writing\n", filename);
        
        int linebyte = m_width * 3;
        int linemod = linebyte % 4;
        if(linemod != 0) {
            linebyte += (4 - linemod);
        }
        const int kFileHeaderSize = 14;
        const int kInfoHeaderSize = 40;
        
        char bfType[3] = "BM";
        unsigned int bfSize = kFileHeaderSize + kInfoHeaderSize + m_height * linebyte;
        unsigned short int bfReserved1 = 0;
        unsigned short int bfReserved2 = 0;
        unsigned int bfOffBits = kFileHeaderSize + kInfoHeaderSize;
        
        
        fs.write((char *)bfType, 2);
        fs.write((char *)&bfSize, 4);
        fs.write((char *)&bfReserved1, 2);
        fs.write((char *)&bfReserved2, 2);
        fs.write((char *)&bfOffBits, 4);
        
        unsigned int biSize = kInfoHeaderSize;
        unsigned int biWidth = m_width;
        unsigned int biHeight = m_height;
        unsigned short int biPlanes = 1;
        unsigned short int biBitCount = 24;
        unsigned int biCompression = 0;
        unsigned int biSizeImage = linebyte * m_height;
        unsigned int biXPelsPerMeter = 0; // horizontal resolution in pixels per meter (unreliable)
        unsigned int biYPelsPerMeter = 0; // vertical resolution in pixels per meter (unreliable)
        unsigned int biClrUsed = 0; // number of colors in image, or zero
        unsigned int biClrImportant = 0; // number of important colors, or zero
        
        fs.write((char *)&biSize, 4);
        fs.write((char *)&biWidth, 4);
        fs.write((char *)&biHeight, 4);
        fs.write((char *)&biPlanes, 2);
        fs.write((char *)&biBitCount, 2);
        fs.write((char *)&biCompression, 4);
        fs.write((char *)&biSizeImage, 4);
        fs.write((char *)&biXPelsPerMeter, 4);
        fs.write((char *)&biYPelsPerMeter, 4);
        fs.write((char *)&biClrUsed, 4);
        fs.write((char *)&biClrImportant, 4);
        
        int i, j;
        int padvalue = 0;
        Pixel *ptr = m_pixels;
        for (j = 0; j < m_height; ++j) {
            for (i = 0; i < m_width; ++i) {
                Pixel pixel = *ptr;
                fs.put(pixel.b);
                fs.put(pixel.g);
                fs.put(pixel.r);
                ptr++;
            }
            if (linemod != 0) {
                fs.write((char *)&padvalue, 4 - linemod);
            }
        }
        fs.close();
    }
    
    void Image::thresholdFilter(double th)
    {
        for(int y = 0; y < m_height; y++) {
            for(int x = 0; x < m_width; x++) {
                Color c = pixelColorAt(x, y);
                if (c.luminance() > th) {
                    setPixelColor(x, y, kColorWhite);
                } else {
                    setPixelColor(x, y, kColorBlack);
                }
                
            }
        }
    }
    
    bool Image::equalsImage(Image* img)
    {
        if (img->width() != m_width || img->height() != m_height) 
            return false;
        for (unsigned int y = 0; y < m_height; y++) {
            for (unsigned int x = 0; x < m_width; x++) {
                int offset = x + y * m_width;
                Pixel q = m_pixels[offset];
                Pixel p = img->m_pixels[offset];
                if (p.r != q.r || 
                    p.g != q.g || 
                    p.b != q.b) {
                    return false;
                }
            }
        }
        return true;
    }
    
    std::ostream& operator<<(std::ostream& out, const Image& image)
    {
        out << "Image(";
        out << image.width();
        out << ", ";
        out << image.height();
        out << ")";
        return out;
    }
}
