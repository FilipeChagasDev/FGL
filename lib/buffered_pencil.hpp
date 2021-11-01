/*
 * buffered_pencil.hpp
 *
 *  Created on: 23 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef HQCANVAS_HPP
#define HQCANVAS_HPP

#include "pencil.hpp"
#include "color.hpp"
#include "framebuffer.hpp"

/**
 * @brief BufferedPencil is a Pencil subclass with anti-aliasing and alpha-composition.
 * This class consumes more memory and processing than your Pencil superclass, so be careful when using it.
 */
class BufferedPencil : public Pencil
{
protected:
    FrameBuffer *fb;
    bool anti_aliasing;

    /**
     * @brief Draw a pixel with transparency.
     * 
     * @param x X coordinate to pixel.
     * @param y Y coordinate to pixel.
     * @param opacity Opacity (1-transparency).
     * @param color Pixel color.
     */
    void drawTransparentPixel(int x, int y, float opacity, Color color);
public:
    float scattering;
    bool aliased_overdraw;

    /**
     * @brief Construct a new BufferedPencil object
     * 
     * @param display Display object where the BufferedPencil class will draw things.
     * @param back_color Background color used.
     * @param anti_aliasing (Optional) Enable anti-aliasing. Default is true.
     * @param buffer24 (Optional) Set it as true to use 24 bit framebuffer. Default is 16 bit.
     */
    BufferedPencil(Display &display, Color back_color, bool anti_aliasing = true, bool buffer24 = false);

    /**
     * @brief Draw a pixel with alpha-composition.
     * 
     * @param x X coordinate to pixel.
     * @param y Y coordinate to pixel.
     * @param color Pixel color.
     */
    virtual void drawPixel(float x, float y, Color color);

    /**
     * @brief Destroy the BufferedPencil object
     */
    virtual ~BufferedPencil();
};

#endif // HQCANVAS_HPP
