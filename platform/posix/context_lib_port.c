#include <stdio.h>
#include "context_lib_port.h"

//here there are functions that take care of platform specific operations
void context_lib_port_setup()
{
    puts("PLATFORM SETUP");
}

void platform_toggle_led()
{
    puts("PLATFORM SPECIFIC ACTION");
}

void context_lib_port_teardown()
{
    puts("PLATFORM TEARDOWN");
}