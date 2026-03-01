
#include "context_lib_port.h"
#include <stdio.h>


void context_lib_port_setup()
{
    printf("KINETIS PLATFORM SETUP\n");
}

void platform_toggle_led()
{
    printf("KINETIS PLATFORM ACTION (toggle LED placeholder)\n");
}

void context_lib_port_teardown()
{
    printf("KINETIS PLATFORM TEARDOWN\n");
}
