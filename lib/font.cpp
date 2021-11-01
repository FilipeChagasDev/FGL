/*
 * font.cpp
 *
 *  Created on: 22 de out de 2021
 *      Author: filipe
 */

#include "font.hpp"

Font::Font()
{
	// TODO Auto-generated constructor stub

}

Font::~Font()
{
    List<Glyph*> *glyphs = this->glyph_map.listData();

    for(Iterator<Glyph*> it = glyphs->getIteratorBegin(); not it.isNull(); it.foward())
    {
        delete it.getData();
    }

    delete glyphs;
}

Glyph* Font::getGlyph(char c)
{
    Glyph *g = this->glyph_map.find(c)->data;
    assert(g != nullptr);
    return g;
}

void Font::setGlyph(char c, Glyph *glyph)
{
    this->glyph_map.add(c, glyph);
}
