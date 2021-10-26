/*
 * color.hpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

class Color
{
public:
    float a, r, g, b;
    Color();
    Color(float r, float g, float b);
    Color(float a, float r, float g, float b);
    void setRGB(float r, float g, float b);
    void setARGB(float a, float r, float g, float b);
    virtual ~Color();
};

#endif /* COLOR_HPP_ */
