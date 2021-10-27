/*
 * ST7735.h
 *
 *  Created on: 21 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef ST7735_H_
#define ST7735_H_

#include "display.hpp"

/**
 * @brief ST7735 generic driver class. 
 * This class implements ST7735 commands and communication patterns. This class 
 * must be inherited to make hardware-specific drivers. Subclasses must override 
 * all virtual methods defined here as ``=0``. To use ST7735 on your platform,
 * check if there is a hardware-specific ST7735 driver at ``platforms`` folder
 * or implement it yourself (and make a pull request with it, please).
 */
class ST7735 : public Display
{
private:
	void initCommand1();
	void initCommand2();
	void initCommand3();
	void sendCommand(uint8_t cmd);
	void sendData(uint8_t data);
	void setAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	int convertOrientationX(int vx, int vy);
	int convertOrientationY(int vx, int vy);
	static uint16_t convertColor(float r, float g, float b);

protected:
	/**
	 * @brief State of the display orientation.
	 */
	Orientation orientation;

	/**
	 * @brief Display width in dots.
	 */
	uint32_t v_width_dots;

	/**
	 * @brief Display height in dots.
	 */
	uint32_t v_height_dots;

	/**
	 * @brief Display width in millimeters.
	 */
	float v_width_mm;

	/**
	 * @brief Display height millimeters.
	 */
	float v_height_mm;

	/**
	 * @brief Display selection state.
	 */
	bool selected;
	
public:

	ST7735();

	/**
	 * @brief Returns "ST7735".
	 * 
	 * @return const char* 
	 */
	const char *getName() override;

	/**
	 * @brief Returns ST7735 1.77" width in dots. 
	 * If your ST7735 has a different size, you can change this value by inheriting
	 * this class and changing the value of the **v_width_dots** protected attribute.
	 * @return uint32_t 
	 */
	uint32_t getWidth() override;

	/**
	 * @brief Returns ST7735 1.77" width in dots.
	 * If your ST7735 has a different size, you can change this value by inheriting
	 * this class and changing the value of the **v_height_dots** protected attribute.
	 * @return uint32_t 
	 */
	uint32_t getHeight() override;

	/**
	 * @brief Returns ST7735 1.77" X-axis dots-per-millimeter. 
	 * If your ST7735 has a different size, you can change this value by inheriting
	 * this class and changing the value of the **v_width_dots** and **v_width_mm**
	 * protected attributes.
	 * @return float 
	 */
	float getDPMMX() override;
	
	/**
	 * @brief Returns ST7735 1.77" Y-axis dots-per-millimeter. 
	 * If your ST7735 has a different size, you can change this value by inheriting
	 * this class and changing the value of the **v_height_dots** and **v_height_mm**
	 * protected attribute.
	 * @return float 
	 */
	float getDPMMY() override;

	/**
	 * @brief This method has no action.(TODO).
	 * 
	 * @param v 
	 */
	void setBrightness(float v) override;
	
	/**
	 * @brief Returns 1.
	 * 
	 * @return float 
	 */
	float getBrightness() override;

	/**
	 * @brief This function has no action (TODO).
	 * 
	 * @param orientation 
	 */
	void setOrientation(Orientation orientation) override;
	
	/**
	 * @brief Returns Orientation::V.
	 * 
	 * @return Orientation 
	 */
	Orientation getOrientation() override;

	
	/**
	 * @brief Send commands to initialize ST7735.
	 * 
	 */
	void init() override;
	
	/**
	 * @brief Send commands to reset ST7735.
	 * 
	 */
	void reset() override;

	/**
	 * @brief Send command to select ST7735.
	 * ST7735 must be selected to enable drawning.
	 */
	void select() override;
	
	/**
	 * @brief Send command to unselect ST7735.
	 * ST7735 must be selected to enable drawning.
	 */
	void unselect() override;

	/**
	 * @brief Send command to draw a pixel/dot.
	 * 
	 * @param x X-axis dot location.
	 * @param y Y-axis dot location.
	 * @param r Red unitary value.
	 * @param g Green unitary value.
	 * @param b Blue unitary value.
	 * @return true if the pixel was printed.
	 * @return false if the pixel was not printed.
	 */
	bool drawPixel(int x, int y, float r, float g, float b) override;

	/**
	 * @brief Send command to fill a area with a single color.
	 * Use it to clear the screen, it's fastest as **Pencil::fillRectangle**.
	 * 
	 * @param x1 X-axis initial area location.
	 * @param y1 Y-axis initial area location.
	 * @param x2 X-axis final area location.
	 * @param y2 Y-axis final area location.
	 * @param r Red unitary value.
	 * @param g Green unitary value.
	 * @param b Blue unitary value.
	 * @return true if the area (or a part of it) was printed. 
	 * @return false if nothing was printed.
	 */
	bool drawArea(int x1, int y1, int x2, int y2, float r, float g, float b) override;

	/**
	 * @brief Virtual method to initialize GPIOs connected to **RST**, **DC** and **CS**.
	 * Override it to make a hardware-specific driver.
	 */
	virtual void initIO() = 0;

	/**
	 * @brief Virtual method to set **RST** pin as **high** logic level.
	 * Override it to make a hardware-specific driver.
	 */
	virtual void rstPinSet() = 0;

	/**
	 * @brief Virtual method to set **RST** pin as **low** logic level.
	 * Override it to make a hardware-specific driver.
	 */
	virtual void rstPinReset() = 0;

	/**
	 * @brief Virtual method to set **DC** pin as **high** logic level.
	 * Override it to make a hardware-specific driver.
	 */
	virtual void dcPinSet() = 0;

	/**
	 * @brief Virtual method to set **DC** pin as **low** logic level.
	 * Override it to make a hardware-specific driver.
	 */
	virtual void dcPinReset() = 0;

	/**
	 * @brief Virtual method to set **CS** pin as **high** logic level.
	 * Override it to make a hardware-specific driver.
	 */
	virtual void csPinSet() = 0;

	/**
	 * @brief Virtual method to set **CS** pin as **low** logic level.
	 * Override it to make a hardware-specific driver.
	 */
	virtual void csPinReset() = 0;

	/**
	 * @brief Virtual method to send a byte via SPI to the ST7735 display.
	 * Override it to make a hardware-specific driver.
	 * @param data 
	 */

	virtual void sendByte(uint8_t data) = 0;
	/**
	 * @brief Virtual method to delay.
	 * Override it to make a hardware-specific driver.
	 * @param ms Delay time in milliseconds.
	 */
	virtual void delay(uint8_t ms) = 0;

	/**
	 * @brief Destroy the ST7735 object.
	 * 
	 */
	virtual ~ST7735();
};

#endif /* ST7735_H_ */
