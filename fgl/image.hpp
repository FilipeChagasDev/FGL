/*
 * Author: Filipe Chagas (filipe.ferraz0@gmail.com)
 * october/2021
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "color.hpp"
#include <stdint.h>

class Image
{
protected:
    uint32_t w, h;
public:
    Image(uint32_t width, uint32_t height);
    uint32_t getWidth();
    uint32_t getHeight();
    virtual Color getPixel(uint32_t x, uint32_t y) = 0;
    virtual void setPixel(uint32_t x, uint32_t y, Color color) = 0;
    virtual ~Image();
};

class ImageARGB8888 : public Image
{
public:
    uint8_t *a_array;
    uint8_t *r_array;
    uint8_t *g_array;
    uint8_t *b_array;
    ImageARGB8888(uint32_t width, uint32_t height);
    Color getPixel(uint32_t x, uint32_t y);
    void setPixel(uint32_t x, uint32_t y, Color color);
    virtual ~ImageARGB8888();
};

class ImageARGB1555 : public Image
{
public:
    uint16_t *argb_array;
    ImageARGB1555(uint32_t width, uint32_t height);
    Color getPixel(uint32_t x, uint32_t y);
    void setPixel(uint32_t x, uint32_t y, Color color);
    virtual ~ImageARGB1555();
};

class ImageRGB565 : public Image
{
public:
    uint16_t *rgb_array;
    ImageRGB565(uint32_t width, uint32_t height);
    Color getPixel(uint32_t x, uint32_t y);
    void setPixel(uint32_t x, uint32_t y, Color color);
    virtual ~ImageRGB565();
};

class ImageK8 : public Image
{
public:
    Color *color_map[256];
    uint8_t *k_array;
    ImageK8(uint32_t width, uint32_t height);
    Color getPixel(uint32_t x, uint32_t y);
    void setPixel(uint32_t x, uint32_t y, Color color);
    virtual ~ImageK8();
};

#endif // IMAGE_HPP
