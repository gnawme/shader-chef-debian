################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../shadertest.cpp 

OBJS += \
./shadertest.o 

CPP_DEPS += \
./shadertest.d 


# Each subdirectory must supply rules for building sources it contributes
shadertest.o: ../shadertest.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -fsyntax-only -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"shadertest.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


