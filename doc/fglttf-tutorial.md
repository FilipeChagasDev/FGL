# FGLTTF script

To use a font from a TTF file in FGL, it is necessary to convert the TTF file to a C++ code responsible for generating an **Font** object with similar content as the TTF file. The **fglttf.py** Python script is responsible for converting TTF files into C++ code for use with FGL.

## Usage
This script must be used at the terminal. With "scripts" as working directory,
type the command ``python fglttf.py input output``, where ``input`` is the
input TTF file path and ``output`` is the output code name (not the file name).
This usage of fglttf.py will generate a pair of C++ code files (header and source)
with a function to generate a Font object with the input TTF contents.

## Parameters:
* **input_font** : Input TTF file path. 
* **output_name** : Name to the output code (not file name). This name must comply with the C++ identifier regex ***"(\[a-zA-Z\]\|\_)(\[a-zA-Z\]|[0-9]|_)\*"***.   
* **--fname *NAME* (Optional)**: Changes the name of the output function. Default is the same name as output code.
* **--dir *PATH* (Optional)** : Defines a root directory to header and source files. Default is '.' directory.
* **--size *SIZE* (Optional)**: Defines the output FGL font size. Default is 10px.

## Examples

```sh
python fglttf.py myfold/myfont.ttf myfont
```

This command line will generate **myfont.hpp** and **myfont.cpp**. These code files will contains the **myfont** function, prototyped as ``Font *myfont();``. **myfont** will returns a pointer to a Font object.

```sh
python fglttf.py myfold/myfont.ttf myfont --dir mycodefold --fname get_myfont --size 12
```

This command line will generate **mycodefold/myfont.hpp** and **mycodefold/myfont.cpp**. These code files will contains the **get_myfont** function, prototyped as ``Font *get_myfont();``. **get_myfont** will returns a pointer to a Font object with a 12px font similar to **myfont.ttf**.
