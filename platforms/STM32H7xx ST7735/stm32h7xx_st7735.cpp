/*
 * stm32h7_st7735.cpp
 *
 *  Created on: 21 de out de 2021
 *      Author: filipe
 */

#include <stm32h7xx_st7735.hpp>

STM32H7_ST7735::STM32H7_ST7735(GPIO_TypeDef *rst_port,
		uint16_t rst_pin,
		GPIO_TypeDef *dc_port,
		uint16_t dc_pin,
		GPIO_TypeDef *cs_port,
		uint16_t cs_pin,
		SPI_HandleTypeDef *hspi) : ST7735()
{
	this->rst_port = rst_port;
	this->rst_pin = rst_pin;
	this->dc_port = dc_port;
	this->dc_pin = dc_pin;
	this->cs_port = cs_port;
	this->cs_pin = cs_pin;
	this->hspi = hspi;
}

STM32H7_ST7735::~STM32H7_ST7735()
{
	// TODO Auto-generated destructor stub
}

void STM32H7_ST7735::initIO()
{
	HAL_SPI_Init(this->hspi);
}

void STM32H7_ST7735::rstPinSet()
{
	HAL_GPIO_WritePin(this->rst_port, this->rst_pin, GPIO_PIN_SET);
}

void STM32H7_ST7735::rstPinReset()
{
	HAL_GPIO_WritePin(this->rst_port, this->rst_pin, GPIO_PIN_RESET);
}

void STM32H7_ST7735::dcPinSet()
{
	HAL_GPIO_WritePin(this->dc_port, this->dc_pin, GPIO_PIN_SET);
}

void STM32H7_ST7735::dcPinReset()
{
	HAL_GPIO_WritePin(this->dc_port, this->dc_pin, GPIO_PIN_RESET);
}

void STM32H7_ST7735::csPinSet()
{
	HAL_GPIO_WritePin(this->cs_port, this->cs_pin, GPIO_PIN_SET);
}

void STM32H7_ST7735::csPinReset()
{
	HAL_GPIO_WritePin(this->cs_port, this->cs_pin, GPIO_PIN_RESET);
}

void STM32H7_ST7735::sendByte(uint8_t data)
{
	HAL_SPI_Transmit(this->hspi, &data, 1, 0x1);
}

void STM32H7_ST7735::delay(uint8_t ms)
{
	HAL_Delay(ms);
}
