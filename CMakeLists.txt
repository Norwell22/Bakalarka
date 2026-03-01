cmake_minimum_required(VERSION 3.10)
project(MyLib C)

add_library(context_lib
    src/main/context_manager.c
    src/main/l1_private.c
    src/main/l1_public.c
    src/main/l2_private.c
    src/main/l2_public.c
    src/main/l3.c
    src/main/helper_functions.c
    platform/posix/context_lib_port.c
)

target_include_directories(context_lib PUBLIC include platform/posix)
add_subdirectory(examples/posix_demo)
