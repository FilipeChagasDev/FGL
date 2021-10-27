# FGLIMG script

To use an image from a file (such as a PNG or JPG) in FGL, it is necessary to convert the image file to a C++ code responsible for generating an **Image** object with the same content as the image file. The **fglimg.py** Python script is responsible for converting image files into C++ code for use with FGL.

## Usage
This script must be used at the terminal. With "tools" as working directory, type the command **"python fglimg.py *INPUT* *OUTPUT*"**, where ***INPUT*** is the input image file path and ***OUTPUT*** is the output code name (not the file name). This usage of **fglimg.py** will generate a pair of C++ code files (header and source) with a function to generate a Image object with the input image contents.

## Parameters
*   **input_image** : Input image file path. 
*   **output_name** : Name to the output code (not file name). This name must comply with the C++ identifier regex ***"(\[a-zA-Z\]\|\_)(\[a-zA-Z\]|[0-9]|_)\*"***.
*   **--fname *NAME* (Optional)** : Changes the name of the output function. Default is the same name as output code.
*   **--dir *PATH* (Optional)** : Defines a root directory to header and source files. Default is '.' directory.
*   **--format *FORMAT* (Optional)** : Changes the target FGL image format. The ***FORMAT*** options are **ARGB8888**, **ARGB1555**, **RGB565** and **K8**. Default is **ARGB8888**.
*   **--resize *WIDTH* *HEIGHT* (Optional)** : Defines, respectively, width and height to the output FGL image. Default is the same size of the original image.
*   **--ncolors *NUMBER* (Optional)** : If **K8** format is chosen, it defines a number of colors to be extracted. By default, the script finds the better number of colors to the K8 pallete using elbow method.

**IMPORTANT:** To generate **K8** images, **fglimg.py** uses **sklearn** and **numpy**, so you must install these dependences with **pip** before using the script with **--format** set as **K8**. **For other formats, no need to install dependencies.**

## Examples:

```sh
python fglimg.py myfold/myimage.png myimage
```

This command line will generate **myimage.hpp** and **myimage.cpp**. These code files will contains the **myimage** function, prototyped as ``Image *myimage();``. **myimage** will returns a pointer to a **ImageARGB8888** object with the same contents as **myimage.png**.

```sh
python fglimg.py myfold/myimage.png myimage --dir mycodefold --fname get_myimage --format ARGB1555 --resize 32 32
```

This command line will generate ``mycodefold/myimage.hpp`` and ``mycodefold/myimage.cpp``. These code files will contains the **get_myimage** function, prototyped as ``Image *get_myimage();``. **get_myimage** will returns a pointer to a **ImageARGB1555** object with the same contents as "myimage.png" resized to ``[width,height]=[32,32]``.

```sh
python fglimg.py myfold/myimage.png myimage --dir mycodefold --fname get_myimage --format K8 --ncolors 10
```

This command line will generate ``mycodefold/myimage.hpp`` and ``mycodefold/myimage.cpp``. These code files will contains the "get_myimage" function, prototyped as ``Image *get_myimage();``. **get_myimage** will returns a pointer to a ImageK8 object with the same contents as **myimage.png** and 10 colors in the pallete.