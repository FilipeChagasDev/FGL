# File: fglimg.py
# Author: Filipe Chagas
# Date: october-2021
# Brief: This script generates C++ code with the contents of a image file for 
#        using with FGL.
#
# Usage:
#    This script must be used at the terminal. With "scripts" as working directory,
#    type the command "python fglimg.py <input> <output>", where <input> is the
#    input image file path and <output> is the output code name (not the file name).
#    This usage of fglimg.py will generate a pair of C++ code files (header and source)
#    with a function to generate a Image object with the input image contents.
#
# Example:
#   '''sh
#    python fglimg.py myfold/myimage.png myimage
#   '''
#    This command line will generate "myimage.hpp" and "myimage.cpp". These code files
#    will contains the "myimage" function, prototyped as "Image *myimage();". "myimage"
#    will returns a pointer to a ImageARGB8888 object with the same contents as "myimage.png".
#
# Optional parameters:
#   --fname <string> : Changes the name of the output function. Default is the same name as output code.
#   --dir <string> : Defines a root directory to header and source files. Default is '.' directory.
#   --format {ARGB8888, ARGB1555, RGB565, K8} : Changes the target FGL image format. Default is ARGB8888.
#   --resize <int> <int> : Defines, respectively, width and height to the output FGL image. Default is the same size of the original image.
#   --ncolors <int> : If K8 format is chosen, defines a number of colors to be extracted. By default, the script finds the better number of colors using elbow method.
#
# Note:
#   To generate K8 images, fglimg.py uses sklearn and numpy, so you must install these dependences with pip
#   before using the script with --format set to K8. For other formats, no need to install dependencies.
#
# Example:
#   '''sh
#    python fglimg.py myfold/myimage.png myimage --dir mycodefold --fname get_myimage --format ARGB1555 --resize 32 32
#   '''
#    This command line will generate "mycodefold/myimage.hpp" and "mycodefold/myimage.cpp". These code files
#    will contains the "get_myimage" function, prototyped as "Image *get_myimage();". "get_myimage" will returns  
#    a pointer to a ImageARGB1555 object with the same contents as "myimage.png" resized to [width,height]=[32,32].
#
# Example:
#   '''sh
#    python fglimg.py myfold/myimage.png myimage --dir mycodefold --fname get_myimage --format K8 --ncolors 10
#   '''
#    This command line will generate "mycodefold/myimage.hpp" and "mycodefold/myimage.cpp". These code files
#    will contains the "get_myimage" function, prototyped as "Image *get_myimage();". "get_myimage" will returns  
#    a pointer to a ImageK8 object with the same contents as "myimage.png" and 10 colors in the pallete.

from PIL import Image
from datetime import datetime
import argparse
import os
import re
from typing import *

today_date = datetime.today().strftime('%Y-%m-%d')

def open_image_file(image_file_name: str) -> Image.Image:
    if(not os.path.exists(image_file_name)):
        print(f'No such file or directory: {image_file_name}')
        exit()

    if(not os.path.isfile(image_file_name)):
        print(f'Path is not a file: {image_file_name}')
        exit()
    
    try:
        img = Image.open(image_file_name, mode='r')
    except:
        print(f'Cannot open file as image: {image_file_name}')
        exit()

    return img

def check_cpp_identifier(txt: str) -> bool:
    matching = re.match('([a-zA-Z]|_)([a-zA-Z]|[0-9]|_)*', txt)
    if matching != None:
        return matching.span() == (0, len(txt))
    else:
        return False

def get_header_text(image_file_name: str, fgl_format: str, function_name: str, file_name: str) -> str:
    text = (
        '/* -- F. Graphics Library (FGL) --\n'
        f' * File: {file_name}.hpp\n'
        ' *\n'
        ' * This code file generated by the img_to_fgl.py script\n'
        ' * contains the contents of an image file adapted to\n'
        ' * using with FGL\n'
        ' *\n'
        f' * Original image file: {os.path.split(image_file_name)[1]}\n'
        f' * FGL image format: {fgl_format}\n'
        f' * Generation date (Y-M-D): {today_date}\n'
        ' */\n'
        f'#ifndef {file_name.upper()}_HPP\n'
        f'#define {file_name.upper()}_HPP\n'
        '\n'
        f'#include <image.hpp>\n'
        '\n'
        f'Image *{function_name}();\n'
        '\n'
        '#endif\n'
    )
    return text

