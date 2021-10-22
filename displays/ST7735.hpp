/*
 * ST7735.h
 *
 *  Created on: 21 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef ST7735_H_
#define ST7735_H_

#include "display.hpp"

class ST7735 : public Display
{
protected:
	Orientation orientation;
	uint32_t v_width_dots;
	uint32_t v_height_dots;
	float v_width_mm;
	float v_height_mm;
	bool selected;

	void initCommand1();
	void initCommand2();
	void initCommand3();
	void sendCommand(uint8_t cmd);
	void sendData(uint8_t data);
	void setAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	int convertOrientationX(int vx, int vy);
	int convertOrientationY(int vx, int vy);
	static uint16_t convertColor(float r, float g, float b);

public:

	ST7735();

	//Name
	const char *getName() override;

	//Properties
	uint32_t getWidth() override;
	uint32_t getHeight() override;
	float getDPMMX() override;
	float getDPMMY() override;

	//Brightness
	void setBrightness(float v) override;
	float getBrightness() override;

	//Orientation
	void setOrientation(Orientation orientation) override;
	Orientation getOrientation() override;

	//Actions
	void init() override;
	void reset() override;
	void select() override;
	void unselect() override;
	bool drawPixel(int x, int y, float r, float g, float b) override;
	bool drawArea(int x1, int y1, int x2, int y2, float r, float g, float b) override;

	//Low-Level Interface
	virtual void initIO() = 0;
	virtual void rstPinSet() = 0;
	virtual void rstPinReset() = 0;
	virtual void dcPinSet() = 0;
	virtual void dcPinReset() = 0;
	virtual void csPinSet() = 0;
	virtual void csPinReset() = 0;
	virtual void sendByte(uint8_t data) = 0;
	virtual void delay(uint8_t ms) = 0;

	virtual ~ST7735();
};

#endif /* ST7735_H_ */
