/*
 * canvas.cpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#include <pencil.hpp>
#include <math.h>
#include <assert.h>
#include <base/ccw_sort.hpp>
#include <base/array_search.hpp>
#include <base/list.hpp>

#define ABS(v) (((v) >= 0) ? (v) : -(v))
#define PI 3.14159265359

Pencil::Pencil(Display &display)
{
    this->display = &display;
    this->w = display.getWidth();
    this->h = display.getHeight();
}

Pencil::~Pencil()
{

}

void Pencil::drawPixel(float x, float y, Color color)
{
    this->display->drawPixel(roundf(x), roundf(y), color.r, color.g, color.b);
}

void Pencil::drawLine(float x1, float y1, float x2, float y2, Color color)
{
    float a = (y2-y1)/(x2-x1);

    if(ABS(a) < 1)
    {
        float bx = (x1 > x2) ? x1 : x2; //bigger x
        float sx = (x1 > x2) ? x2 : x1; //smaller x
        float b = y1 - a*x1;
        for(float x = floorf(sx); x <= bx; x+=1)
        {
            this->drawPixel(x, a*x+b, color);
        }
    }
    else //ABS(A) >= 1
    {
        float by = (y1 > y2) ? y1 : y2; //bigger y
        float sy = (y1 > y2) ? y2 : y1; //smaller y
        float ai = (x2-x1)/(y2-y1);
        float bi = x1 - ai*y1;
        for(float y = floorf(sy); y <= by; y+=1)
        {
            this->drawPixel(ai*y+bi, y, color);
        }
    }

}

void Pencil::drawRectangle(float x, float y, float w, float h, Color color)
{
    assert(w >= 0);
    assert(h >= 0);

    if(w > 0 and h > 0)
    {
        //Horizontal lines
        this->drawLine(x, y, x+w, y, color);
        this->drawLine(x, y+h, x+w, y+h, color);

        //Vertical lines
        this->drawLine(x, y, x, y+h, color);
        this->drawLine(x+w, y, x+w, y+h, color);
    }
}

void Pencil::drawCircle(float x, float y, float radius, Color color, uint32_t vertices)
{
    assert(radius >= 0);
    assert(vertices > 2);

    if(radius > 0)
    {
        float step = 2*PI/(float)vertices;
        float _x_prev = x + radius;
        float _y_prev = y;

        for(float theta = step; theta < 2*PI; theta += step)
        {
            float _x = x + radius*cosf(theta);
            float _y = y + radius*sinf(theta);
            this->drawLine(_x_prev, _y_prev, _x, _y, color);
            _x_prev = _x;
            _y_prev = _y;
        }

        float _x = x + radius*cosf(2*PI);
        float _y = y + radius*sinf(2*PI);
        this->drawLine(_x_prev, _y_prev, _x, _y, color);
    }
}

void Pencil::drawEllipse(float x, float y, float w, float h, Color color, uint32_t vertices)
{
    assert(w >= 0);
    assert(h >= 0);
    assert(vertices > 2);

    if(w > 0 and h > 0)
    {
        float step = 2*PI/(float)vertices;
        float xr = w/2; //x-axis radius
        float yr = h/2; //y-axis radius
        float _x_prev = x + xr;
        float _y_prev = y;

        for(float theta = step; theta < 2*PI; theta += step)
        {
            float _x = x + xr*cosf(theta);
            float _y = y + yr*sinf(theta);
            this->drawLine(_x_prev, _y_prev, _x, _y, color);
            _x_prev = _x;
            _y_prev = _y;
        }

        float _x = x + xr*cosf(2*PI);
        float _y = y + yr*sinf(2*PI);
        this->drawLine(_x_prev, _y_prev, _x, _y, color);
    }
}

void Pencil::drawArc(float x, float y, float theta1, float theta2, float radius, Color color, uint32_t vertices)
{
    assert(radius > 0);
    assert(vertices > 2);

    if(radius > 0 and ABS(theta2-theta1) > 0)
    {
        float step = ABS(theta2-theta1)/(float)vertices;

        float _x_prev = x + radius*cosf(theta1);
        float _y_prev = y + radius*sinf(theta1);

        if(theta2 > theta1) //counter-clockwise rotation
        {
            for(float theta = theta1+step; theta < theta2; theta += step)
            {
                float _x = x + radius*cosf(theta);
                float _y = y + radius*sinf(theta);
                this->drawLine(_x_prev, _y_prev, _x, _y, color);
                _x_prev = _x;
                _y_prev = _y;
            }
        }
        else //clockwise rotation
        {
            for(float theta = theta1-step; theta > theta2; theta -= step)
            {
                float _x = x + radius*cosf(theta);
                float _y = y + radius*sinf(theta);
                this->drawLine(_x_prev, _y_prev, _x, _y, color);
                _x_prev = _x;
                _y_prev = _y;
            }
        }

        float _x = x + radius*cos(theta2);
        float _y = y + radius*sin(theta2);
        this->drawLine(_x_prev, _y_prev, _x, _y, color);
    }
}

void Pencil::drawRoundedRectangle(float x, float y, float w, float h, float radius, Color color, uint32_t edge_vertices)
{
    assert(w >= 0);
    assert(h >= 0);
    assert(radius >= 0);
    assert(edge_vertices > 2);

    if(w > 0 and h > 0 and radius > 0)
    {
        //Horizontal lines
        this->drawLine(x+radius, y, x+w-radius, y, color); //Top
        this->drawLine(x+radius, y+h, x+w-radius, y+h, color); //Bottom

        //Vertical lines
        this->drawLine(x, y+radius, x, y+h-radius, color); //Left
        this->drawLine(x+w, y+radius, x+w, y+h-radius, color); //Right

        //Edges
        this->drawArc(x+radius, y+radius, PI, PI+PI/2, radius, color); //Left-top
        this->drawArc(x+radius, y+h-radius, PI/2, PI, radius, color); //Left-bottom
        this->drawArc(x+w-radius, y+radius, PI+PI/2, 2*PI, radius, color); //Right-top
        this->drawArc(x+w-radius, y+h-radius, 0, PI/2, radius, color); //Right-bottom
    }
}

void Pencil::drawPolygon(float *x_array, float *y_array, uint32_t len, Color color)
{
    assert(len > 2);

    float min_x = min_float(x_array, len);
    float min_y = min_float(y_array, len);
    float max_x = max_float(x_array, len);
    float max_y = max_float(y_array, len);

    ccw_selection_sort(x_array, y_array, len); //sort points counter clockwise

    for(int i = 1; i < len; i++)
    {
        this->drawLine(x_array[i-1], y_array[i-1], x_array[i], y_array[i], color);
    }

    this->drawLine(x_array[len-1], y_array[len-1], x_array[0], y_array[0], color);
}

void Pencil::drawChar(float x, float y, char c, Font &font, Color color)
{
    //TODO
}

void Pencil::drawText(float x, float y, const char* text, Font &font, Color color)
{
    //TODO
}

void Pencil::drawImage(float x, float y, Image &image)
{
    assert(x >= 0);
    assert(y >= 0);

    for(uint32_t i = 0; i < image.getWidth(); i++)
    {
        for(uint32_t j = 0; j < image.getHeight(); j++)
        {
            this->drawPixel(floorf(x)+i, floorf(y)+j, image.getPixel(i, j));
        }
    }
}

void Pencil::fillRectangle(float x, float y, float w, float h, Color color)
{
    assert(w >= 0);
    assert(h >= 0);

    int i_lim = (int)floorf(x+w);
    int j_lim = (int)floorf(y+h);

    for(int i = ceilf(x); i < i_lim; i++)
    {
        for(int j = ceilf(y); j < j_lim; j++)
        {
            this->drawPixel(i, j, color);
        }
    }

    this->drawRectangle(x, y, w, h, color); //Border
}

void Pencil::fillCircle(float x, float y, float radius, Color color)
{
    assert(radius >= 0);

    if(radius > 0)
    {
        float round_radius = roundf(radius);
        for(float i = -round_radius; i <= round_radius; i += 1)
        {
            float k = radius*radius - i*i;
            if(k >= 0)
            {
                float j = sqrtf(k);
                this->drawLine(x+i, y-j, x+i, y+j, color);
            }
        }
    }
}

void Pencil::fillEllipse(float x, float y, float w, float h, Color color)
{
    assert(w >= 0);
    assert(h >= 0);

    if(w > 0 and h > 0)
    {
        float round_radius = roundf(w/2);
        for(float i = -round_radius; i <= round_radius; i += 1)
        {
            float k = w*w - 4*i*i;
            if(k >= 0)
            {
                float j = h*sqrtf(k)/(2*w);
                this->drawLine(x+i, y-j, x+i, y+j, color);
            }
        }
    }
}

void Pencil::fillPolygon(float *x_array, float *y_array, uint32_t len, Color color)
{
    assert(len > 2);

    float min_x = min_float(x_array, len);
    float min_y = min_float(y_array, len);
    float max_x = max_float(x_array, len);
    float max_y = max_float(y_array, len);

    ccw_selection_sort(x_array, y_array, len); //sort points counter clockwise

    for(int i = floorf(min_x); i < ceilf(max_x); i++)
    {
        for(int j = floorf(min_y); j < ceilf(max_y); j++)
        {
            bool inside = true;

            for(int k = 1; k < len; k++)
            {
                float f = (x_array[k]-x_array[k-1])*j + (y_array[k-1]-y_array[k])*i + (x_array[k-1]*y_array[k] - x_array[k]*y_array[k-1]);
                inside = inside and (f >= 0);
            }

            float f = (x_array[0]-x_array[len-1])*j + (y_array[len-1]-y_array[0])*i + (x_array[len-1]*y_array[0] - x_array[0]*y_array[len-1]);
            inside = inside and (f >= 0);
            if(inside) this->drawPixel(i, j, color);
        }
    }
}


void Pencil::fillSector(float x, float y, float theta1, float theta2, float radius, Color color, uint32_t vertices)
{
    assert(radius >= 0);
    assert(vertices > 2);

    if(radius > 0 and ABS(theta2-theta1) > 0)
    {
        List<float> x_list;
        List<float> y_list;
        x_list.pushEnd(x);
        y_list.pushEnd(y);

        float step = ABS(theta2-theta1)/(float)vertices;

        if(theta2 > theta1) //counter-clockwise rotation
        {
            for(float theta = theta1; theta < theta2; theta += step)
            {
                float _x = x + radius*cosf(theta);
                float _y = y + radius*sinf(theta);
                x_list.pushEnd(_x);
                y_list.pushEnd(_y);

                if(ABS(theta-theta1) >= PI/2) //For each PI/2 rotation, paint the half-sector, clear the lists and continue from then on
                {
                    if(x_list.getLen() > 2)
                        this->fillPolygon(x_list.getArray(), y_list.getArray(), x_list.getLen(), color);
                    x_list.clear();
                    y_list.clear();
                    x_list.pushEnd(x);
                    y_list.pushEnd(y);
                    x_list.pushEnd(_x);
                    y_list.pushEnd(_y);
                }
            }
        }
        else //clockwise rotation
        {
            for(float theta = theta1; theta > theta2; theta -= step)
            {
                float _x = x + radius*cosf(theta);
                float _y = y + radius*sinf(theta);
                x_list.pushEnd(_x);
                y_list.pushEnd(_y);

                if(ABS(theta-theta1) >= PI/2) //For each PI/2 rotation, paint the half-sector, clear the lists and continue from then on
                {
                    if(x_list.getLen() > 2)
                        this->fillPolygon(x_list.getArray(), y_list.getArray(), x_list.getLen(), color);
                    x_list.clear();
                    y_list.clear();
                    x_list.pushEnd(x);
                    y_list.pushEnd(y);
                    x_list.pushEnd(_x);
                    y_list.pushEnd(_y);
                }
            }
        }

        float _x = x + radius*cos(theta2);
        float _y = y + radius*sin(theta2);
        x_list.pushEnd(_x);
        y_list.pushEnd(_y);

        if(x_list.getLen() > 2)
            this->fillPolygon(x_list.getArray(), y_list.getArray(), x_list.getLen(), color);

        this->drawArc(x, y, theta1, theta2, radius, color, vertices); //Border
    }
}

void Pencil::fillRoundedRectangle(float x, float y, float w, float h, float radius, Color color, uint32_t edge_vertices)
{
    assert(w >= 0);
    assert(h >= 0);
    assert(radius >= 0);
    assert(edge_vertices > 2);

    if(w > 0 and h > 0 and radius > 0)
    {
        this->fillRectangle(x, y+radius, radius, h-2*radius, color); //Left rectangle
        this->fillRectangle(x+w-radius, y+radius, radius, h-2*radius, color); //Right rectangle
        this->fillRectangle(x+radius, y, w-2*radius, h, color); //Central rectangle

        //Edges
        //this->fillSector(x+radius, y+radius, PI, PI+PI/2, radius, color); //Left-top
        //this->fillSector(x+radius, y+h-radius, PI/2, PI, radius, color); //Left-bottom
        //this->fillSector(x+w-radius, y+radius, PI+PI/2, 2*PI, radius, color); //Right-top
        //this->fillSector(x+w-radius, y+h-radius, 0, PI/2, radius, color); //Right-bottom
        this->fillCircle(x+radius, y+radius, radius, color); //Left-top
        this->fillCircle(x+radius, y+h-radius, radius, color); //Left-bottom
        this->fillCircle(x+w-radius, y+radius, radius, color); //Right-top
        this->fillCircle(x+w-radius, y+h-radius, radius, color); //Right-bottom

        this->drawRoundedRectangle(x, y, w, h, radius, color, edge_vertices);
    }
}
