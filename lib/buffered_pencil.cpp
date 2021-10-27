/*
 * buffered_pencil.cpp
 *
 *  Created on: 23 de out de 2021
 *      Author: Filipe Chagas
 */

#include "buffered_pencil.hpp"
#include <math.h>

#define ABS(v) (((v) >= 0) ? (v) : -(v))

BufferedPencil::BufferedPencil(Display &display, Color back_color, bool anti_aliasing, bool buffer24) : Pencil(display)
{
    this->anti_aliasing = anti_aliasing;

    if(buffer24) this->fb = new FrameBuffer24(display.getWidth(), display.getHeight());
    else this->fb = new FrameBuffer16(display.getWidth(), display.getHeight());

    for(int i = 0; i < this->w; i++)
    {
        for(int j = 0; j < this->h; j++)
        {
            this->fb->setColor(i, j, back_color);
        }
    }
}

void BufferedPencil::drawTransparentPixel(int x, int y, float opacity, Color color)
{
    if(x > 0 and y > 0 and x < this->display->getWidth() and y < this->display->getHeight())
    {
        Color buff_color = this->fb->getColor(x, y);
        float buff_r = buff_color.r;
        float buff_g = buff_color.g;
        float buff_b = buff_color.b;
        float r = opacity*color.a*color.r + (1-opacity*color.a)*buff_r;
        float g = opacity*color.a*color.g + (1-opacity*color.a)*buff_g;
        float b = opacity*color.a*color.b + (1-opacity*color.a)*buff_b;
        this->display->drawPixel(x, y, r, g, b);
        this->fb->setColor(x, y, Color(r, g, b));
    }
}

void BufferedPencil::drawPixel(float x, float y, Color color)
{
    if(this->anti_aliasing)
    {
        float floor_coeff_x = 1 - ABS(x - floor(x));
        float floor_coeff_y = 1 - ABS(y - floor(y));

        float ceil_coeff_x = 1 - ABS(x - ceil(x));
        float ceil_coeff_y = 1 - ABS(y - ceil(y));

        this->drawTransparentPixel(floor(x), floor(y), floor_coeff_x*floor_coeff_y, color);
        this->drawTransparentPixel(floor(x), ceil(y), floor_coeff_x*ceil_coeff_y, color);
        this->drawTransparentPixel(ceil(x), floor(y), ceil_coeff_x*floor_coeff_y, color);
        this->drawTransparentPixel(ceil(x), ceil(y), ceil_coeff_x*ceil_coeff_y, color);
    }
    else
    {
        int round_x = roundf(x);
        int round_y = roundf(y);
        this->drawTransparentPixel(round_x, round_y, 1, color);
    }
}

BufferedPencil::~BufferedPencil()
{
    delete this->fb;
}
