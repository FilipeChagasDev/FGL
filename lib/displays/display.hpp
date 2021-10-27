/*
 * Display.hpp
 *
 *  Created on: 21 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <stdint.h>

/**
 * V = Vertical
 * VI = Vertical inverted
 * H = Horizontal
 * HI = Horizontal inverted
 */
enum class Orientation {V, VI, H, HI};

/**
 * @brief Abstract class to display devices.
 * 
 */
class Display
{
public:
	/**
	 * @brief Get the name of the display. Ex: "ST7735".
	 * 
	 * @return const char* 
	 */
	virtual const char *getName() = 0;

	/**
	 * @brief Get display width in dots. 
	 * 
	 * @return uint32_t 
	 */
	virtual uint32_t getWidth() = 0;

	/**
	 * @brief Get display height in dots.
	 * 
	 * @return uint32_t 
	 */
	virtual uint32_t getHeight() = 0;

	/**
	 * @brief Get display dots-per-millimeter at the X axis.
	 * 
	 * @return float 
	 */
	virtual float getDPMMX() = 0;

	/**
	 * @brief Get display dots-per-millimeter at the Y axis.
	 * 
	 * @return float 
	 */
	virtual float getDPMMY() = 0;

	/**
	 * @brief Set display brightness.
	 * 
	 * @param v 
	 */
	virtual void setBrightness(float v) = 0;

	/**
	 * @brief Get the current display brightness.
	 * 
	 * @return float 
	 */
	virtual float getBrightness() = 0;

	/**
	 * @brief Set display orientation (V, VI, H or HI).
	 * 
	 * @param orientation 
	 */
	virtual void setOrientation(Orientation orientation) = 0;

	/**
	 * @brief Get display orientation
	 * 
	 * @return Orientation 
	 */
	virtual Orientation getOrientation() = 0;

	/**
	 * @brief Initialize display.
	 * 
	 */
	virtual void init() = 0;

	/**
	 * @brief Reset display.
	 * 
	 */
	virtual void reset() = 0;

	/**
	 * @brief Select display for communication (necessary to SPI and I2C displays).
	 * 
	 */
	virtual void select() = 0;

	/**
	 * @brief Unselect display for communication (necessary to SPI and I2C displays).
	 * 
	 */
	virtual void unselect() = 0;

	/**
	 * @brief Draw a pixel/dot at the screen.
	 * 
	 * @param x X-axis dot location.
	 * @param y Y-axis dot location.
	 * @param r Red unitary value (between 0 and 1).
	 * @param g Green unitary value (between 0 and 1).
	 * @param b Blue unitary value (between 0 and 1).
	 * @return true if the dot was printed at the screen. 
	 * @return false if the dot was not printed at the screen.
	 */
	virtual bool drawPixel(int x, int y, float r, float g, float b) = 0;
	
	/**
	 * @brief Fill a area at the screen with a single color. 
	 * 
	 * @param x1 Initial x-axis area location.
	 * @param y1 Initial y-axis area location.
	 * @param x2 Final x-axis area location.
	 * @param y2 Final y-axis area location.
	 * @param r Red unitary value (between 0 and 1).
	 * @param g Green unitary value (between 0 and 1).
	 * @param b Blue unitary value (between 0 and 1).
	 * @return true if the area (or a part of it) was printed at the screen.
	 * @return false if the area (or a part of it) was not printed at the screen.
	 */
	virtual bool drawArea(int x1, int y1, int x2, int y2, float r, float g, float b) = 0;

	/**
	 * @brief Destroy the Display object.
	 * 
	 */
	virtual ~Display();
};

#endif /* DISPLAY_HPP_ */
