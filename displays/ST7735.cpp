/*
 * ST7735.cpp
 *
 *  Created on: 21 de out de 2021
 *      Author: Filipe Chagas
 *      Based on: https://github.com/Dungyichao/STM32F4-LCD_ST7735s/blob/master/ST7735/st7735.c
 */

#include "ST7735.hpp"

#define ST7735_XSTART 0
#define ST7735_YSTART 0
#define ST7735_IS_160X128 1
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY)

#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

#define ST7735_COLOR565(r, g, b) (((r & 0x1F) << 11) | ((g & 0x3F) << 5) | ((b & 0x1F)))

#define CLIPVALUE(v, min, max) ((v < min) ? min : ((v > max) ? max : v))

ST7735::ST7735()
{
	//1.8 inch display dimensions
	this->orientation = Orientation::V;
	this->v_width_dots = 128;
	this->v_height_dots = 160;
	this->v_width_mm = 28.03;
	this->v_height_mm = 35.04;
}

ST7735::~ST7735()
{
	// TODO Auto-generated destructor stub
}

void ST7735::sendCommand(uint8_t cmd)
{
	this->dcPinReset();
	this->sendByte(cmd);
}

void ST7735::sendData(uint8_t data)
{
	this->dcPinSet();
	this->sendByte(data);
}

void ST7735::init()
{
	this->initIO();
	this->reset();
}

void ST7735::initCommand1()
{
	this->sendCommand(ST7735_SWRESET); //1: Software reset
	this->delay(150);
	this->sendCommand(ST7735_SLPOUT); //2: Out of sleep mode
	this->delay(500);
	this->sendCommand(ST7735_FRMCTR1); //3: Frame rate ctrl - normal mode
	this->sendData(0x01); //Rate = fosc/(1x2+40) * (LINE+2C+2D)
	this->sendData(0x2C);
	this->sendData(0x2D);
	this->sendCommand(ST7735_FRMCTR2); //4: Frame rate control - idle mode
	this->sendData(0x01); //Rate = fosc/(1x2+40) * (LINE+2C+2D)
	this->sendData(0x2C);
	this->sendData(0x2D);
	this->sendCommand(ST7735_FRMCTR3); //5: Frame rate ctrl - partial mode
	this->sendData(0x01); //Dot inversion mode
	this->sendData(0x2C);
	this->sendData(0x2D);
	this->sendData(0x01); //Line inversion mode
	this->sendData(0x2C);
	this->sendData(0x2D);
	this->sendCommand(ST7735_INVCTR); //6: Display inversion ctrl
	this->sendData(0x07); //No inversion
	this->sendCommand(ST7735_PWCTR1); //7: Power control
	this->sendData(0xA2);
	this->sendData(0x02); // -4.6V
	this->sendData(0x84); // AUTO mode
	this->sendCommand(ST7735_PWCTR2); // 8: Power control
	this->sendData(0xC5); // VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
	this->sendCommand(ST7735_PWCTR3); // 9: Power control
	this->sendData(0x0A); // Opamp current small
	this->sendData(0x00); // Boost frequency
	this->sendCommand(ST7735_PWCTR4); // 10: Power control
	this->sendData(0x8A); // BCLK/2, Opamp current small & Medium low
	this->sendData(0x2A);
	this->sendCommand(ST7735_PWCTR5); // 11: Power control
	this->sendData(0x8A);
	this->sendData(0xEE);
	this->sendCommand(ST7735_VMCTR1); // 12: Power control
	this->sendData(0x0E);
	this->sendCommand(ST7735_INVOFF); // 13: Don't invert display
	this->sendCommand(ST7735_MADCTL); // 14: Memory access control (directions)
	this->sendData(ST7735_ROTATION); // row addr/col addr, bottom to top refresh
	this->sendCommand(ST7735_COLMOD); // 15: set color mode
	this->sendData(0x05); // 16-bit color
}

void ST7735::initCommand2()
{
	this->sendCommand(ST7735_CASET); // 1: Column addr set
	this->sendData(0x00); // XSTART = 0
	this->sendData(0x00);
	this->sendData(0x00); // XEND = 127
	this->sendData(0x7F);
	this->sendCommand(ST7735_RASET); // 2: Row addr set
	this->sendData(0x00); // XSTART = 0
	this->sendData(0x00);
	this->sendData(0x00); // XEND = 127
	this->sendData(0x7F);
}

