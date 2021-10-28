/*
 * color.hpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

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

#endif /* COLOR_HPP_ */
