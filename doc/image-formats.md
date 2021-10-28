# FGL image formats

FGL has 4 internal image formats:

* ARGB8888
* ARGB1555
* ARGB565
* K8

Converting an image file (such as PNG or JPG) to a usable form in FGL requires using the **fglimg.py** script. See the **fglimg.py script** wiki page. 

See also the **Image** class reference.

## ARGB8888

**Class: ImageARGB8888**

This is the format that provides the best image quality, but it is also the one that takes up the most memory. In this format, each pixel is 32 bits long. Channels ​​A, R, G and B are 8 bits long.

## ARGB1555

**Class: ImageARGB1555**

This format requires 50% of the memory that ARGB8888 requires. In this format, each pixel is 16 bits long. The **Alpha channel is binary**, meaning that each pixel has 0% or 100% transparency. The **R**, **G** and **B** channels ​​are 5 bits long. Color quality in this format is acceptable, but alpha channel binarization may cause some aliasing.

## RGB565

**Class: ImageRGB565**

This format also requires 50% of the memory that ARGB8888 requires. **In this format there is no transparency**, the **R** and **B** channels have 5 bits and the **G** channel has 6 bits. As the **G** channel in RGB565 format has twice the resolution of the G channel in ARGB1555 format, the color quality ends up being a little better. The G channel is chosen to have the extra bit because [our eyes are more sensitive to the green color](https://www.physicsclassroom.com/class/light/Lesson-2/Visible-Light-and-the-Eye-s-Response).

![eye sensitivity](https://www.physicsclassroom.com/Class/light/u12l2b2.gif)

## K8

**Class: ImageK8**

This is the format that consumes the least memory. In this format, a palette of a maximum of 256 colors is stored in the image object. The image is encoded as an array of 8-bit keys. Each matrix key corresponds to a pixel, and each key value is mapped to a color in the palette. This format is ideal for images with few colors. Images that are too colorful or have too many gradients can suffer a severe loss of quality if converted to K8.