void ST7735::initCommand3()
{
	this->sendCommand(ST7735_GMCTRP1); // 1: Magical unicorn dust
	this->sendData(0x02);
	this->sendData(0x1C);
	this->sendData(0x07);
	this->sendData(0x12);
	this->sendData(0x37);
	this->sendData(0x32);
	this->sendData(0x29);
	this->sendData(0x2D);
	this->sendData(0x29);
	this->sendData(0x25);
	this->sendData(0x2B);
	this->sendData(0x39);
	this->sendData(0x00);
	this->sendData(0x01);
	this->sendData(0x03);
	this->sendData(0x10);
	this->sendCommand(ST7735_GMCTRN1); // 2: Sparkles and rainbows
	this->sendData(0x03);
	this->sendData(0x1D);
	this->sendData(0x07);
	this->sendData(0x06);
	this->sendData(0x2E);
	this->sendData(0x2C);
	this->sendData(0x29);
	this->sendData(0x2D);
	this->sendData(0x2E);
	this->sendData(0x2E);
	this->sendData(0x37);
	this->sendData(0x3F);
	this->sendData(0x00);
	this->sendData(0x00);
	this->sendData(0x02);
	this->sendData(0x10);
	this->sendCommand(ST7735_NORON);
	this->delay(10);
	this->sendCommand(ST7735_DISPON);
	this->delay(100);
}

const char *ST7735::getName()
{
	return "ST7735";
}

uint32_t ST7735::getWidth()
{
	if(this->orientation == Orientation::V)
		return this->v_width_dots;
	else
		return this->v_height_dots;
}

uint32_t ST7735::getHeight()
{
	if(this->orientation == Orientation::V)
		return this->v_height_dots;
	else
		return this->v_width_dots;
}

float ST7735::getDPMMX()
{
	if(this->orientation == Orientation::V)
		return (float)this->v_width_dots/this->v_width_mm;
	else
		return (float)this->v_height_dots/this->v_height_mm;
}

float ST7735::getDPMMY()
{
	if(this->orientation == Orientation::V)
		return (float)this->v_height_dots/this->v_height_mm;
	else
		return (float)this->v_width_dots/this->v_width_mm;
}

void ST7735::setBrightness(float v)
{
	//TODO
}

float ST7735::getBrightness()
{
	//TODO
	return 1;
}

void ST7735::setOrientation(Orientation orientation)
{
	this->orientation = orientation;
}

Orientation ST7735::getOrientation()
{
	return this->orientation;
}

void ST7735::reset()
{
	//select
	this->csPinReset();

	//reset
	this->rstPinReset();
	this->delay(7);
	this->rstPinSet();

	//configure
	this->initCommand1();
	this->initCommand2();
	this->initCommand3();

	//unselect
	this->csPinSet();
}

void ST7735::select()
{
	this->selected = true;
	this->csPinReset();
}

void ST7735::unselect()
{
	this->selected = false;
	this->csPinSet();
}

void ST7735::setAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    this->sendCommand(ST7735_CASET); // Column addr set
	this->sendData(0x00);            // XS15 ~ XS8
	this->sendData(x0+ST7735_XSTART);     // XSTART       XS7 ~ XS0
	this->sendData(0x00);            // XE15 ~ XE8
	this->sendData(x1+ST7735_XSTART);     // XEND         XE7 ~ XE0

	this->sendCommand(ST7735_RASET); // Row addr set
	this->sendData(0x00);
	this->sendData(y0+ST7735_YSTART);     // YSTART
	this->sendData(0x00);
	this->sendData(y1+ST7735_YSTART);     // YEND

	this->sendCommand(ST7735_RAMWR);
}

uint16_t ST7735::convertColor(float r, float g, float b)
{
	r = CLIPVALUE(r, 0, 1);
	g = CLIPVALUE(g, 0, 1);
	b = CLIPVALUE(b, 0, 1);
	uint8_t R = 0x1F * r;
	uint8_t G = 0x3F * g;
	uint8_t B = 0x1F * b;
	uint16_t color = ST7735_COLOR565(R,G,B);
	return color;
}


bool ST7735::drawPixel(int x, int y, float r, float g, float b)
{
    if(this->selected)
    {
    	if(x >= this->getWidth() or y >= this->getHeight() or x < 0 or y < 0)
    		return false;

    	uint16_t color = ST7735::convertColor(r, g, b);
    	this->setAddressWindow(x, y, x+1, y+1);
    	uint8_t data[2];
    	this->sendData(color >> 8);
    	this->sendData(color & 0xFF);
    	return true;
    }
    else
    {
    	return false;
    }
}

bool ST7735::drawArea(int x1, int y1, int x2, int y2, float r, float g, float b)
{
    if(this->selected)
    {
    	uint32_t w = this->getWidth();
    	uint32_t h = this->getHeight();

    	if(x1 >= w or y1 >= h or x1 >= x2 or y1 >= y2)
    		return false;

    	x1 = (x1 < 0) ? 0 : x1;
    	y1 = (y1 < 0) ? 0 : y1;
    	x2 = CLIPVALUE(x2, x1, w);
    	y2 = CLIPVALUE(y2, y1, h);

    	uint16_t color = ST7735::convertColor(r, g, b);
    	this->setAddressWindow(x1, y1, x2, y2);
    	this->dcPinSet();

    	for(int i = x1; i <= x2; i += 1 )
    	{
    		for(int j = y1; j <= y2; j += 1)
    		{
    			this->sendData(color >> 8);
    			this->sendData(color & 0xFF);
    		}
    	}

    	return true;
    }
    else
    {
    	return false;
    }
}

