/*
 * framebuffer.cpp
 *
 *  Created on: 24 de out de 2021
 *      Author: Filipe Chagas
 */

#include "framebuffer.hpp"

FrameBuffer::FrameBuffer()
{

}

FrameBuffer::~FrameBuffer()
{

}

// ------ FrameBuffer24 ------

FrameBuffer24::FrameBuffer24(uint32_t w, uint32_t h)
{
    this->w = w;
    this->h = h;
    this->r = new uint8_t[w*h];
    this->g = new uint8_t[w*h];
    this->b = new uint8_t[w*h];
}

void FrameBuffer24::setColor(uint32_t x, uint32_t y, Color color)
{
    this->r[x*this->w + y] = (uint8_t)(255*color.r);
    this->g[x*this->w + y] = (uint8_t)(255*color.g);
    this->b[x*this->w + y] = (uint8_t)(255*color.b);
}

Color FrameBuffer24::getColor(uint32_t x, uint32_t y)
{
    uint8_t r8 = this->r[x*this->w + y];
    uint8_t g8 = this->g[x*this->w + y];
    uint8_t b8 = this->b[x*this->w + y];
    return Color((float)r8/255, (float)g8/255, (float)b8/255);
}

FrameBuffer24::~FrameBuffer24()
{
    delete[] this->r;
    delete[] this->g;
    delete[] this->b;
}

// ------ FrameBuffer16 -----------

#define COLOR565(r, g, b) (((r & 0x1F) << 11) | ((g & 0x3F) << 5) | ((b & 0x1F)))

FrameBuffer16::FrameBuffer16(uint32_t w, uint32_t h)
{
    this->w = w;
    this->h = h;
    this->buff = new uint16_t[w*h];
}

void FrameBuffer16::setColor(uint32_t x, uint32_t y, Color color)
{
    uint8_t r8 = (uint8_t)(0x1F*color.r);
    uint8_t g8 = (uint8_t)(0x3F*color.g);
    uint8_t b8 = (uint8_t)(0x1F*color.b);
    this->buff[x*this->w + y] = COLOR565(r8, g8, b8);
}

Color FrameBuffer16::getColor(uint32_t x, uint32_t y)
{
    uint16_t color16 = this->buff[x*this->w + y];
    uint8_t r8 = (color16 >> 11) & 0x1F;
    uint8_t g8 = (color16 >> 5) & 0x3F;
    uint8_t b8 = (color16) & 0x1F;
    return Color((float)r8/(float)0x1F, (float)g8/(float)0x3F, (float)b8/(float)0x1F);
}

FrameBuffer16::~FrameBuffer16()
{
    delete[] this->buff;
}

