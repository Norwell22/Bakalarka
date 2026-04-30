#include "context_lib_port.h"

/*! 
 * \file      context_lib_port.c
 * \brief     Structures containing device-specific metadata and functions
 * \details   
 * Implementation of everything declared in \c context_lib_port.h. This file
 * is very important as an example and documentation for the person writing 
 * port of this library to new platform.
 * Dependencies:
 * - "context_lib_port.h"
 * 
 * \author    Michal Zidzik
 * \date      02.03.2026
 */


/*!
 * \note There is enumeration type in \c include\types.h containing low level ways for read/write functions.
 * For every set of functions added inside \c src\cl_layer1.c , add one value into that enum
 *
 * \code
 * enum Bare_save_type{ CL_CPU,CL_DEVICE };
 * \endcode
 */

// implement this function in any way that's helpful to you. Use other_d pointer freely
uint32_t send_byte(uint8_t b, uint8_t *addr,void *other_d)
{
    puts("ERROR: context_lib_port.c/send_byte was not implemented and therefore does nothing. Returning 1");
    return 1;
}


uint32_t rcv_byte(uint8_t *b, uint8_t *addr,void *other_d)
{
    puts("ERROR: context_lib_port.c/rcv_byte was not implemented and therefore does nothing. Returning 1");
    return 1;
}

// replace with memory areas that you actually want to use
cl_int_t MEMORY_ARR1[100];
cl_int_t MEMORY_ARR2[100];
const cl_addr_t reg_addr1 = (cl_addr_t)0xaaa00;
const cl_addr_t reg_addr2 = (cl_addr_t)0xaaa04;
const cl_addr_t reg_addr3 = (cl_addr_t)0xaaa08;

// size is 8 for 32-bit architecture, 5 for 64-bit architecture
const Cl_memory_area_t cl_metadata_ma = {255,MEMORY_ARR1,MEMORY_ARR1 + 7,CL_CPU};
const Cl_memory_area_t memory_area_example1 = {1,MEMORY_ARR1 + 10,MEMORY_ARR1 + 30,CL_CPU};
const Cl_memory_area_t memory_area_example2 = {2,MEMORY_ARR2,MEMORY_ARR2 + 50,CL_CPU};
const Cl_peripheral_area_t peripheral_area_example1 = {200, 3,CL_CPU,
    {
        reg_addr1,
        reg_addr2,
        reg_addr3,
    }
};


/*
* Layer 3 metadata
*/

#ifdef CL_ALLOW_L3

/*!
 * \note There is enumeration type in \c include\types.h containing following power modes. If you want to add more,
 * do so in that file. 
 *
 * \code
 * enum Cl_power_mode_t { CL_RUN, CL_SLEEP, CL_STOP, CL_LLS, CL_VLLS0, CL_VLLS1, CL_VLLS2, CL_VLLS3 };
 * \endcode
 */

// memory area example 1 will be saved into memory area example 2
const cl_int_t cl_area_backup_table_size = 1;
struct cl_area_backup cl_area_backup_table[] = {
    {&memory_area_example1, &memory_area_example2,CL_RUN,true}
};

// peripheral area example 1 will be saved into memory area example 2
const cl_int_t cl_peripheral_backup_table_size = 1;
const struct cl_peripheral_backup cl_peripheral_backup_table[] = {
    {&peripheral_area_example1,&memory_area_example2,CL_RUN,true}
};
#endif