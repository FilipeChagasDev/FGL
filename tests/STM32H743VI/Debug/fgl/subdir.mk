################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../fgl/buffered_pencil.cpp \
../fgl/color.cpp \
../fgl/framebuffer.cpp \
../fgl/image.cpp \
../fgl/pencil.cpp 

OBJS += \
./fgl/buffered_pencil.o \
./fgl/color.o \
./fgl/framebuffer.o \
./fgl/image.o \
./fgl/pencil.o 

CPP_DEPS += \
./fgl/buffered_pencil.d \
./fgl/color.d \
./fgl/framebuffer.d \
./fgl/image.d \
./fgl/pencil.d 


# Each subdirectory must supply rules for building sources it contributes
fgl/%.o: ../fgl/%.cpp fgl/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/filipe/github/FGL/tests/STM32H743VI/fgl" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

