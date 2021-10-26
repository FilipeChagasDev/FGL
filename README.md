# F. Graphics Library (FGL)
By Filipe Chagas

A small graphics library for LCD displays in embedded systems.

## Available graphic features
* Abstract display class (implementable for any graphic display)
* Abstract drivers for commercial graphic displays (implementable for any hardware with memory enough)
* Hardware-specific drivers for commercial graphic displays
* **RGB** color model
* Drawing of **dots**, **lines**, **rectangles**, **rectangles with rounded edges**, **circles**, **ellipses**, **arcs**, **polygons** and **images**
* Filling of **rectangles**, **rectangles with rounded edges**, **circles**, **ellipses**, **polygons** and **sectors**
* Optional **anti-aliasing** and **alpha composition**

## Available non-graphic features
* List
* Counterclockwise point sorting (selection sort)
* Search for float minimum and maximum values in arrays

## Available display generic drivers 
|Display    |Type   |Color Model   |Communication |Available hardware-specific implementations|
|-----------|-------|--------------|--------------|-------------------------------------------|
|ST7735     |TFT    |RGB565        |SPI           |STM32H7xx                                  |
