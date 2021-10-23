# F. Graphics Library (FGL)
A small graphics library for LCD displays in embedded systems.

## Available graphic features
* Abstract display class (implementable for any graphic display)
* Abstract drivers for commercial graphic displays (implementable for any hardware with memory enough)
* Hardware-specific drivers for commercial graphic displays
* RGB color model
* Drawing of **dots**, **lines**, **rectangles** and **ellipses**

## Available non-graphic features
* List

## Available display generic drivers 
|Display    |Type   |Color Model   |Communication |Available hardware-specific implementations|
|-----------|-------|--------------|--------------|-------------------------------------------|
|ST7735     |TFT    |RGB565        |SPI           |STM32H7xx                                  |
