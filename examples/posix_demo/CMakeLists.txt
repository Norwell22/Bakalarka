add_executable(posix_demo main.c tests_helper.c)
add_executable(use_cases use_cases.c tests_helper.c)
add_executable(tests tests.c
                     tests_helper.c
                     l2_tests.c
                     l3_tests.c )

target_link_libraries(posix_demo context_lib)
target_link_libraries(use_cases context_lib)
target_link_libraries(tests context_lib)

