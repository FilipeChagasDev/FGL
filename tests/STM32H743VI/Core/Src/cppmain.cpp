/*
 * cpp_main.cpp
 *
 *  Created on: 21 de out de 2021
 *      Author: Filipe Chagas
 */

#include <stm32h7_st7735.hpp>
#include <main.h>
#include <spi.h>

void cppMain()
{
	STM32H7_ST7735 *tft = new STM32H7_ST7735(TFT_RST_GPIO_Port,
											TFT_RST_Pin,
											TFT_A0_GPIO_Port,
											TFT_A0_Pin,
											TFT_CS_GPIO_Port,
											TFT_CS_Pin,
											&hspi1);

	tft->init();
	tft->select();
	tft->drawArea(0,0, tft->getWidth()-1, tft->getHeight()-1, 0,0,0);
	tft->drawArea(10, 10, tft->getWidth()-10, 20, 1, 0, 0);
	tft->drawArea(10, 30, tft->getWidth()-10, 40, 0, 1, 0);
	tft->drawArea(10, 50, tft->getWidth()-10, 60, 0, 0, 1);
	tft->drawArea(10, 70, tft->getWidth()-10, 80, 1, 1, 1);
	tft->unselect();

	while(true)
	{

	}
}

extern "C" void jumpToCPP()
{
	cppMain();
}


