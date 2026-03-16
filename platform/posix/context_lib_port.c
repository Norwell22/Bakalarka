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
 * \todo Do include in some better way
 * \author    Michal Zidzik
 * \date      02.03.2026
 */

/*
* L1 send/receive functions
*/
uint32_t send_byte(uint8_t b, uint8_t *addr)
{
    puts("ERROR: context_lib_port.c/send_byte was not implemented and therefore does nothing. Returning 1");
    return 1;
}

uint32_t custom_send_byte(uint8_t b, uint8_t *addr,void *other_data)
{
    puts("ERROR: context_lib_port.c/custom_send_byte was not implemented and therefore does nothing. Returning 1");
    return 1;
}

uint32_t rcv_byte(uint8_t *b, uint8_t *addr)
{
    puts("ERROR: context_lib_port.c/rcv_byte was not implemented and therefore does nothing. Returning 1");
    return 1;
}

uint32_t custom_rcv_byte(uint8_t *b, uint8_t *addr, void *other_data)
{
    puts("ERROR: context_lib_port.c/custom_rcv_byte was not implemented and therefore does nothing. Returning 1");
    return 1;
}

/*
* Layer 2 MCU memory simulation
*/
cl_int_t FLASH[1024];
cl_int_t LRAM[1024];
cl_int_t CL_PROTECTED_MEM[10];
cl_int_t HRAM[1024];
cl_int_t REGISTER_FILE2[256];
cl_int_t REGISTER_FILE[128];
cl_int_t OUTSIDE1[256];
cl_int_t OUTSIDE2[256];
cl_int_t UART0_REGS[8];
cl_int_t SPI0_REGS[6];
cl_int_t I2C0_REGS[6];
cl_int_t TIMER0_REGS[10];
cl_int_t GPIO_REGS[16];

/*
* Layer 2 memory areas
*/
const Cl_memory_area_t ma255 = {255,CL_PROTECTED_MEM,CL_PROTECTED_MEM + 9};
const Cl_memory_area_t ma1 = {1,REGISTER_FILE,REGISTER_FILE + 127};
const Cl_memory_area_t ma2 = {2,REGISTER_FILE2,REGISTER_FILE2 + 255};
const Cl_memory_area_t ma10 = {10,LRAM, LRAM + 99};
const Cl_memory_area_t ma11 = {11,LRAM + 100, LRAM + 109};
const Cl_memory_area_t ma12 = {12,LRAM + 120, LRAM + 124};
const Cl_memory_area_t ma13 = {13,LRAM, LRAM + 10};
const Cl_memory_area_t ma100 = {100, HRAM     , HRAM + 5};
const Cl_memory_area_t ma101 = {101, HRAM + 10, HRAM + 15};
const Cl_memory_area_t ma102 = {102, HRAM + 20, HRAM + 25};
const Cl_memory_area_t ma103 = {103, HRAM + 30, HRAM + 36};
const Cl_memory_area_t ma104 = {104, HRAM + 40, HRAM + 47};
const Cl_memory_area_t ma105 = {105, HRAM + 50, HRAM + 54};

const Cl_peripheral_area_t ma200 = {200, 8,
    {
        (cl_addr_t)&UART0_REGS[0],(cl_addr_t)&UART0_REGS[1],
        (cl_addr_t)&UART0_REGS[2],(cl_addr_t)&UART0_REGS[3],
        (cl_addr_t)&UART0_REGS[4],(cl_addr_t)&UART0_REGS[5],
        (cl_addr_t)&UART0_REGS[6],(cl_addr_t)&UART0_REGS[7]
    }
};

const Cl_peripheral_area_t ma201 = {
    201,6,
    {
        (cl_addr_t)&SPI0_REGS[0],(cl_addr_t)&SPI0_REGS[1],
        (cl_addr_t)&SPI0_REGS[2],(cl_addr_t)&SPI0_REGS[3],
        (cl_addr_t)&SPI0_REGS[4],(cl_addr_t)&SPI0_REGS[5]
    }
};

