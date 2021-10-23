/*
 * canvas.h
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef CANVAS_HPP_
#define CANVAS_HPP_

#include <stdint.h>
#include "displays/display.hpp"
#include "fonts/font.hpp"
#include "color.hpp"

class Canvas
{
protected:
	Display *display;
	bool anti_aliasing;
	bool transparency;
	float *r_buffer;
	float *g_buffer;
	float *b_buffer;
	int w, h;

public:
	Canvas(Display &display, bool transparency = false, bool anti_aliasing = false);
	void drawPixel(float x, float y, Color color);
	void drawLine(float x1, float y1, float x2, float y2, Color color);
	void drawRectangle(float x, float y, float w, float h, Color color);
	void drawEllipse(float x, float y, float radius, uint32_t vertices, Color color);
	void drawChar(float x, float y, char c, Font &font, Color color);
	void drawText(float x, float y, const char* text, Font &font, Color color);
	virtual ~Canvas();
};

#endif /* CANVAS_HPP_ */
