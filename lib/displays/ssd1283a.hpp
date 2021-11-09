#ifndef SSD1283A_HPP
#define SSD1283A_HPP

#include "display.hpp"
#include <stdint.h>

class SSD1283A : public Display
{
public:
    uint8_t rotation;
    uint8_t inversion_bit;
    float brightness;
    void sendCommand(uint8_t command);
    void sendByteData(uint8_t data);
    void sendHalfWordData(uint16_t data);
    void initCommands();
    void setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y2);
    void setRotation(uint8_t r);
protected:
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

public:
    SSD1283A();

    /**
     * @brief Return "SSD1283A".
     *
     * @return const char*
     */
    virtual const char *getName() override;

    /**
     * @brief Get display width in dots.
     *
     * @return uint32_t
     */
    virtual uint32_t getWidth() override;

    /**
     * @brief Get display height in dots.
     *
     * @return uint32_t
     */
    virtual uint32_t getHeight() override;

    /**
     * @brief Get display dots-per-millimeter at the X axis.
     *
     * @return float
     */
    virtual float getDPMMX() override;

    /**
     * @brief Get display dots-per-millimeter at the Y axis.
     *
     * @return float
     */
    virtual float getDPMMY() override;

    /**
     * @brief Set display brightness.
     *
     * @param v
     */
    virtual void setBrightness(float v) override;

    /**
     * @brief Get the current display brightness.
     *
     * @return float
     */
    virtual float getBrightness() override;

    /**
     * @brief Set display orientation (V, VI, H or HI).
     *
     * @param orientation
     */
    virtual void setOrientation(Orientation orientation) override;

    /**
     * @brief Get display orientation
     *
     * @return Orientation
     */
    virtual Orientation getOrientation() override;

    /**
     * @brief Initialize display.
     *
     */
    virtual void init() override;

    /**
     * @brief Reset display.
     *
     */
    virtual void reset() override;

    /**
     * @brief Select display for communication (necessary to SPI and I2C displays).
     *
     */
    virtual void select() override;

    /**
     * @brief Unselect display for communication (necessary to SPI and I2C displays).
     *
     */
    virtual void unselect() override;

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
    virtual bool drawPixel(int x, int y, float r, float g, float b) override;

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
    virtual bool drawArea(int x1, int y1, int x2, int y2, float r, float g, float b) override;


    /**
     * @brief Virtual method to initialize GPIOs connected to **RST**, **DC** and **CS**.
     * **Override it to make a hardware-specific driver.**
     */
    virtual void initIO() = 0;

    /**
     * @brief Virtual method to set **CS** pin as **high** logic level.
     * **Override it to make a hardware-specific driver.**
     */
    virtual void csPinSet() = 0;

    /**
     * @brief Virtual method to set **CS** pin as **low** logic level.
     * **Override it to make a hardware-specific driver.**
     */
    virtual void csPinReset() = 0;

    /**
     * @brief Virtual method to set **CD** pin as **high** logic level.
     * **Override it to make a hardware-specific driver.**
     */
    virtual void cdPinSet() = 0;

    /**
     * @brief Virtual method to set **CD** pin as **low** logic level.
     * **Override it to make a hardware-specific driver.**
     */
    virtual void cdPinReset() = 0;

    /**
     * @brief Virtual method to set **RST** pin as **high** logic level.
     * **Override it to make a hardware-specific driver.**
     */
    virtual void rstPinSet() = 0;

    /**
     * @brief Virtual method to set **RST** pin as **low** logic level.
     * **Override it to make a hardware-specific driver.**
     */
    virtual void rstPinReset() = 0;

    /**
     * @brief Virtual method to set a duty cycle or voltage value to the **LED** pin.
     * **Override it to make a hardware-specific driver.**
     * @param Unitary value (can be from 0 to 1).
     */
    virtual void setLedValue(float value) = 0;

    /**
     * @brief Virtual method to send a byte via SPI to the SSD1283A display.
     * **Override it to make a hardware-specific driver.**
     * @param 8-bit data.
     */
    virtual void sendByte(uint8_t data) = 0;

    /**
     * @brief Virtual method to send a half-word via SPI to the SSD1283A display.
     * **Override it to make a hardware-specific driver.**
     * @param 16-bit data.
     */
    virtual void sendHalfWord(uint16_t data) = 0;

    /**
     * @brief Virtual method to delay.
     * **Override it to make a hardware-specific driver.**
     * @param ms Delay time in milliseconds.
     */
    virtual void delay(uint8_t ms) = 0;

    virtual ~SSD1283A();
};

#endif // SSD1283A_HPP
