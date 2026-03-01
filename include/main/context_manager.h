#ifndef CONTEXT_LIB
#define CONTEXT_LIB

#include <stdio.h>
#include "l1.h"
#include "l2.h"
#include "l3.h"
//here, you should probably include context_lib_port.h
// #include "../../platform/posix/context_lib_port.h"

/*
#ifndef BACKUP_MEM_PTR
#define BACKUP_MEM_PTR 0x00
#endif

#ifndef BACKUP_MEM_SIZE
#define BACKUP_MEM_SIZE 0
#endif
*/


cl_int_t save_byte(uint8_t b, uint8_t *addr);

cl_int_t load_byte(uint8_t *b, uint8_t *addr);


#endif