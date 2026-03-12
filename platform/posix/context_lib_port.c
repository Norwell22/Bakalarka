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


const cl_int_t memory_areas_table_size = 12;
const Cl_memory_area_t *memory_areas[] = {&ma255,&ma1,&ma2,&ma10,&ma11,&ma12,&ma100,&ma101,&ma102,&ma103,
        &ma104,&ma105};

const cl_int_t peripheral_areas_table_size = 5;
const Cl_peripheral_area_t *peripheral_areas[] = {&ma200,&ma201,&ma202,&ma203,&ma204};

const cl_int_t area_mode_table_size = 8;
const struct area_in_mode area_mode_table[] = {
    {LRAM, LRAM + 1023, RUN, ON},
    {LRAM, LRAM + 1023, SLEEP, ON},
    {LRAM, LRAM + 1023, STOP, ON},
    {LRAM, LRAM + 1023, VLLS, OFF},
    {LRAM, LRAM + 1023, VLLS0, OFF},

    {HRAM, HRAM + 1023, RUN, ON},
    {HRAM, HRAM + 1023, SLEEP, ON},
    {HRAM, HRAM + 1023, STOP, OFF},
    {HRAM, HRAM + 1023, VLLS, OFF},
    {HRAM, HRAM + 1023, VLLS0, OFF},

    {REGISTER_FILE, REGISTER_FILE + 127,RUN,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,SLEEP,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,STOP,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,VLLS,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,VLLS0,OFF},

    {REGISTER_FILE2, REGISTER_FILE2 + 255,RUN,ON},
    {REGISTER_FILE2, REGISTER_FILE2 + 255,SLEEP,ON},
    {REGISTER_FILE2, REGISTER_FILE2 + 255,STOP,ON},
    {REGISTER_FILE2, REGISTER_FILE2 + 255,VLLS,ON},
    {REGISTER_FILE2, REGISTER_FILE2 + 255,VLLS0,ON},

    {OUTSIDE1,OUTSIDE1 + 255, RUN, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, SLEEP, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, STOP, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, VLLS, BOTH_VALID},

    {OUTSIDE2,OUTSIDE2 + 255, RUN, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, SLEEP, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, STOP, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, VLLS, BOTH_VALID},

    {UART0_REGS, UART0_REGS + 7, RUN, BOTH_VALID},
    {UART0_REGS, UART0_REGS + 7, SLEEP, BOTH_VALID},
    {UART0_REGS, UART0_REGS + 7, STOP, OFF},
    {UART0_REGS, UART0_REGS + 7, VLLS, OFF},

    {SPI0_REGS, SPI0_REGS + 5, RUN, BOTH_VALID},
    {SPI0_REGS, SPI0_REGS + 5, SLEEP, BOTH_VALID},
    {SPI0_REGS, SPI0_REGS + 5, STOP, OFF},
    {SPI0_REGS, SPI0_REGS + 5, VLLS, OFF},

    {I2C0_REGS, I2C0_REGS + 5, RUN, BOTH_VALID},
    {I2C0_REGS, I2C0_REGS + 5, SLEEP, BOTH_VALID},
    {I2C0_REGS, I2C0_REGS + 5, STOP, OFF},
    {I2C0_REGS, I2C0_REGS + 5, VLLS, OFF},

    {TIMER0_REGS, TIMER0_REGS + 9, RUN, BOTH_VALID},
    {TIMER0_REGS, TIMER0_REGS + 9, SLEEP, BOTH_VALID},
    {TIMER0_REGS, TIMER0_REGS + 9, STOP, OFF},
    {TIMER0_REGS, TIMER0_REGS + 9, VLLS, OFF},

    {GPIO_REGS, GPIO_REGS + 15, RUN, BOTH_VALID},
    {GPIO_REGS, GPIO_REGS + 15, SLEEP, BOTH_VALID},
    {GPIO_REGS, GPIO_REGS + 15, STOP, OFF},
    {GPIO_REGS, GPIO_REGS + 15, VLLS, OFF}
};


const cl_int_t area_backup_table_size = 10;
const struct area_backup area_backup_table[] = {
    {&ma255,&ma1},{&ma10,&ma1},{&ma11,&ma1},
    {&ma100,&ma10},{&ma101,&ma10},{&ma102,&ma10},
    {&ma103,&ma10},{&ma104,&ma10},{&ma105,&ma10},
    {&ma1,&ma2}
};

const cl_int_t peripheral_backup_table_size = 5;
const struct peripheral_backup peripheral_backup_table[] = {
    {&ma200,&ma10},{&ma201,&ma10},{&ma202,&ma10},{&ma203,&ma11},
    {&ma204,&ma11}
};



