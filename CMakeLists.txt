cmake_minimum_required (VERSION 3.16)

set (PROJECT_NAME rx-template)
project (${PROJECT_NAME} C ASM)

set (CMAKE_C_COMPILER rx-elf-gcc)
set (CMAKE_ASM_COMPILER rx-elf-gcc)

# TODO make something more clever about build type later
set (CMAKE_BUILD_TYPE Debug)

add_executable (${PROJECT_NAME} src/main.c
                                src/device/startup.S
                                src/device/vector_table.c
                                src/device/interrupt_handlers.c
                                src/device/hardware_setup.c
                                src/device/cpu.S
               )

target_include_directories (${PROJECT_NAME} PRIVATE src/device src/device)
target_compile_options (${PROJECT_NAME} PRIVATE -mcpu=rx600 -mlittle-endian-data)
target_link_options (${PROJECT_NAME} PRIVATE "-T${CMAKE_SOURCE_DIR}/src/device/RX62N.ld"
                                             -nostartfiles
                                             -mcpu=rx600
                                             -mlittle-endian-data
                                             "-e_PowerON_Reset"
                                             -specs=nosys.specs
                                             -specs=nano.specs
                    )

# Debug on HW

add_custom_target (gdbser
  COMMAND JLinkGDBServerCLExe -select USB -device RX62N -endian little -if JTAG -speed 4000 -ir -noLocalhostOnly
  DEPENDS ${PROJECT_NAME})

add_custom_target (cgdbl
                   COMMAND cgdb -d rx-elf-gdb $<TARGET_FILE:${PROJECT_NAME}> -ex 'b main'
                   -ex 'target remote 127.0.0.1:2331'
                   -ex 'monitor halt'
                   -ex 'monitor reset 2'
                   -ex 'load'
                   DEPENDS ${PROJECT_NAME})

add_custom_target (cgdbr
                   COMMAND cgdb -d rx-elf-gdb $<TARGET_FILE:${PROJECT_NAME}> -ex 'b main'
                   -ex 'target remote 127.0.0.1:2331'
                   -ex 'monitor halt'
                   -ex 'monitor reset 2'
                   DEPENDS ${PROJECT_NAME})
