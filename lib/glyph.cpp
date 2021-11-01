#include "glyph.hpp"

Glyph::Glyph(uint32_t width, uint32_t height)
{
    this->w = width;
    this->h = height;
    this->array = new uint8_t[width*height];
}

Glyph::~Glyph()
{
    delete[] this->array;
}

uint8_t Glyph::getPixel(uint32_t x, uint32_t y)
{
    assert(x < this->w);
    assert(y < this->h);
    return this->array[x*this->h + y];
}

void Glyph::setPixel(uint32_t x, uint32_t y, uint8_t value)
{
    assert(x < this->w);
    assert(y < this->h);
    this->array[x*this->h + y] = value;
}
