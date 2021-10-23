/*
 * canvas.cpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#include <canvas.hpp>
#include <math.h>

#define ABS(v) ((v >= 0) ? v : -v)
#define PI 3.14159265359

Canvas::Canvas(Display &display, bool transparency, bool anti_aliasing)
{
	this->display = &display;
	this->anti_aliasing = anti_aliasing;
	this->transparency = transparency;

	this->w = display.getWidth();
	this->h = display.getHeight();

	if(anti_aliasing or transparency)
	{
		this->r_buffer = new float[display.getWidth()*display.getHeight()];
		this->g_buffer = new float[display.getWidth()*display.getHeight()];
		this->b_buffer = new float[display.getWidth()*display.getHeight()];

		for(int i = 0; i < this->w; i++)
		{
			for(int j = 0; j < this->h; j++)
			{
				this->r_buffer[i*this->w + j] = 0;
				this->g_buffer[i*this->w + j] = 0;
				this->b_buffer[i*this->w + j] = 0;
			}
		}
	}
}

Canvas::~Canvas()
{
	delete this->r_buffer;
	delete this->g_buffer;
	delete this->b_buffer;
}

void Canvas::drawPixel(float x, float y, Color color)
{
	if(this->anti_aliasing and this->transparency)
	{
		int px = x;
		int nx = ceil(x);
		int py = y;
		int ny = ceil(y);

		float apx = x-floor(x);
		float anx = ceil(x)-x;
		float apy = y-floor(y);
		float any = ceil(y)-y;

		this->r_buffer[px*this->w + py] = apx*apy*color.a*color.r - (1-apx*apy*color.a)*this->r_buffer[px*this->w + py];
		this->r_buffer[nx*this->w + py] = anx*apy*color.a*color.r - (1-anx*apy*color.a)*this->r_buffer[nx*this->w + py];
		this->r_buffer[px*this->w + ny] = apx*any*color.a*color.r - (1-apx*any*color.a)*this->r_buffer[px*this->w + ny];
		this->r_buffer[nx*this->w + ny] = anx*any*color.a*color.r - (1-anx*any*color.a)*this->r_buffer[nx*this->w + ny];

		this->g_buffer[px*this->w + py] = apx*apy*color.a*color.g - (1-apx*apy*color.a)*this->g_buffer[px*this->w + py];
		this->g_buffer[nx*this->w + py] = anx*apy*color.a*color.g - (1-anx*apy*color.a)*this->g_buffer[nx*this->w + py];
		this->g_buffer[px*this->w + ny] = apx*any*color.a*color.g - (1-apx*any*color.a)*this->g_buffer[px*this->w + ny];
		this->g_buffer[nx*this->w + ny] = anx*any*color.a*color.g - (1-anx*any*color.a)*this->g_buffer[nx*this->w + ny];

		this->b_buffer[px*this->w + py] = apx*apy*color.a*color.b - (1-apx*apy*color.a)*this->b_buffer[px*this->w + py];
		this->b_buffer[nx*this->w + py] = anx*apy*color.a*color.b - (1-anx*apy*color.a)*this->b_buffer[nx*this->w + py];
		this->b_buffer[px*this->w + ny] = apx*any*color.a*color.b - (1-apx*any*color.a)*this->b_buffer[px*this->w + ny];
		this->b_buffer[nx*this->w + ny] = anx*any*color.a*color.b - (1-anx*any*color.a)*this->b_buffer[nx*this->w + ny];

		this->display->drawPixel(px, py, this->r_buffer[px*this->w + py], this->g_buffer[px*this->w + py], this->b_buffer[px*this->w + py]);
		this->display->drawPixel(nx, py, this->r_buffer[nx*this->w + py], this->g_buffer[nx*this->w + py], this->b_buffer[nx*this->w + py]);
		this->display->drawPixel(px, ny, this->r_buffer[px*this->w + ny], this->g_buffer[px*this->w + ny], this->b_buffer[px*this->w + ny]);
		this->display->drawPixel(nx, ny, this->r_buffer[nx*this->w + ny], this->g_buffer[nx*this->w + ny], this->b_buffer[nx*this->w + ny]);
	}
	else if(this->anti_aliasing and not this->transparency)
	{
		int px = x;
		int nx = ceil(x);
		int py = y;
		int ny = ceil(y);

		float apx = x-floor(x);
		float anx = ceil(x)-x;
		float apy = y-floor(y);
		float any = ceil(y)-y;

		this->r_buffer[px*this->w + py] = apx*apy*color.r - (1-apx*apy)*this->r_buffer[px*this->w + py];
		this->r_buffer[nx*this->w + py] = anx*apy*color.r - (1-anx*apy)*this->r_buffer[nx*this->w + py];
		this->r_buffer[px*this->w + ny] = apx*any*color.r - (1-apx*any)*this->r_buffer[px*this->w + ny];
		this->r_buffer[nx*this->w + ny] = anx*any*color.r - (1-anx*any)*this->r_buffer[nx*this->w + ny];

		this->g_buffer[px*this->w + py] = apx*apy*color.g - (1-apx*apy)*this->g_buffer[px*this->w + py];
		this->g_buffer[nx*this->w + py] = anx*apy*color.g - (1-anx*apy)*this->g_buffer[nx*this->w + py];
		this->g_buffer[px*this->w + ny] = apx*any*color.g - (1-apx*any)*this->g_buffer[px*this->w + ny];
		this->g_buffer[nx*this->w + ny] = anx*any*color.g - (1-anx*any)*this->g_buffer[nx*this->w + ny];

		this->b_buffer[px*this->w + py] = apx*apy*color.b - (1-apx*apy)*this->b_buffer[px*this->w + py];
		this->b_buffer[nx*this->w + py] = anx*apy*color.b - (1-anx*apy)*this->b_buffer[nx*this->w + py];
		this->b_buffer[px*this->w + ny] = apx*any*color.b - (1-apx*any)*this->b_buffer[px*this->w + ny];
		this->b_buffer[nx*this->w + ny] = anx*any*color.b - (1-anx*any)*this->b_buffer[nx*this->w + ny];

		this->display->drawPixel(px, py, this->r_buffer[px*this->w + py], this->g_buffer[px*this->w + py], this->b_buffer[px*this->w + py]);
		this->display->drawPixel(nx, py, this->r_buffer[nx*this->w + py], this->g_buffer[nx*this->w + py], this->b_buffer[nx*this->w + py]);
		this->display->drawPixel(px, ny, this->r_buffer[px*this->w + ny], this->g_buffer[px*this->w + ny], this->b_buffer[px*this->w + ny]);
		this->display->drawPixel(nx, ny, this->r_buffer[nx*this->w + ny], this->g_buffer[nx*this->w + ny], this->b_buffer[nx*this->w + ny]);
	}
	else if(not this->anti_aliasing and this->transparency)
	{
		int rx = x;
		int ry = y;
		this->r_buffer[rx*this->w + ry] = color.a*color.r - (1-color.a)*this->r_buffer[rx*this->w + ry];
		this->g_buffer[rx*this->w + ry] = color.a*color.g - (1-color.a)*this->g_buffer[rx*this->w + ry];
		this->b_buffer[rx*this->w + ry] = color.a*color.b - (1-color.a)*this->b_buffer[rx*this->w + ry];
		this->display->drawPixel(rx, ry, this->r_buffer[rx*this->w + ry], this->g_buffer[rx*this->w + ry], this->b_buffer[rx*this->w + ry]);
	}
	else
	{
		this->display->drawPixel(x, y, color.r, color.g, color.b);
	}
}

void Canvas::drawLine(float x1, float y1, float x2, float y2, Color color)
{
	float a = (y2-y1)/(x2-x1);

	if(ABS(a) < 1)
	{
		float bx = (x1 > x2) ? x1 : x2;
		float sx = (x1 > x2) ? x2 : x1;
		float b = y1 - a*x1;
		for(float x = floor(sx); x <= bx; x+=1)
		{
			this->drawPixel(x, a*x+b, color);
		}
	}
	else //ABS(A) >= 1
	{
		float by = (y1 > y2) ? y1 : y2;
		float sy = (y1 > y2) ? y2 : y1;
		float ai = (x2-x1)/(y2-y1);
		float bi = x1 - ai*y1;
		for(float y = floor(sy); y <= by; y+=1)
		{
			this->drawPixel(ai*y+bi, y, color);
		}
	}

}

void Canvas::drawRectangle(float x, float y, float w, float h, Color color)
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

void Canvas::drawEllipse(float x, float y, float radius, uint32_t vertices, Color color)
{
	if(radius > 0 and vertices > 2)
	{
		float interval = 2*PI/(float)vertices;
		float _x_prev = x + radius;
		float _y_prev = y;
		for(float theta = interval; theta < 2*PI + interval; theta += interval)
		{
			float _x = x + radius*cos(theta);
			float _y = y + radius*sin(theta);
			this->drawLine(_x_prev, _y_prev, _x, _y, color);
			_x_prev = _x;
			_y_prev = _y;
		}
	}
}

void Canvas::drawChar(float x, float y, char c, Font &font, Color color)
{
	//TODO
}

void Canvas::drawText(float x, float y, const char* text, Font &font, Color color)
{
	//TODO
}
