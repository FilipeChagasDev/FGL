################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../fgl/base/array_search.cpp \
../fgl/base/ccw_sort.cpp \
../fgl/base/list.cpp 

OBJS += \
./fgl/base/array_search.o \
./fgl/base/ccw_sort.o \
./fgl/base/list.o 

CPP_DEPS += \
./fgl/base/array_search.d \
./fgl/base/ccw_sort.d \
./fgl/base/list.d 


# Each subdirectory must supply rules for building sources it contributes
fgl/base/%.o: ../fgl/base/%.cpp fgl/base/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/filipe/github/FGL/tests/STM32H743VI/fgl" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

