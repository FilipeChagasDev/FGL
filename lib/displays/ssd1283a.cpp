#include "ssd1283a.hpp"
#include <assert.h>

#define CLIPVALUE(v, min, max) (((v) < (min)) ? (min) : (((v) > (max)) ? (max) : (v)))

void SSD1283A::sendCommand(uint8_t command)
{
    this->cdPinReset();
    this->sendByte(command);
}

void SSD1283A::sendByteData(uint8_t data)
{
    this->cdPinSet();
    this->sendByte(data);
}

void SSD1283A::sendHalfWordData(uint16_t data)
{
    this->cdPinSet();
    this->sendHalfWord(data);
}

void SSD1283A::initCommands()
{
    this->sendCommand(0x10);
    this->sendHalfWordData(0x2F8E);
    this->sendCommand(0x11);
    this->sendHalfWordData(0x000C);
    this->sendCommand(0x07);
    this->sendHalfWordData(0x0021);
    this->sendCommand(0x28);
    this->sendHalfWordData(0x0006);
    this->sendCommand(0x28);
    this->sendHalfWordData(0x0005);
    this->sendCommand(0x27);
    this->sendHalfWordData(0x057F);
    this->sendCommand(0x29);
    this->sendHalfWordData(0x89A1);
    this->sendCommand(0x00);
    this->sendHalfWordData(0x0001);
    this->delay(100);
    this->sendCommand(0x29);
    this->sendHalfWordData(0x80B0);
    this->delay(30);
    this->sendCommand(0x29);
    this->sendHalfWordData(0xFFFE);
    this->sendCommand(0x07);
    this->sendHalfWordData(0x0223);
    this->delay(30);
    this->sendCommand(0x07);
    this->sendHalfWordData(0x0233);
    this->sendCommand(0x01);
    this->sendHalfWordData(0x2183);
    this->sendCommand(0x03);
    this->sendHalfWordData(0x6830);
    this->sendCommand(0x2F);
    this->sendHalfWordData(0xFFFF);
    this->sendCommand(0x2C);
    this->sendHalfWordData(0x8000);
    this->sendCommand(0x27);
    this->sendHalfWordData(0x0570);
    this->sendCommand(0x02);
    this->sendHalfWordData(0x0300);
    this->sendCommand(0x0B);
    this->sendHalfWordData(0x580C);
    this->sendCommand(0x12);
    this->sendHalfWordData(0x0609);
    this->sendCommand(0x13);
    this->sendHalfWordData(0x3100);
}

void SSD1283A::setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    assert(x1 >= x0);
    assert(y1 >= y0);

    uint32_t w = this->getWidth();
    uint32_t h = this->getHeight();

    switch (this->rotation)
    {
    case 0:
        this->sendCommand(0x44);
        this->sendHalfWordData(x1 + 2);
        this->sendHalfWordData(x0 + 2);
        this->sendCommand(0x45);
        this->sendHalfWordData(y1 + 2);
        this->sendHalfWordData(y0 + 2);
        this->sendCommand(0x21);
        this->sendHalfWordData(y0 + 2);
        this->sendHalfWordData(x0 + 2);
        break;
    case 1:
        this->sendCommand(0x44);
        this->sendHalfWordData(h - y0 + 1);
        this->sendHalfWordData(h - y1 + 1);
        this->sendCommand(0x45);
        this->sendHalfWordData(w - x0 - 1);
        this->sendHalfWordData(w - x1 - 1);
        this->sendCommand(0x21);
        this->sendHalfWordData(w - x0 - 1);
        this->sendHalfWordData(h - y0 + 1);
        break;
    case 2:
        this->sendCommand(0x44);
        this->sendHalfWordData(w - x0 + 1);
        this->sendHalfWordData(w - x1 + 1);
        this->sendCommand(0x45);
        this->sendHalfWordData(h - y0 + 1);
        this->sendHalfWordData(h - y1 + 1);
        this->sendCommand(0x21);
        this->sendHalfWordData(h - y0 + 1);
        this->sendHalfWordData(w - x0 + 1);
        break;
    case 3:
        this->sendCommand(0x44);
        this->sendHalfWordData(y1 + 2);
        this->sendHalfWordData(y0 + 2);
        this->sendCommand(0x45);
        this->sendHalfWordData(x1);
        this->sendHalfWordData(x0);
        this->sendCommand(0x21);
        this->sendHalfWordData(x0);
        this->sendHalfWordData(y0 + 2);
        break;
    }
    this->sendCommand(0x22);
}

