# Including FGL to my project (general)

FGL is portable and requires no installation, you just need to copy the necessary files to your project directory and make the necessary settings in your IDE or build system.

## Step by step

### 1 - Check if you can merge C++ code into your project

Before anything else, you should check this out. First, there needs to be a C++ compiler compatible with your platform. If the platform's processor architecture is ARM, Xtensa or RISC-V, you can certainly use a G++ distribution.

It is very likely that your platform's default SDK is for C language. In this case, you will have to make some changes to the SDK (at least change the compiler and add the ``extern "c"`` specification to the SDK library files). In some cases, you can use some software to make this adaptation from C to C++.

### 2 - Clone github's FGL repository and copy the necessary files for your project

First, clone the FGL repository using the following command:

```sh
git clone https://github.com/FilipeChagasDev/FGL
```

Obviously, you need to have git installed to do this.

Second, you must copy the necessary files from the FGL repository to your project. The main FGL code files are located in the **lib** folder. All code contained in the lib folder is portable, it only depends on some standard C language libraries (**math**, **stdint** and **assert**). It is also necessary that the dynamic allocation operators **new**, **new[]**, **delete** and **delete[]** are defined. If you think it's necessary, you can delete the generic display drivers you won't be using from the **lib/displays** folder (don't delete the **display.hpp** and **display.cpp** files, they are the basis of all display drivers).

You will also need hardware-specific or platform-specific drivers. Make sure the code you need exists in the **platforms** folder. If found, copy it to your project, otherwise inherit the Display class or one of the available generic drivers and override the virtual methods to create your own platform-specific driver.

### 3 - Configure your IDE or your build system

You must configure your development environment to integrate FGL into your project. First, you must add the **lib** folder to the project's include paths. You can do this by adding a flag to the compiler's build command or by changing project settings in your IDE. If you don't know what include paths are or don't know how to create them, do some research. Also, you need to include all FGL files with **"*.cpp"** extension to your project's sources so that the compiler will generate object codes for FGL and merge them with your project's in the linking.

## Summing up

1. Prepare your project's development environment to include C++ code.
2. Clone github's FGL repository.
3. Copy the **lib** folder to your project.
4. Delete generic display drivers you won't use from **lib/displays**.
5. Add **lib** to your project's include paths.
6. Check if there is platform-specific drivers in the **platforms** folder and copy them. Otherwise, create them yourself.
7. Add all **FGL** files with **"*.cpp"** extension to your project's sources.