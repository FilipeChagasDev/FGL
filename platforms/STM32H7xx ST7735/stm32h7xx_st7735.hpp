/*
 * stm32h7_st7735.h
 *
 *  Created on: 21 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef STM32H7XX_ST7735_HPP
#define STM32H7XX_ST7735_HPP

#include <displays/ST7735.hpp>
#include <stm32h7xx_hal.h>

class STM32H7_ST7735 : public ST7735
{
protected:
	GPIO_TypeDef *rst_port;
	uint16_t rst_pin;
	GPIO_TypeDef *dc_port;
	uint16_t dc_pin;
	GPIO_TypeDef *cs_port;
	uint16_t cs_pin;
	SPI_HandleTypeDef *hspi;

public:
	STM32H7_ST7735(GPIO_TypeDef *rst_port,
				uint16_t rst_pin,
				GPIO_TypeDef *dc_port,
				uint16_t dc_pin,
				GPIO_TypeDef *cs_port,
				uint16_t cs_pin,
				SPI_HandleTypeDef *hspi);
	
	//Low-Level Interface
	void initIO() override;
	void rstPinSet() override;
	void rstPinReset() override;
	void dcPinSet() override;
	void dcPinReset() override;
	void csPinSet() override;
	void csPinReset() override;
	void sendByte(uint8_t data) override;
	void delay(uint8_t ms) override;

	virtual ~STM32H7_ST7735();
};

#endif /* INC_STM32H7_ST7735_HPP_ */
