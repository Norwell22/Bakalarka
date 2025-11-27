#ifndef CONTEXT_LIB
#define CONTEXT_LIB

void lib_init();

void blink_led();

//this function should be implemented by user
void platform_toggle_led();

#endif