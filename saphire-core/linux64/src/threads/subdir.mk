################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/threads/CCpuThread.cpp \
../src/threads/CThreadManager.cpp 

OBJS += \
./src/threads/CCpuThread.o \
./src/threads/CThreadManager.o 

CPP_DEPS += \
./src/threads/CCpuThread.d \
./src/threads/CThreadManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/threads/%.o: ../src/threads/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/mnt/oldos/home/rast/workspace/saphire-core/include" -O0 -g3 -Wall -c -fmessage-length=0 -static-libstdc++  -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


