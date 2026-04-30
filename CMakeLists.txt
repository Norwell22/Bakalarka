cmake_minimum_required(VERSION 3.10)
project(MyLib C)

set(TARGET_PLATFORM "posix" CACHE STRING "Target platform (posix, stm32, ...)")

if(TARGET_PLATFORM STREQUAL "posix")
    set(PLATFORM_SRC platform/posix/context_lib_port.c)
    set(PLATFORM_INCLUDE platform/posix)
    set(DEMO_DIR examples/posix_demo)

elseif(TARGET_PLATFORM STREQUAL "stm32")
    set(PLATFORM_SRC platform/stm32/context_lib_port.c)
    set(PLATFORM_INCLUDE platform/stm32)
    set(DEMO_DIR examples/stm32_demo)

elseif(TARGET_PLATFORM STREQUAL "frdm_kl27z")
    set(PLATFORM_SRC platform/frdm_kl27z/context_lib_port.c)
    set(PLATFORM_INCLUDE platform/frdm_kl27z)
    set(DEMO_DIR examples/frdm_kl27z_demo)

elseif(TARGET_PLATFORM STREQUAL "template")
    set(PLATFORM_SRC platform/template/context_lib_port.c)
    set(PLATFORM_INCLUDE platform/template)
    set(DEMO_DIR examples/template_demo)

elseif(TARGET_PLATFORM STREQUAL "rpi_pico")
    set(PLATFORM_SRC platform/rpi_pico/context_lib_port.c)
    set(PLATFORM_INCLUDE platform/rpi_pico)
    set(DEMO_DIR examples/rpi_demo)
else()
    message(FATAL_ERROR "Unknown platform: ${TARGET_PLATFORM}")
endif()


add_library(context_lib
    src/context_manager.c
    src/cl_layer1.c
    src/cl_layer2.c
    src/cl_layer3.c
    ${PLATFORM_SRC}
)


if(TARGET_PLATFORM STREQUAL "posix")
    target_compile_definitions(context_lib PRIVATE CL_PLATFORM_POSIX)
elseif(TARGET_PLATFORM STREQUAL "stm32")
    target_compile_definitions(context_lib PRIVATE CL_PLATFORM_STM)
elseif(TARGET_PLATFORM STREQUAL "frdm_kl27z")
    target_compile_definitions(context_lib PRIVATE CL_PLATFORM_FRDM)
elseif(TARGET_PLATFORM STREQUAL "template")
    target_compile_definitions(context_lib PRIVATE CL_PLATFORM_TEMPLATE)
elseif(TARGET_PLATFORM STREQUAL "rpi_pico")
    target_compile_definitions(context_lib PRIVATE CL_PLATFORM_PICO)
endif()


target_include_directories(context_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PLATFORM_INCLUDE}
)
add_subdirectory(ulog)
target_link_libraries(context_lib PRIVATE ulog)
add_subdirectory(${DEMO_DIR})
