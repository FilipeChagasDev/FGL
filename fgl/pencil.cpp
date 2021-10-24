/*
 * canvas.cpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#include <pencil.hpp>
#include <math.h>

#define ABS(v) ((v >= 0) ? v : -v)
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
	if(radius > 0 and vertices > 2)
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
	if(vertices > 2)
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
	if(radius > 0 and vertices > 2 and theta2 > theta1)
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
	if(w > 0 and h > 0 and edge_vertices > 2)
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

void Pencil::drawChar(float x, float y, char c, Font &font, Color color)
{
	//TODO
}

void Pencil::drawText(float x, float y, const char* text, Font &font, Color color)
{
	//TODO
}
