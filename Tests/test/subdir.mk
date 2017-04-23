################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/Board_Tests.cpp \
../test/Move_Tests.cpp \
../test/main.cpp 

OBJS += \
./test/Board_Tests.o \
./test/Move_Tests.o \
./test/main.o 

CPP_DEPS += \
./test/Board_Tests.d \
./test/Move_Tests.d \
./test/main.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/sparris/Documents/workspace/Sliding_Blocks_Puzzle/external" -I"/Users/sparris/Documents/workspace/Sliding_Blocks_Puzzle/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


