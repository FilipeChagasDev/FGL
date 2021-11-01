/*
 * font.hpp
 *
 *  Created on: 22 de out de 2021
 *      Author: filipe
 */

#ifndef FONT_HPP_
#define FONT_HPP_

#include <stdint.h>
#include <assert.h>
#include "glyph.hpp"
#include "base/map.hpp"
#include "base/list.hpp"

/**
 * @brief The Font class. This class represents fonts.
 */
class Font
{
private:
    Map<char, Glyph*> glyph_map;
public:
    /**
     * @brief Font constructor.
     */
	Font();

    /**
     * @brief Get glyph of a char.
     * @param c Char.
     * @return Pointer to the Glyph object.
     */
    Glyph* getGlyph(char c);

    /**
     * @brief Set glyph to a char.
     * @param c Char.
     * @param glyph Pointer to the Glyph object.
     */
    void setGlyph(char c, Glyph* glyph);
	virtual ~Font();
};



#endif /* FONT_HPP_ */
