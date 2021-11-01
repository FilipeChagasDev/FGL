#ifndef GLYPH_HPP
#define GLYPH_HPP

#include <stdint.h>
#include <assert.h>

/**
 * @brief The Glyph class. An FGL glyph is an image that only has the alpha channel.
 * Image color must be set as drawGlyph method argument. Glyphs are mainly used in fonts,
 * but can also be used for icons and logos.
 */
class Glyph
{
public:
    uint8_t *array;
    uint32_t w, h;

    /**
     * @brief Glyph constructor.
     * @param width Glyph width.
     * @param height Glyph height.
     */
    Glyph(uint32_t width, uint32_t height);

    /**
     * @brief Get a pixel value from the glyph.
     * @param x X coordinate to the pixel.
     * @param y Y coordinate to the pixel.
     * @return Pixel (alpha) value.
     */
    uint8_t getPixel(uint32_t x, uint32_t y);

    /**
     * @brief Set value to a pixel.
     * @param x X coordinate to the pixel.
     * @param y Y coordinate to the pixel.
     * @param (Alpha) value.
     */
    void setPixel(uint32_t x, uint32_t y, uint8_t value);
    virtual ~Glyph();
};

#endif // GLYPH_HPP