const Cl_peripheral_area_t ma202 = {202,6,
    {
        (cl_addr_t)&I2C0_REGS[0],(cl_addr_t)&I2C0_REGS[1],
        (cl_addr_t)&I2C0_REGS[2],(cl_addr_t)&I2C0_REGS[3],
        (cl_addr_t)&I2C0_REGS[4],(cl_addr_t)&I2C0_REGS[5]
    }
};

const Cl_peripheral_area_t ma203 = {203, 10,
    {
        (cl_addr_t)&TIMER0_REGS[0],(cl_addr_t)&TIMER0_REGS[1],
        (cl_addr_t)&TIMER0_REGS[2],(cl_addr_t)&TIMER0_REGS[3],
        (cl_addr_t)&TIMER0_REGS[4],(cl_addr_t)&TIMER0_REGS[5],
        (cl_addr_t)&TIMER0_REGS[6],(cl_addr_t)&TIMER0_REGS[7],
        (cl_addr_t)&TIMER0_REGS[8],(cl_addr_t)&TIMER0_REGS[9]
    }
};

const Cl_peripheral_area_t ma204 = {204,16,
    {
        (cl_addr_t)&GPIO_REGS[0],(cl_addr_t)&GPIO_REGS[1],
        (cl_addr_t)&GPIO_REGS[2],(cl_addr_t)&GPIO_REGS[3],
        (cl_addr_t)&GPIO_REGS[4],(cl_addr_t)&GPIO_REGS[5],
        (cl_addr_t)&GPIO_REGS[6],(cl_addr_t)&GPIO_REGS[7],
        (cl_addr_t)&GPIO_REGS[8],(cl_addr_t)&GPIO_REGS[9],
        (cl_addr_t)&GPIO_REGS[10],(cl_addr_t)&GPIO_REGS[11],
        (cl_addr_t)&GPIO_REGS[12],(cl_addr_t)&GPIO_REGS[13],
        (cl_addr_t)&GPIO_REGS[14],(cl_addr_t)&GPIO_REGS[15]
    }
};


/*
* Layer 3 metadata
*/

/*!
 * \brief Implement this enumeration in \c types.h
 *
 * \code
 * enum Cl_power_mode_t { RUN, SLEEP, STOP, LLS, VLLS0, VLLS1, VLLS2, VLLS3 };
 * \endcode
 */


const cl_int_t area_backup_table_size = 19;
struct area_backup area_backup_table[] = {

    {&ma100, &ma10, STOP,false},{&ma101, &ma10, STOP,false},{&ma102, &ma10, STOP,false},
    {&ma103, &ma10, STOP,false},{&ma104, &ma10, STOP,false},{&ma105, &ma10,  STOP,false},

    {&ma100, &ma1, VLLS,false},{&ma101, &ma1, VLLS,false},{&ma102, &ma1, VLLS,false},
    {&ma103, &ma1, VLLS,false},{&ma104, &ma1, VLLS,false},{&ma105, &ma1, VLLS,false},

    {&ma10, &ma1, VLLS,false},{&ma11, &ma1, VLLS,false},{&ma12, &ma1, VLLS,false},

    {&ma10, &ma2, VLLS0,false},{&ma11, &ma2, VLLS0,false},{&ma12, &ma2, VLLS0,false},

    {&ma1, &ma2, VLLS0,false}
};

const cl_int_t peripheral_backup_table_size = 15;
const struct peripheral_backup peripheral_backup_table[] = {
    {&ma200, &ma10, RUN,true},{&ma201, &ma10, RUN,true},{&ma202, &ma10, RUN,true},
    {&ma203, &ma10, RUN,true},{&ma204, &ma10, RUN,true},

    {&ma200, &ma10, STOP,true},{&ma201, &ma10, STOP,true},{&ma202, &ma10, STOP,true},
    {&ma203, &ma10, STOP,true},{&ma204, &ma10, STOP,true},

    {&ma200, &ma1, VLLS,false},{&ma201, &ma1, VLLS,false},{&ma202, &ma1, VLLS,false},
    {&ma203, &ma1, VLLS,false},{&ma204, &ma1, VLLS,false}
};