# F Graphics Library (FGL)

![logo](doc/logo-dark.png)

By Filipe Chagas

F Graphics Library is a C++ library that I created for use in embedded system projects with graphic display. This library is portable to any platform for which there is a C++ compiler with only basic C language features available (such as stdlib, stdint, math and string libraries). You can easily port this library yourself to your platform and your display device by simply inheriting the abstract Display class or one of the generic display drivers available and overriding some methods. Furthermore, you can use Qt to simulate the human-machine interface of your project on desktop using a virtual display class, making the development process more practical and comfortable.

It is not necessary to install FGL on your desktop, just include the directory "lib" (renaming it to "fgl" ) and the other files you need to your project and make the appropriate settings in your IDE or build system.

To learn more about and learn how to use FGL, see the [full documentation](https://fgl.docsforge.com/).

Full documentation page: [fgl.docsforge.com](https://fgl.docsforge.com/)

## Available graphic features
* Abstract display class (implementable for any graphic display)
* Abstract drivers for commercial graphic displays (implementable for any hardware with memory enough)
* Hardware-specific drivers for commercial graphic displays
* **RGB** color model
* Drawing of **dots**, **lines**, **rectangles**, **rectangles with rounded edges**, **circles**, **ellipses**, **arcs**, **polygons** and **images**
* Filling of **rectangles**, **rectangles with rounded edges**, **circles**, **ellipses**, **polygons** and **sectors**
* Optional **anti-aliasing** and **alpha composition**
* Possibility to simulate the human-machine interface with **Qt**

## Available non-graphic features
* List
* Counterclockwise point sorting (selection sort)
* Search for float minimum and maximum values in arrays

## Available display generic drivers 
|Display    |Type       |Color Model   |Communication |Available hardware-specific implementations|
|-----------|-----------|--------------|--------------|-------------------------------------------|
|Qt display |Simulation |RGB888        |              |                                           |
|ST7735     |TFT        |RGB565        |SPI           |STM32F1xx, STM32F4xx, STM32H7xx            |
