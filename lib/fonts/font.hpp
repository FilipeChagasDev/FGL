/*
 * font.hpp
 *
 *  Created on: 22 de out de 2021
 *      Author: filipe
 */

#ifndef FONT_HPP_
#define FONT_HPP_
#include "stdint.h"

class Font
{
public:
	Font();
	virtual float* getCharBuffer(char c, uint32_t &w, uint32_t &h) = 0;
	virtual ~Font();
};

#endif /* FONT_HPP_ */
