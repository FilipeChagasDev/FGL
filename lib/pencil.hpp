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
#include "image.hpp"

class Pencil
{
protected:
    Display *display;
    int w, h;

public:
    Pencil(Display &display);

    //Draw methods
    virtual void drawPixel(float x, float y, Color color);
    void drawLine(float x1, float y1, float x2, float y2, Color color);
    void drawRectangle(float x, float y, float w, float h, Color color);
    void drawCircle(float x, float y, float radius, Color color, uint32_t vertices = 100);
    void drawEllipse(float x, float y, float w, float h, Color color, uint32_t vertices = 100);
    void drawArc(float x, float y, float theta1, float theta2, float radius, Color color, uint32_t vertices = 100);
    void drawRoundedRectangle(float x, float y, float w, float h, float radius, Color color, uint32_t edge_vertices = 100);
    void drawPolygon(float *x_array, float *y_array, uint32_t len, Color color);
    void drawChar(float x, float y, char c, Font &font, Color color); //unavailable
    void drawText(float x, float y, const char* text, Font &font, Color color); //unavailable
    void drawImage(float x, float y, Image &image);

    //Fill methods
    void fillRectangle(float x, float y, float w, float h, Color color);
    void fillCircle(float x, float y, float radius, Color color);
    void fillEllipse(float x, float y, float w, float h, Color color);
    void fillPolygon(float *x_array, float *y_array, uint32_t len, Color color);
    void fillSector(float x, float y, float theta1, float theta2, float radius, Color color, uint32_t vertices = 100);
    void fillRoundedRectangle(float x, float y, float w, float h, float radius, Color color, uint32_t edge_vertices = 100);

    //Destructor
    virtual ~Pencil();
};

#endif /* PENCIL_H */
