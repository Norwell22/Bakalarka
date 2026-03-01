#include <stdio.h>
#include "context_lib_port.h"
// #include "../../include/context_manager.h"

/*
============ L1 send/receive functions ===========
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
=========== Memory areas of MCU
*/

//saving data into flash won't probably be possible
cl_int_t FLASH[1024];
//saving data into LRAM specifically should be possible using __attribute__
cl_int_t LRAM[1024];
//TODO: this should maybe be somewhere else
cl_int_t CL_PROTECTED_MEM[10];
//saving data into HRAM specifically should be possible using __attribute__
cl_int_t HRAM[1024];
//saving data into register file will be done using direct write
cl_int_t REGISTER_FILE[128];
//saving data into outside memory will be done using special function
cl_int_t OUTSIDE1[256];

cl_int_t OUTSIDE2[256];

// metadata which should be saved into RF
const Cl_memory_area_t ma255 = {255,CL_PROTECTED_MEM,CL_PROTECTED_MEM + 9};

// Register file memory
const Cl_memory_area_t ma1 = {1,REGISTER_FILE,REGISTER_FILE + 127};

// LRAM memory: pretty stable
const Cl_memory_area_t ma10 = {10,LRAM, LRAM + 99};
const Cl_memory_area_t ma11 = {11,LRAM + 100, LRAM + 109};


// HRAM memory: deleted quite often
const Cl_memory_area_t ma100 = {100, HRAM     , HRAM + 5};
const Cl_memory_area_t ma101 = {101, HRAM + 10, HRAM + 15};
const Cl_memory_area_t ma102 = {102, HRAM + 20, HRAM + 25};
const Cl_memory_area_t ma103 = {103, HRAM + 30, HRAM + 35};
const Cl_memory_area_t ma104 = {104, HRAM + 40, HRAM + 45};
const Cl_memory_area_t ma105 = {105, HRAM + 50, HRAM + 55};

// Peripheral memory: usually can be turned on or off
const Cl_peripheral_area_t ma200;
const Cl_peripheral_area_t ma201;
const Cl_peripheral_area_t ma202;
const Cl_peripheral_area_t ma203;
const Cl_peripheral_area_t ma204;

// ==== Layer 3

// this should be filled by all areas by the user
// ideally in order by its ID for quicker search
const cl_int_t memory_areas_table_size = 10;
const Cl_memory_area_t *memory_areas[] = {&ma255,&ma1,&ma10,&ma11,&ma100,&ma101,&ma102,&ma103,
        &ma104,&ma105};

const cl_int_t peripheral_areas_table_size = 5;
const Cl_peripheral_area_t *peripheral_areas[] = {&ma200,&ma201,&ma202,&ma203,&ma204};




const cl_int_t area_mode_table_size = 8;
const struct area_in_mode area_mode_table[] = {
    {LRAM, LRAM + 1023, RUN, ON},
    {LRAM, LRAM + 1023, SLEEP, ON},
    {LRAM, LRAM + 1023, STOP, ON},
    {LRAM, LRAM + 1023, VLLS, OFF},

    {HRAM, HRAM + 1023, RUN, ON},
    {HRAM, HRAM + 1023, SLEEP, ON},
    {HRAM, HRAM + 1023, STOP, OFF},
    {HRAM, HRAM + 1023, VLLS, OFF},

    {REGISTER_FILE, REGISTER_FILE + 127,RUN,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,SLEEP,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,STOP,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,VLLS,ON},

    {OUTSIDE1,OUTSIDE1 + 255, RUN, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, SLEEP, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, STOP, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, VLLS, BOTH_VALID},

    {OUTSIDE2,OUTSIDE2 + 255, RUN, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, SLEEP, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, STOP, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, VLLS, BOTH_VALID},
};


const cl_int_t area_backup_table_size = 6;
const struct area_backup area_backup_table[] = {
    {&ma255,&ma1},{&ma11,&ma1},
    {&ma100,&ma10},{&ma101,&ma10},{&ma102,&ma10},
    {&ma103,&ma11}
};