def get_source_argb8888(img: Image.Image, function_name: str, file_name: str) -> str:
    image = img.convert('RGBA')

    text = (
        '/* -- F. Graphics Library (FGL) --\n'
        f' * File: {file_name}.cpp\n'
        ' *\n'
        ' * This code file generated by the img_to_fgl.py script\n'
        ' * contains the contents of an image file adapted to\n'
        ' * using with FGL\n'
        ' *\n'
        f' * FGL image format: ARGB8888\n'
        f' * Generation date (Y-M-D): {today_date}\n'
        ' */\n'
        f'#include \"{file_name}.hpp\"\n'
        '\n'
        f'Image *{function_name}()\n'
        '{\n'
        f'\tImageARGB8888 *myimg = new ImageARGB8888({image.width}, {image.height});\n'
    )

    for x in range(image.width):
        for y in range(image.height):
            print(f'({int(((x*image.width + y)/(image.width*image.height))*100)}%) generating code...', end='\r')
            pixel = image.getpixel((x,y))
            text += f'\tmyimg->r_array[{x*image.width + y}] = {hex(pixel[0])};\n'
            text += f'\tmyimg->g_array[{x*image.width + y}] = {hex(pixel[1])};\n'
            text += f'\tmyimg->b_array[{x*image.width + y}] = {hex(pixel[2])};\n'
            text += f'\tmyimg->a_array[{x*image.width + y}] = {hex(pixel[3])};\n'

    text += (
        '\treturn myimg;\n'
        '}\n'
    )

    print('(100%) generating code...')
    return text

def get_source_argb1555(img: Image.Image, function_name: str, file_name: str) -> str:
    image = img.convert('RGBA')

    text = (
        '/* -- F. Graphics Library (FGL) --\n'
        f' * File: {file_name}.cpp\n'
        ' *\n'
        ' * This code file generated by the img_to_fgl.py script\n'
        ' * contains the contents of an image file adapted to\n'
        ' * using with FGL\n'
        ' *\n'
        f' * FGL image format: ARGB1555\n'
        f' * Generation date (Y-M-D): {today_date}\n'
        ' */\n'
        f'#include \"{file_name}.hpp\"\n'
        '\n'
        f'Image *{function_name}()\n'
        '{\n'
        f'\tImageARGB1555 *myimg = new ImageARGB1555({image.width}, {image.height});\n'
    )

    for x in range(image.width):
        for y in range(image.height):
            print(f'({int(((x*image.width + y)/(image.width*image.height))*100)}%) generating code...', end='\r')
            pixel = image.getpixel((x,y))
            a = int(round(pixel[3]/255)) & 0x01
            r = int(round((pixel[0]/255)*0x1F)) & 0x1F
            g = int(round((pixel[1]/255)*0x1F)) & 0x1F
            b = int(round((pixel[2]/255)*0x1F)) & 0x1F
            px = (a << 15) | (r << 10) | (g << 5) | b
            text += f'\tmyimg->argb_array[{x*image.height + y}] = {hex(px)};\n'

    text += (
        '\treturn myimg;\n'
        '}\n'
    )

    print('(100%) generating code...')
    return text


