/*
 * Author: Filipe Chagas (filipe.ferraz0@gmail.com)
 * october/2021
 */

#include "image.hpp"
#include <assert.h>
#include <math.h>

#define ABS(v) (((v) >= 0) ? (v) : -(v))

Image::Image(uint32_t width, uint32_t height)
{
    assert(width > 0);
    assert(height > 0);

    this->w = width;
    this->h = height;
}

uint32_t Image::getWidth()
{
    return this->w;
}

uint32_t Image::getHeight()
{
    return this->h;
}

Image::~Image()
{

}

ImageARGB8888::ImageARGB8888(uint32_t width, uint32_t height) : Image(width, height)
{
    this->a_array = new uint8_t[width*height];
    this->r_array = new uint8_t[width*height];
    this->g_array = new uint8_t[width*height];
    this->b_array = new uint8_t[width*height];
}

ImageARGB8888::~ImageARGB8888()
{
    delete[] this->a_array;
    delete[] this->r_array;
    delete[] this->g_array;
    delete[] this->b_array;
}

Color ImageARGB8888::getPixel(uint32_t x, uint32_t y)
{
    assert(x < this->w);
    assert(y < this->h);

    uint8_t a = this->a_array[x*this->h + y];
    uint8_t r = this->r_array[x*this->h + y];
    uint8_t g = this->g_array[x*this->h + y];
    uint8_t b = this->b_array[x*this->h + y];
    return Color((float)a/255.0, (float)r/255.0, (float)g/255.0, (float)b/255.0);
}

void ImageARGB8888::setPixel(uint32_t x, uint32_t y, Color color)
{
    assert(x < this->w);
    assert(y < this->h);

    uint8_t a = color.a * 255;
    uint8_t r = color.r * 255;
    uint8_t g = color.g * 255;
    uint8_t b = color.b * 255;
    this->a_array[x*this->h + y] = a;
    this->r_array[x*this->h + y] = r;
    this->g_array[x*this->h + y] = g;
    this->b_array[x*this->h + y] = b;
}

ImageARGB1555::ImageARGB1555(uint32_t width, uint32_t height) : Image(width, height)
{
    this->argb_array = new uint16_t[width*height];
}

Color ImageARGB1555::getPixel(uint32_t x, uint32_t y)
{
    // A  R  R  R  R  R  G  G  G  G  G  B  B  B  B  B
    //15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

    assert(x < this->w);
    assert(y < this->h);

    uint16_t argb = this->argb_array[x*this->h + y];
    uint8_t a = (argb >> 15) & 0x01;
    uint8_t r = (argb >> 10) & 0x1F;
    uint8_t g = (argb >> 5) & 0x1F;
    uint8_t b = argb & 0x1F;
    return Color((float)a, (float)r/(float)0x1F, (float)g/(float)0x1F, (float)b/(float)0x1F);
}

void ImageARGB1555::setPixel(uint32_t x, uint32_t y, Color color)
{
    // A  R  R  R  R  R  G  G  G  G  G  B  B  B  B  B
    //15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

    assert(x < this->w);
    assert(y < this->h);

    uint8_t a = (uint8_t)(roundf(color.a) * 0x01) & 0x01;
    uint8_t r = (uint8_t)(color.r * 0x1F) & 0x1F;
    uint8_t g = (uint8_t)(color.g * 0x1F) & 0x1F;
    uint8_t b = (uint8_t)(color.b * 0x1F) & 0x1F;
    this->argb_array[x*this->h + y] = (a << 15) | (r << 10) | (g << 5) | b;
}

ImageARGB1555::~ImageARGB1555()
{
    delete[] this->argb_array;
}


ImageRGB565::ImageRGB565(uint32_t width, uint32_t height) : Image(width, height)
{
    this->rgb_array = new uint16_t[width*height];
}

Color ImageRGB565::getPixel(uint32_t x, uint32_t y)
{
    // R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B
    //15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

    assert(x < this->w);
    assert(y < this->h);

    uint16_t rgb = this->rgb_array[x*this->w + y];
    uint8_t r = (rgb >> 11) & 0x1F;
    uint8_t g = (rgb >> 5) & 0x3F;
    uint8_t b = rgb & 0x1F;
    return Color((float)r/(float)0x1F, (float)g/(float)0x3F, (float)b/(float)0x1F);
}

void ImageRGB565::setPixel(uint32_t x, uint32_t y, Color color)
{
    // R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B
    //15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

    assert(x < this->w);
    assert(y < this->h);

    uint8_t r = (uint8_t)(color.r * 0x1F) & 0x1F;
    uint8_t g = (uint8_t)(color.g * 0x3F) & 0x3F;
    uint8_t b = (uint8_t)(color.b * 0x1F) & 0x1F;
    this->rgb_array[x*this->h + y] = (r << 11) | (g << 5) | b;
}

ImageRGB565::~ImageRGB565()
{
    delete[] this->rgb_array;
}

ImageK8::ImageK8(uint32_t width, uint32_t height) : Image(width, height)
{
    assert(width > 0);
    assert(height > 0);
    this->k_array = new uint8_t[width*height];
}

Color ImageK8::getPixel(uint32_t x, uint32_t y)
{
    assert(x < this->w);
    assert(y < this->h);

    uint8_t k = this->k_array[x*this->h + y];
    Color *target_color = this->color_map[k];

    assert(target_color != nullptr);

    return *target_color;
}

float diference_between_colors(Color &a, Color &b)
{
    return ABS(a.a - b.a) + ABS(a.r - b.r) + ABS(a.g - b.g) + ABS(a.b - b.b);
}

void ImageK8::setPixel(uint32_t x, uint32_t y, Color color)
{
    assert(x < this->w);
    assert(y < this->h);
    assert(this->color_map[0] != nullptr);

    float smaller_difference = diference_between_colors(color, *this->color_map[0]);
    uint8_t k = 0;

    for(int i = 1; i < 256; i++)
    {
        if(this->color_map[i] != nullptr)
        {
            float difference = diference_between_colors(color, *this->color_map[i]);
            if(difference < smaller_difference)
            {
                smaller_difference = difference;
                k = i;
            }
        }
    }

    this->k_array[x*this->h + y] = k;
}

ImageK8::~ImageK8()
{
    for(int i = 1; i < 256; i++)
    {
        if(this->color_map[i] != nullptr)
        {
            delete this->color_map[i];
        }
    }

    delete[] this->k_array;
}
