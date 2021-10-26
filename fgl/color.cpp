/*
 * color.cpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#include <color.hpp>

#define CLIPVALUE(v, min, max) (((v) < (min)) ? (min) : (((v) > (max)) ? (max) : (v)))

Color::Color()
{
    this->a = 1;
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color::Color(float r, float g, float b)
{
    this->a = 1;
    this->r = CLIPVALUE(r, 0, 1);
    this->g = CLIPVALUE(g, 0, 1);
    this->b = CLIPVALUE(b, 0, 1);
}

Color::Color(float a, float r, float g, float b)
{
    this->a = CLIPVALUE(a, 0, 1);
    this->r = CLIPVALUE(r, 0, 1);
    this->g = CLIPVALUE(g, 0, 1);
    this->b = CLIPVALUE(b, 0, 1);
}

void Color::setRGB(float r, float g, float b)
{
    this->a = 1;
    this->r = CLIPVALUE(r, 0, 1);
    this->g = CLIPVALUE(g, 0, 1);
    this->b = CLIPVALUE(b, 0, 1);
}

void Color::setARGB(float a, float r, float g, float b)
{
    this->a = CLIPVALUE(a, 0, 1);
    this->r = CLIPVALUE(r, 0, 1);
    this->g = CLIPVALUE(g, 0, 1);
    this->b = CLIPVALUE(b, 0, 1);
}

Color::~Color()
{
    // TODO Auto-generated destructor stub
}