def get_source_rgb565(img: Image.Image, function_name: str, file_name: str) -> str:
    image = img.convert('RGB')

    text = (
        '/* -- F. Graphics Library (FGL) --\n'
        f' * File: {file_name}.cpp\n'
        ' *\n'
        ' * This code file generated by the img_to_fgl.py script\n'
        ' * contains the contents of an image file adapted to\n'
        ' * using with FGL\n'
        ' *\n'
        f' * FGL image format: RGB565\n'
        f' * Generation date (Y-M-D): {today_date}\n'
        ' */\n'
        f'#include \"{file_name}.hpp\"\n'
        '\n'
        f'Image *{function_name}()\n'
        '{\n'
        f'\tImageRGB565 *myimg = new ImageRGB565({image.width}, {image.height});\n'
    )

    for x in range(image.width):
        for y in range(image.height):
            print(f'({int(((x*image.width + y)/(image.width*image.height))*100)}%) generating code...', end='\r')
            pixel = image.getpixel((x,y))
            r = int(round((pixel[0]/255)*0x1F)) & 0x1F
            g = int(round((pixel[1]/255)*0x3F)) & 0x3F
            b = int(round((pixel[2]/255)*0x1F)) & 0x1F
            px = (r << 11) | (g << 5) | b
            text += f'\tmyimg->rgb_array[{x*image.width + y}] = {hex(px)};\n'

    text += (
        '\treturn myimg;\n'
        '}\n'
    )

    print('(100%) generating code...')
    return text

def get_image_kmeans_elbow(image: Image.Image) -> object:
    import numpy as np
    from sklearn.cluster import KMeans
    from kneed import KneeLocator
    import warnings
    warnings.filterwarnings("ignore")

    kmeans_data = [image.getpixel((x, y)) for x in range(image.width) for y in range(image.height)]
    kmeans_data = np.vstack(kmeans_data)
    
    #Find the best number of clusters
    kmeans_instances = [KMeans(n_clusters=2).fit(kmeans_data)] #List of kmeans instances
    sse = [kmeans_instances[0].inertia_] #List of SSE (inertia) values
    elbow = None #Current SSE elbow found
    elbow_repetition = 0 #Number of times which the same elbow is consecutively found

    for n in range(3, 256): 
        print(f'({n+1}/256) searching for the SSE elbow... elbow={elbow}     ', end='\r')
        ckm = KMeans(n_clusters=n).fit(kmeans_data) #current kmeans
        
        kmeans_instances.append(ckm)
        sse.append(ckm.inertia_)

        kl = KneeLocator(range(2, n+1), sse, curve="convex", direction="decreasing") #Find the SSE elbow between 2 clusters and _n_ clusters
        
        if elbow != None and elbow == kl.elbow: #Current elbow is the same as the previous
            elbow_repetition += 1
        else:
            elbow_repetition = 0

        if elbow_repetition == 20: #If the same elbow is found 20 consecutive times, stop searching
            break

        elbow = kl.elbow

    print(f'\nelbow found: {elbow}')
    
    return kmeans_instances[elbow-2] if elbow != None else None

def get_image_kmeans(image: Image.Image, k: int) -> object:
    import numpy as np
    from sklearn.cluster import KMeans
    from kneed import KneeLocator
    import warnings
    warnings.filterwarnings("ignore")

    kmeans_data = [image.getpixel((x, y)) for x in range(image.width) for y in range(image.height)]
    kmeans_data = np.vstack(kmeans_data)/255
    
    #Find the best number of clusters
    return KMeans(n_clusters=k).fit(kmeans_data)

