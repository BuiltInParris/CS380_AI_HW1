################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Board/Board.cpp \
../src/Board/Move.cpp 

OBJS += \
./src/Board/Board.o \
./src/Board/Move.o 

CPP_DEPS += \
./src/Board/Board.d \
./src/Board/Move.d 


# Each subdirectory must supply rules for building sources it contributes
src/Board/%.o: ../src/Board/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


