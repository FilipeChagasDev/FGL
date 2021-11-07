/*
 * color.hpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <stdint.h>

/**
 * @brief Class that represents a color.
 */
class Color
{
public:
    float a, r, g, b;
    /**
     * @brief Construct a new Color object (black).
     */
    Color();

    /**
     * @brief Construct a new Color object with ``alpha=1``.
     * 
     * @param r Red unitary value.
     * @param g Green unitary value.
     * @param b Blue unitary value.
     */
    Color(float r, float g, float b);

    /**
     * @brief Construct a new Color object.
     * 
     * @param a Alpha unitary value.
     * @param r Red unitary value.
     * @param g Green unitary value.
     * @param b Blue unitary value.
     */
    Color(float a, float r, float g, float b);

    /**
     * @brief Set RGB color values (``alpha=1``).
     * 
     * @param r Red unitary value.
     * @param g Green unitary value.
     * @param b Blue unitary value.
     */
    void setRGB(float r, float g, float b);

    /**
     * @brief Set ARGB color values.
     * 
     * @param a Alpha unitary value.
     * @param r Red unitary value.
     * @param g Green unitary value.
     * @param b Blue unitary value.
     */
    void setARGB(float a, float r, float g, float b);

    /**
     * @brief Destroy the Color object.
     */
    virtual ~Color();
};

/**
 * @brief Create a color object from a rgb888 value.
 * @param rgb 32-bit parameter whose first (most significant) 8 bits are ignored, the next 8 bits are channel R, the next 8 bits are channel G, and the last 8 bits are channel B.
 * @param Unitary alpha value. Default to 1.
 * @return Color object.
 */
Color color_from_rgb888(uint32_t rgb, float alpha = 1.0);

/**
 * @brief Create a color object from a rgba8888 value.
 * @param rgba 32-bit parameter whose first (most significant) 8 bits are channel R, the next 8 bits are channel G, the next 8 bits are channel B, and the last 8 bits are channel A.
 * @return Color object.
 */
Color color_from_rgba8888(uint32_t rgba);


#endif /* COLOR_HPP_ */
