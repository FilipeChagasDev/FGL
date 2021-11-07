/*
 * color.cpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#include "color.hpp"

#define CLIPVALUE(v, min, max) (((v) < (min)) ? (min) : (((v) > (max)) ? (max) : (v)))

Color::Color()
{
    this->a = 1;
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color::Color(float r, float g, float b)
{
    this->a = 1;
    this->r = CLIPVALUE(r, 0, 1);
    this->g = CLIPVALUE(g, 0, 1);
    this->b = CLIPVALUE(b, 0, 1);
}

Color::Color(float a, float r, float g, float b)
{
    this->a = CLIPVALUE(a, 0, 1);
    this->r = CLIPVALUE(r, 0, 1);
    this->g = CLIPVALUE(g, 0, 1);
    this->b = CLIPVALUE(b, 0, 1);
}

void Color::setRGB(float r, float g, float b)
{
    this->a = 1;
    this->r = CLIPVALUE(r, 0, 1);
    this->g = CLIPVALUE(g, 0, 1);
    this->b = CLIPVALUE(b, 0, 1);
}

void Color::setARGB(float a, float r, float g, float b)
{
    this->a = CLIPVALUE(a, 0, 1);
    this->r = CLIPVALUE(r, 0, 1);
    this->g = CLIPVALUE(g, 0, 1);
    this->b = CLIPVALUE(b, 0, 1);
}

Color::~Color()
{
    // TODO Auto-generated destructor stub
}


Color color_from_rgb888(uint32_t rgb, float alpha)
{
    // x  x  x  x  x  x  x  x  R  R  R  R  R  R  R  R  G  G  G  G  G  G  G G B B B B B B B B
    // 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0

    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;
    return Color(alpha, (float)r/255.0, (float)g/255.0, (float)b/255.0);
}

Color color_from_rgba8888(uint32_t rgba)
{
    // R  R  R  R  R  R  R  R  G  G  G  G  G  G  G  G  B  B  B  B  B  B  B B A A A A A A A A
    // 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0

    uint8_t r = (rgba >> 24) & 0xFF;
    uint8_t g = (rgba >> 16) & 0xFF;
    uint8_t b = (rgba >> 8) & 0xFF;
    uint8_t a = rgba & 0xFF;
    return Color((float)a/255.0, (float)r/255.0, (float)g/255.0, (float)b/255.0);
}
