# Basic usage tutorial - Drawing with the Pencil

## An introductory example with ST7735 and STM32H7xx

After the entire process of adding FGL to the project has been completed, you can start programming with it. First, you should understand the heart of FGL's basic features: the **Display** and **Pencil** classes. Actually, the Display class is just an interface, what you're really going to use is a platform-specific display driver. As an example, let's use the **ST7735** display driver for the **STM32H7xx** microcontroller line.

### 1. HAL generation

Using the **STM32CubeMX** tool, generate a HAL with the SPI communicator and all GPIOs properly configured to communicate with the ST7735. **The code must have global asserts enabled** and must be generated for the **STM32CubeIDE**.

STM32CubeMX by default only generates C libraries. To program in C++ using the generated HAL, you need to convert the HAL to C++ using the STM32CubeIDE.

### 2. Creating a main function in C++

First, you must declare a function called **jumpToCPP** in **main.h**.

```c
/* USER CODE BEGIN EFP */
void jumpToCPP();
/* USER CODE END EFP */
```

After that, you create a file called **main.cpp** and make the following definitions:

```c++
//HAL includes
#include <main.h>
#include <spi.h>

//FGL includes
#include <stm32h7_st7735.hpp>
#include <pencil.hpp>

/* -- global code section begin -- */

/* -- global code section end -- */

void cppMain()
{
    /* -- setup code section begin -- */

    /* -- setup code section end -- */

	while(true)
    {
        /* -- loop code section begin -- */

        /* -- loop code section end -- */
    }
}

extern "C" void jumpToCPP()
{
	cppMain();
}
```
Note that there are three sections in the code: **global**, **setup** and **loop**. Keep these three names in mind as they will be used throughout the article to reference these sections of code.

### 3. Instantiating the display driver

Suppose the SPI communicator handler is **hspi1** and the GPIOs are labeled as **TFT_RST**, **TFT_A0** and **TFT_CS**.

You should now instance the display driver in the **global** section as follows:

```c++
STM32H7_ST7735 display(TFT_RST_GPIO_Port,
					TFT_RST_Pin,
					TFT_A0_GPIO_Port,
					TFT_A0_Pin,
					TFT_CS_GPIO_Port,
					TFT_CS_Pin,
					&hspi1);
```

### 4. Clearing the screen

To start rendering on the display, you must initialize it using the **init** method, select it for communication using the **select** method and clear the screen using the **drawArea** method. The screen background color will be black. 

Put the following code in the **setup** section:

```c++
display.init();
display.select();
display.drawArea(0, 0, display->getWidth()-1, display->getHeight()-1, 0, 0, 0);
```

### 5. Instantiating a pencil

In the setup section, instantiate the pencil as follows:

```c++
Pencil pencil(display);
```

If you want to use anti-aliasing and alpha compositing, you should use the **BufferedPencil** class instead of **Pencil**. Drawing with this class is slower and consumes more memory, so test and think if it's really worth using.

```c++
BufferedPencil pencil(display, Color(0,0,0));
```

Now you can draw on the screen using the methods of the **Pencil** class. Consult the documentation to find out about them.

### Summing up

The resulting code is as follows:

```c++
//HAL includes
#include <main.h>
#include <spi.h>

//FGL includes
#include <stm32h7_st7735.hpp>
#include <pencil.hpp>

/* -- global code section begin -- */
STM32H7_ST7735 display(TFT_RST_GPIO_Port,
					TFT_RST_Pin,
					TFT_A0_GPIO_Port,
					TFT_A0_Pin,
					TFT_CS_GPIO_Port,
					TFT_CS_Pin,
					&hspi1);
/* -- global code section end -- */

void cppMain()
{
    /* -- setup code section begin -- */
	display.init();
	display.select();
	display.drawArea(0, 0, display->getWidth()-1, display->getHeight()-1, 0, 0, 0);

	Pencil pencil(display); //use BufferedPencil to enable anti-aliasing and alpha-composition (transparency)

	//use the methods of Pencil to draw on the screen

    /* -- setup code section end -- */

	while(true)
    {
        /* -- loop code section begin -- */

        /* -- loop code section end -- */
    }
}

extern "C" void jumpToCPP()
{
	cppMain();
}
```