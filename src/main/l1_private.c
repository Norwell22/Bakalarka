#include "../../include/main/context_manager.h"
#include "../../include/main/l1.h"
#include "../../platform/posix/context_lib_port.h"
#include <stdio.h> //this would be better if wasn't here
#include <stdbool.h> //this would be better if it wasn't here


__attribute__((weak)) cl_int_t save_byte(uint8_t b, uint8_t *addr)
{
   *addr = b; 
   return 0;
}


__attribute__((weak)) cl_int_t load_byte(uint8_t *b, uint8_t *addr)
{
   *b = *addr;
   return 0;
}