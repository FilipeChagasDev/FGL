/*
 * framebuffer.hpp
 *
 *  Created on: 24 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <stdint.h>
#include "color.hpp"

class FrameBuffer
{
public:
    FrameBuffer();
    virtual void setColor(uint32_t x, uint32_t y, Color color) = 0;
    virtual Color getColor(uint32_t x, uint32_t y) = 0;
    virtual ~FrameBuffer();
};

class FrameBuffer24 : public FrameBuffer
{
protected:
    uint32_t w, h;
    uint8_t *r;
    uint8_t *g;
    uint8_t *b;
public:
    FrameBuffer24(uint32_t w, uint32_t h);
    void setColor(uint32_t x, uint32_t y, Color color);
    Color getColor(uint32_t x, uint32_t y);
    virtual ~FrameBuffer24();
};

class FrameBuffer16 : public FrameBuffer
{
protected:
    uint32_t w, h;
    uint16_t *buff;
public:
    FrameBuffer16(uint32_t w, uint32_t h);
    void setColor(uint32_t x, uint32_t y, Color color);
    Color getColor(uint32_t x, uint32_t y);
    virtual ~FrameBuffer16();
};

#endif // FRAMEBUFFER_HPP