void SSD1283A::setRotation(uint8_t r)
{
    this->rotation = r & 3;
    switch (this->rotation)
    {
    case 0:
        this->sendCommand(0x01);
        this->sendHalfWordData(this->inversion_bit | 0x2183);
        this->sendCommand(0x03);
        this->sendHalfWordData(0x6830);
        break;
    case 1:
        this->sendCommand(0x01);
        this->sendHalfWordData(this->inversion_bit | 0x2283);
        this->sendCommand(0x03);
        this->sendHalfWordData(0x6808);
        break;
    case 2:
        this->sendCommand(0x01);
        this->sendHalfWordData(this->inversion_bit | 0x2183);
        this->sendCommand(0x03);
        this->sendHalfWordData(0x6800);
        break;
    case 3:
        this->sendCommand(0x01);
        this->sendHalfWordData(this->inversion_bit | 0x2283);
        this->sendCommand(0x03);
        this->sendHalfWordData(0x6838);
        break;
    }
}

SSD1283A::SSD1283A()
{
    this->rotation = 0;
    this->v_width_dots = 130;
    this->v_height_dots = 130;
    this->v_width_mm = 28.86;
    this->v_height_mm = 28.86;
}

const char *SSD1283A::getName()
{
    return "SSD1283A";
}

uint32_t SSD1283A::getWidth()
{
    /* rotation=0 -> false V
     * rotation=1 -> true H
     * rotation=2 -> false VI
     * rotation=3 -> true HI
     */
    return (this->rotation & 1) ? this->v_height_dots : this->v_width_dots;
}

uint32_t SSD1283A::getHeight()
{
    /* rotation=0 -> false
     * rotation=1 -> true
     * rotation=2 -> false
     * rotation=3 -> true
     */
    return (this->rotation & 1) ? this->v_width_dots : this->v_height_dots;
}

float SSD1283A::getDPMMX()
{
    return this->v_width_mm/this->v_width_dots;
}

float SSD1283A::getDPMMY()
{
    return this->v_height_mm/this->v_height_dots;
}

void SSD1283A::setBrightness(float v)
{
    this->setLedValue(v);
    this->brightness = v;
}

float SSD1283A::getBrightness()
{
    return this->brightness;
}

void SSD1283A::setOrientation(Orientation orientation)
{
    this->select();
    switch(orientation)
    {
    case Orientation::V:
        this->setRotation(0);
        break;
    case Orientation::H:
        this->setRotation(1);
        break;
    case Orientation::VI:
        this->setRotation(2);
        break;
    case Orientation::HI:
        this->setRotation(3);
        break;
    }
    this->unselect();
}

Orientation SSD1283A::getOrientation()
{
    switch(this->rotation)
    {
    case 0:
        return Orientation::V;
    case 1:
        return Orientation::H;
    case 2:
        return Orientation::VI;
    case 3:
        break;
    }

    return Orientation::HI;
}

void SSD1283A::init()
{
    this->initIO();
    this->setLedValue(0);
    this->csPinSet();
    this->rstPinReset();
    this->delay(3);
    this->rstPinSet();
    this->delay(200);
    this->select();
    this->initCommands();
    this->unselect();
    this->setBrightness(1);
}

void SSD1283A::reset()
{
    this->csPinSet();
    this->rstPinReset();
    this->delay(3);
    this->rstPinSet();
    this->delay(200);
    this->select();
    this->initCommands();
    this->unselect();
}

void SSD1283A::select()
{
    this->csPinReset();
}

void SSD1283A::unselect()
{
    this->csPinSet();
}

bool SSD1283A::drawPixel(int x, int y, float r, float g, float b)
{
    this->select();
    // R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B
    // 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0

    uint8_t _r = (uint8_t)(r * 0x1F) & 0x1F;
    uint8_t _g = (uint8_t)(g * 0x3F) & 0x3F;
    uint8_t _b = (uint8_t)(b * 0x1F) & 0x1F;
    uint16_t color = (_r << 11) | (_g << 5) | _b;

    if(x >= 0 and y >= 0 and x < this->getWidth() and y < this->getHeight())
    {
        this->setAddressWindow(x,y,x,y);
        this->sendHalfWordData(color);
        return true;
    }

    return false;
    this->unselect();
}

bool SSD1283A::drawArea(int x1, int y1, int x2, int y2, float r, float g, float b)
{
    this->select();
    uint32_t w = this->getWidth();
    uint32_t h = this->getHeight();

    x1 = (x1 < 0) ? 0 : x1;
    y1 = (y1 < 0) ? 0 : y1;
    x2 = CLIPVALUE(x2, x1, w);
    y2 = CLIPVALUE(y2, y1, h);

    // R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B
    // 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0

    uint8_t _r = (uint8_t)(CLIPVALUE(r, 0, 1) * 0x1F) & 0x1F;
    uint8_t _g = (uint8_t)(CLIPVALUE(g, 0, 1) * 0x3F) & 0x3F;
    uint8_t _b = (uint8_t)(CLIPVALUE(b, 0, 1) * 0x1F) & 0x1F;
    uint16_t color = (_r << 11) | (_g << 5) | _b;

    this->setAddressWindow(x1,y1,x2,y2);
    this->sendCommand(0x22);

    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            this->sendHalfWordData(color);
        }
    }

    return true;
    this->unselect();
}
