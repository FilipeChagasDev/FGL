/*
 * Display.hpp
 *
 *  Created on: 21 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <stdint.h>
/**
 * V = Vertical
 * H = Horizontal
 */
enum class Orientation {V, H};

class Display
{
public:
	//Name
	virtual const char *getName() = 0;

	//Properties
	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
	virtual float getDPMMX() = 0;
	virtual float getDPMMY() = 0;

	//Brightness
	virtual void setBrightness(float v) = 0;
	virtual float getBrightness() = 0;

	//Orientation
	virtual void setOrientation(Orientation orientation) = 0;
	virtual Orientation getOrientation() = 0;

	//Actions
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void select() = 0;
	virtual void unselect() = 0;
	virtual bool drawPixel(int x, int y, float r, float g, float b) = 0;
	virtual bool drawArea(int x1, int y1, int x2, int y2, float r, float g, float b) = 0;

	//Destructor
	virtual ~Display();
};

#endif /* DISPLAY_HPP_ */
