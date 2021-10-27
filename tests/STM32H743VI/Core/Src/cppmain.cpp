/*
 * cpp_main.cpp
 *
 *  Created on: 21 de out de 2021
 *      Author: Filipe Chagas
 */

#include <stm32h7_st7735.hpp>
#include <pencil.hpp>
#include <color.hpp>
#include <main.h>
#include <spi.h>
#include <math.h>

#define PI 3.14159265359

void cppMain()
{
	STM32H7_ST7735 *tft = new STM32H7_ST7735(TFT_RST_GPIO_Port,
											TFT_RST_Pin,
											TFT_A0_GPIO_Port,
											TFT_A0_Pin,
											TFT_CS_GPIO_Port,
											TFT_CS_Pin,
											&hspi1);

	Pencil canvas(*tft);

	tft->init();
	tft->select();
	tft->drawArea(0,0, tft->getWidth()-1, tft->getHeight()-1, 0,0,0);
	/*

	tft->drawArea(10, 10, tft->getWidth()-10, 20, 1, 0, 0);
	tft->drawArea(10, 30, tft->getWidth()-10, 40, 0, 1, 0);
	tft->drawArea(10, 50, tft->getWidth()-10, 60, 0, 0, 1);
	tft->drawArea(10, 70, tft->getWidth()-10, 80, 1, 1, 1);
	*/

	//canvas.drawLine(10, 10, 50, 60, Color(1,0,0));
	//canvas.drawLine(100, 30, 40, 90, Color(0,1,0));
	//canvas.drawLine(22, 30, 90, 70, Color(0,0,1));

	int mx = tft->getWidth()/2;
	int my = tft->getHeight()/2;

	canvas.drawRectangle(10,10,tft->getWidth()-20,tft->getHeight()-20, Color(1,1,1));

	for(float theta = 0; theta < 2*PI; theta += 0.1)
	{
		canvas.drawLine(mx, my, mx+(double)50*cos(theta), my+(double)50*sin(theta), Color(sin(theta),sin(theta+PI/2),sin(theta+PI)));
	}

	canvas.drawEllipse(mx,my,50,100,Color(1,1,1));
	canvas.drawEllipse(mx,my,50.5,100,Color(1,1,1));

	tft->unselect();

	while(true)
	{

	}
}

extern "C" void jumpToCPP()
{
	cppMain();
}


