cmake_minimum_required(VERSION 3.10)
project(MyLib C)

add_library(context_lib
    src/context_manager.c
    src/cl_layer1.c
    src/cl_layer2.c
    src/cl_layer3.c
    platform/posix/context_lib_port.c
)
target_include_directories(context_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_subdirectory(ulog)
target_link_libraries(context_lib PRIVATE ulog)
target_include_directories(context_lib PUBLIC include platform/posix)
add_subdirectory(examples/posix_demo)
