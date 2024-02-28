cmake_minimum_required(VERSION 3.27)
project(Lab1_1 C)

set(CMAKE_C_STANDARD 11)

include_directories(cmsis)
include_directories(cmsis_boot)
include_directories(cmsis_lib/include)

add_executable(Lab1_1
        cmsis/core_cm4.h
        cmsis/core_cm4_simd.h
        cmsis/core_cmFunc.h
        cmsis/core_cmInstr.h
        cmsis_boot/startup/startup_stm32f4xx.c
        cmsis_boot/stm32f4xx.h
        cmsis_boot/stm32f4xx_conf.h
        cmsis_boot/system_stm32f4xx.c
        cmsis_boot/system_stm32f4xx.h
        cmsis_lib/include/stm32f4xx_gpio.h
        cmsis_lib/include/stm32f4xx_rcc.h
        cmsis_lib/source/stm32f4xx_gpio.c
        cmsis_lib/source/stm32f4xx_rcc.c
        syscalls/syscalls.c
        main.c)
