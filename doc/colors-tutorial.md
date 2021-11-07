# Using Colors in FGL

This article introduces ways to work with color in FGL.

## The Color class

FGL uses, by default, the **RGB** and **ARGB** color models. In most FGL methods and functions, colors are represented by **Color** objects. These objects have the R, G, B and A channels as float attributes. The values ​​of these channels in the attributes are unitary, that is, they assume real values ​​from 0 to 1.

## Creating a Color object

In general, it is neither necessary nor recommended to create these objects using the ``new`` operator. It is most appropriate to create these objects statically. 

**Note**: Most FGL methods and functions have Color parameters **by value**.

Here are some ways to create these objects:

### Using Color constructors

The Color class has three constructors:
1. ``Color()``, that defines the color as black.
2. ``Color(float r, float g, float b)``, that defines alpha channel as 1. **r**, **g**, and **b** must be unitary (they can only assume values ​​from 0 to 1).
3. ``Color(float a, float r, float g, float b)``. **a**, **r**, **g** and **b** are unitary.
   
Examples:

```c++
//Draw a black line between points [50,50] and [100,100]
pencil.drawLine(50,50,100,100,Color(0,0,0)); 
```

```c++
//Draw a half-transparent red line between points [50,50] and [100,100]
pencil.drawLine(50,50,100,100,Color(0.5,1,0,0)); 
```

```c++
//Draw a white line between points [50,50] and [100,100]
Color white(1,1,1);
pencil.drawLine(50,50,100,100,white); 
```

### Using hexadecimal notation

You can create color objects from hexadecimal color notations using the **color_from_rgb888** and **color_from_rgba8888** functions. These functions are prototyped as follow:

1. ``Color color_from_rgb888(uint32_t rgb, float alpha = 1.0);``, where rgb should receive the color in hexadecimal without alpha. 
2. ``Color color_from_rgba8888(uint32_t rgba);``, where rgb should receive the color in hexadecimal with alpha.

Examples:

```c++
//Draw a Cyan line between points [50,50] and [100,100]
pencil.drawLine(50,50,100,100,color_from_rgb888(0x00FFFF)); 
```

```c++
//Draw a dark-green line between points [50,50] and [100,100]
Color dark_green = color_from_rgb888(0x006400);
pencil.drawLine(50,50,100,100,dark_green); 
```

```c++
//Draw a half-transparent red line between points [50,50] and [100,100]
pencil.drawLine(50,50,100,100,color_from_rgb888(0xFF0000, 0.5)); 
```

```c++
//Draw a half-transparent red line between points [50,50] and [100,100]
pencil.drawLine(50,50,100,100,color_from_rgba8888(0xFF00007F)); 
```
