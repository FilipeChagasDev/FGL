/*
 * canvas.h
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef PENCIL_H
#define PENCIL_H

#include <stdint.h>
#include "displays/display.hpp"
#include "fonts/font.hpp"
#include "color.hpp"

class Pencil
{
protected:
	Display *display;
	int w, h;

public:
    Pencil(Display &display);
    virtual void drawPixel(float x, float y, Color color);
	void drawLine(float x1, float y1, float x2, float y2, Color color);
	void drawRectangle(float x, float y, float w, float h, Color color);
	void drawCircle(float x, float y, float radius, Color color, uint32_t vertices = 100);
	void drawEllipse(float x, float y, float w, float h, Color color, uint32_t vertices = 100);
	void drawArc(float x, float y, float theta1, float theta2, float radius, Color color, uint32_t vertices = 100);
	void drawRoundedRectangle(float x, float y, float w, float h, float radius, Color color, uint32_t edge_vertices = 100);
    void drawChar(float x, float y, char c, Font &font, Color color); //unavailable
    void drawText(float x, float y, const char* text, Font &font, Color color); //unavailable
    virtual ~Pencil();
};

#endif /* PENCIL_H */
