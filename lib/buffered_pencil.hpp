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

class BufferedPencil : public Pencil
{
protected:
    FrameBuffer *fb;
    bool anti_aliasing;
    void drawTransparentPixel(int x, int y, float opacity, Color color);
public:
    BufferedPencil(Display &display, Color back_color, bool anti_aliasing = true, bool buffer24 = false);
    virtual void drawPixel(float x, float y, Color color);
    virtual ~BufferedPencil();
};

#endif // HQCANVAS_HPP