def get_source_k8(img: Image.Image, function_name: str, file_name: str, ncolors: int = None) -> str:
    import numpy as np
    from sklearn.cluster import KMeans
    from sklearn.preprocessing import StandardScaler
    from kneed import KneeLocator
    import warnings
    warnings.filterwarnings("ignore")
    
    image = img.convert('RGBA')

    if ncolors != None:
        if ncolors < 2:
            print('ncolors value must be greater or equal than 2')
            exit()

    text = (
        '/* -- F. Graphics Library (FGL) --\n'
        f' * File: {file_name}.cpp\n'
        ' *\n'
        ' * This code file generated by the img_to_fgl.py script\n'
        ' * contains the contents of an image file adapted to\n'
        ' * using with FGL\n'
        ' *\n'
        f' * FGL image format: K8\n'
        f' * Generation date (Y-M-D): {today_date}\n'
        ' */\n'
        f'#include \"{file_name}.hpp\"\n'
        '\n'
        f'Image *{function_name}()\n'
        '{\n'
        f'\tImageK8 *myimg = new ImageK8({image.width}, {image.height});\n'
    )

    print('Generating color palette with KMeans')
    km = get_image_kmeans_elbow(image) if ncolors == None else get_image_kmeans(image, ncolors)

    if km == None:
        if ncolors == None:
            print('Cannot find the ideal number of colors using Elbow method. Please, run the script again specifying a number of colors to the --ncolors parameter.')
        else:
            print('An unexpected error has occurred.')
        exit()

    color_counter = 0
    for color in km.cluster_centers_:
        r = color[0]/255
        g = color[1]/255
        b = color[2]/255
        a = color[3]/255
        text += f'\tmyimg->color_map[{color_counter}] = new Color({a},{r},{g},{b});\n'
        color_counter += 1

    for x in range(image.width):
        for y in range(image.height):
            print(f'({int(((x*image.width + y)/(image.width*image.height))*100)}%) generating code...', end='\r')
            pixel = image.getpixel((x,y))
            k = km.predict([pixel])[0]
            text += f'\tmyimg->k_array[{x*image.width + y}] = {k};\n'

    text += (
        '\treturn myimg;\n'
        '}\n'
    )

    print('(100%) generating code...')
    return text

def save_to_file(file_name: str, text: str):
    f = open(file_name, 'w')
    f.write(text)
    f.close()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generates a C++ code with the contents af an image file to using with FGL.')
    parser.add_argument('input_image', type=str, help='Input image file path.')
    parser.add_argument('output_name', type=str, help='Name for the generated code (without path or extensions).')
    parser.add_argument('--dir', type=str, help='Root directory for the generated files.')
    parser.add_argument('--format', type=str, choices=['ARGB8888', 'ARGB1555', 'RGB565', 'K8'], help='FGL image format.')
    parser.add_argument('--fname', type=str, help='Name for the generated function (if this argument is not set, output_name is used as function name).')
    parser.add_argument('--resize', type=int, nargs = 2, help='Width and Height (respectively) to the generated image')
    parser.add_argument('--ncolors', type=int, help='Number of colors to be maped (work only with K8 image type).')
    
    args = parser.parse_args()

    #Checking ncolors
    if args.ncolors != None and not args.format == 'K8':
        print('Ignoring ncolors param')

    #Check output directory name
    dir = args.dir if args.dir != None else '.'

    if(not os.path.exists(dir)):
        print(f'No such file or directory: {dir}')
        exit()

    if(not os.path.isdir(dir)):
        print(f'Path is not a dir: {dir}')
        exit()

    #Load image file
    img = open_image_file(args.input_image)

    if args.resize != None:
        width = args.resize[0]
        height = args.resize[1]
        
        if width <= 1 or height <= 1:
            print('Width and height values must be greater than 1')
            exit()

        img = img.resize((width,height), Image.ANTIALIAS)

    #Output name
    if not check_cpp_identifier(args.output_name):
        print('Invalid output name.')
        print('output_name must have only numbers (not as first character), letters and underscores.')
        exit()
    
    #Function name
    function_name = args.fname if args.fname != None else args.output_name

    if not check_cpp_identifier(function_name):
        print('Invalid fname.')
        print('fname must have only numbers (not as first character), letters and underscores.')
        exit()

    #Generate code
    htxt = get_header_text(args.input_image, args.format, function_name, args.output_name)

    if args.format == 'ARGB8888':
        stxt = get_source_argb8888(img, function_name, args.output_name)
    elif args.format == 'ARGB1555':
        stxt = get_source_argb1555(img, function_name, args.output_name)
    elif args.format == 'RGB565':
        stxt = get_source_rgb565(img, function_name, args.output_name)
    elif args.format == 'K8':
        stxt = get_source_k8(img, function_name, args.output_name, args.ncolors)
    else:
        print('Default format chosen (ARGB8888)')
        stxt = get_source_argb8888(img, function_name, args.output_name)

    save_to_file(os.path.join(dir, args.output_name + '.hpp'), htxt)
    save_to_file(os.path.join(dir, args.output_name + '.cpp'), stxt)
