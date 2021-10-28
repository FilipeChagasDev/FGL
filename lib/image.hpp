/*
 * Author: Filipe Chagas (filipe.ferraz0@gmail.com)
 * october/2021
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "color.hpp"
#include <stdint.h>

/**
 * @brief Abstract image class. 
 * This class serves as an interface to all the different FGL image formats.
 */
class Image
{
protected:
    uint32_t w, h;
public:
    /**
     * @brief Construct a new Image object.
     * 
     * @param width Image width.
     * @param height Image height.
     */
    Image(uint32_t width, uint32_t height);

    /**
     * @brief Get image width.
     * 
     * @return uint32_t 
     */
    uint32_t getWidth();

    /**
     * @brief Get image height.
     * 
     * @return uint32_t 
     */
    uint32_t getHeight();

    /**
     * @brief Get the color of a pixel in the image.
     * 
     * @param x X coordinate of the pixel.
     * @param y Y coordinate of the pixel.
     * @return Color 
     */
    virtual Color getPixel(uint32_t x, uint32_t y) = 0;

    /**
     * @brief Set a color to a pixel in the image.
     * 
     * @param x X coordinate of the pixel.
     * @param y Y coordinate of the pixel.
     * @param color Color.
     */
    virtual void setPixel(uint32_t x, uint32_t y, Color color) = 0;
    virtual ~Image();
};

/**
 * @brief Image subclass to the **ARGB8888** format.
 * In this format, each value **A**, **R**, **G** and **B** is 8 bits long. Each pixel is 32 bits long.
 */
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

/**
 * @brief Image subclass to the **ARGB1555** format.
 * In this format, **A** is binary and **R**, **G** and **B** are 5 bits long. 
 * Each pixel is 16 bits long.
 */
class ImageARGB1555 : public Image
{
public:
    uint16_t *argb_array;
    ImageARGB1555(uint32_t width, uint32_t height);
    Color getPixel(uint32_t x, uint32_t y);
    void setPixel(uint32_t x, uint32_t y, Color color);
    virtual ~ImageARGB1555();
};

/**
 * @brief Image subclass to the **RGB565** format.
 * This format has no transparency. **R** and **B** are 5 bits long and **G** is 6 bits long. 
 * Each pixel is 16 bits long.
 */
class ImageRGB565 : public Image
{
public:
    uint16_t *rgb_array;
    ImageRGB565(uint32_t width, uint32_t height);
    Color getPixel(uint32_t x, uint32_t y);
    void setPixel(uint32_t x, uint32_t y, Color color);
    virtual ~ImageRGB565();
};

/**
 * @brief Image subclass to the **K8** format.
 * This format uses a color palette with a maximum of 256 colors.
 * Each pixel is represented by an 8-bit key that references a color from the palette.
 */
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
