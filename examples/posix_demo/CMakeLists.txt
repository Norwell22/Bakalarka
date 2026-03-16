add_executable(posix_demo main.c use_cases.c)
target_link_libraries(posix_demo context_lib)

add_executable(tests tests.c)
target_link_libraries(tests context_lib)

