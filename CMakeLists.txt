#本文件由自动化脚本生成,改这个文件是没用的,要更改配置请修改项目根目录下的 project_config.json 文件,然后再次运行脚本,即可更改编译配置
#未经作者允许,不可更改脚本内容,不可传播,脚本源码闭源,只可在实验室内部使用,否则本人线下追究责任,脚本版权归作者本人和实验室所有
cmake_minimum_required(VERSION 3.16)

# 项目配置
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m0plus)
set(TARGET_CHIP MSPM0G350X)
set(TARGET_BOARD BLUEPILL)

# 工具链
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(MSPM0_25E C CXX ASM)

# 编译标志 (软件浮点)
set(CMAKE_C_FLAGS "-mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -fdata-sections -ffunction-sections -Wall -fstack-usage -O0 -g3")
set(CMAKE_CXX_FLAGS "-mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -fdata-sections -ffunction-sections -Wall -fstack-usage -O0 -g3")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -fdata-sections -ffunction-sections -Wall -fstack-usage -O0 -g3")

# 链接标志
set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m0plus -mthumb -mfloat-abi=soft  -T${CMAKE_SOURCE_DIR}/Driver/device_linker.lds -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map,--cref -u _printf_float -u _scanf_float -Wl,--print-memory-usage")

# 宏定义
add_definitions(-D__MSPM0G3507__)

# 头文件目录
include_directories(
    BSP
    Control
    Device
    Driver
    Driver_Framework
    app
    Device/encoder
    Device/gray_nomcu
    Device/oled
    Driver_Framework/i2c
    Driver_Framework/key
    Driver_Framework/led
    Driver_Framework/spi
    Middleware/shell
    Middleware/trans
    BSP/ti/devices
    BSP/ti/driverlib
    BSP/ti/devices/msp
    BSP/ti/driverlib/m0p
    BSP/third_party/CMSIS/Core/Include
    BSP/ti/devices/msp/m0p
    BSP/ti/devices/msp/peripherals
    BSP/ti/driverlib/m0p/sysctl
    BSP/ti/devices/msp/peripherals/m0p
    BSP/ti/devices/msp/peripherals/m0p/sysctl
)

# 源文件分组
set(BSP_SOURCES
    BSP/syscalls.c
)

set(CONTROL_SOURCES
    Control/filter.c
    Control/pid.c
)

set(DRIVER_SOURCES
    Driver/gpio.c
    Driver/nvic.c
    Driver/spi.c
    Driver/ti_msp_dl_config.c
    Driver/uart.c
)

set(DRIVER_FRAMEWORK_SOURCES
    Driver_Framework/dev_model_core.c
)

set(APP_SOURCES
    app/control.c
    app/init.c
    app/irq.c
    app/main.c
)

set(DRIVERLIB_SOURCES
    BSP/ti/driverlib/dl_adc12.c
    BSP/ti/driverlib/dl_aes.c
    BSP/ti/driverlib/dl_aesadv.c
    BSP/ti/driverlib/dl_common.c
    BSP/ti/driverlib/dl_comp.c
    BSP/ti/driverlib/dl_crc.c
    BSP/ti/driverlib/dl_crcp.c
    BSP/ti/driverlib/dl_dac12.c
    BSP/ti/driverlib/dl_dma.c
    BSP/ti/driverlib/dl_flashctl.c
    BSP/ti/driverlib/dl_gpamp.c
    BSP/ti/driverlib/dl_gpio.c
    BSP/ti/driverlib/dl_i2c.c
    BSP/ti/driverlib/dl_i2s.c
    BSP/ti/driverlib/dl_iwdt.c
    BSP/ti/driverlib/dl_keystorectl.c
    BSP/ti/driverlib/dl_lcd.c
    BSP/ti/driverlib/dl_lfss.c
    BSP/ti/driverlib/dl_mathacl.c
    BSP/ti/driverlib/dl_mcan.c
    BSP/ti/driverlib/dl_npu.c
    BSP/ti/driverlib/dl_opa.c
    BSP/ti/driverlib/dl_rtc.c
    BSP/ti/driverlib/dl_rtc_a.c
    BSP/ti/driverlib/dl_rtc_b.c
    BSP/ti/driverlib/dl_rtc_common.c
    BSP/ti/driverlib/dl_scratchpad.c
    BSP/ti/driverlib/dl_spgss.c
    BSP/ti/driverlib/dl_spi.c
    BSP/ti/driverlib/dl_tamperio.c
    BSP/ti/driverlib/dl_timer.c
    BSP/ti/driverlib/dl_timera.c
    BSP/ti/driverlib/dl_timerb.c
    BSP/ti/driverlib/dl_timerg.c
    BSP/ti/driverlib/dl_trng.c
    BSP/ti/driverlib/dl_uart.c
    BSP/ti/driverlib/dl_unicomm.c
    BSP/ti/driverlib/dl_unicommi2cc.c
    BSP/ti/driverlib/dl_unicommi2ct.c
    BSP/ti/driverlib/dl_unicommspi.c
    BSP/ti/driverlib/dl_unicommuart.c
    BSP/ti/driverlib/dl_vref.c
    BSP/ti/driverlib/dl_wwdt.c
)

set(ENCODER_SOURCES
    Device/encoder/encoder.c
)

set(GCC_SOURCES
    BSP/ti/devices/msp/m0p/startup_system_files/gcc/startup_mspm0g350x_gcc.c
)

set(GRAY_NOMCU_SOURCES
    Device/gray_nomcu/gray_nomcu.c
)

set(LED_SOURCES
    Driver_Framework/led/df_led.c
)

set(M0P_SOURCES
    BSP/ti/driverlib/m0p/dl_factoryregion.c
    BSP/ti/driverlib/m0p/dl_interrupt.c
)

set(OLED_SOURCES
    Device/oled/OLED.c
    Device/oled/OLED_Data.c
)

set(SYSCTL_SOURCES
    BSP/ti/driverlib/m0p/sysctl/dl_sysctl_mspm0g1x0x_g3x0x.c
)

# 所有源文件
set(SOURCE_FILES
    ${BSP_SOURCES}
    ${CONTROL_SOURCES}
    ${DRIVER_SOURCES}
    ${DRIVER_FRAMEWORK_SOURCES}
    ${APP_SOURCES}
    ${DRIVERLIB_SOURCES}
    ${ENCODER_SOURCES}
    ${GCC_SOURCES}
    ${GRAY_NOMCU_SOURCES}
    ${LED_SOURCES}
    ${M0P_SOURCES}
    ${OLED_SOURCES}
    ${SYSCTL_SOURCES}
)

# 子目录
add_subdirectory(Driver_Framework/i2c)
add_subdirectory(Driver_Framework/key)
add_subdirectory(Driver_Framework/spi)
add_subdirectory(Middleware/shell)
add_subdirectory(Middleware/trans)

# 创建可执行文件
add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES})

# 链接静态库
target_link_libraries(${PROJECT_NAME}.elf
    i2c
    key
    shell
    spi
    trans
)

# 生成输出文件
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMAND ${SIZE} --format=berkeley $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Building output files"
)
