#ifndef INCLUDE_CL_PORT
#define INCLUDE_CL_PORT
#include "../../include/main/types.h"


// uint32_t save_byte_to_arr(uint32_t *b, uint32_t *arr); this probably won't be necessary
uint32_t send_byte(uint8_t b, uint8_t *addr); 

// custom send means that it is up to user to implement it
uint32_t custom_send_byte(uint8_t b, uint8_t *addr,void *other_data);

uint32_t rcv_byte(uint8_t *b, uint8_t *addr);
uint32_t custom_rcv_byte(uint8_t *b, uint8_t *addr, void *other_data);


/*
=========== Memory areas of MCU
*/
// === These represent real memories on the MCU which will not be defined like this
//          in the real scenario: only smaller parts of those would be defined

//saving data into flash won't probably be possible
extern cl_int_t FLASH[1024];

extern cl_int_t CL_PROTECTED_MEM[10];
//saving data into LRAM specifically should be possible using __attribute__
extern cl_int_t LRAM[1024];
//saving data into HRAM specifically should be possible using __attribute__
extern cl_int_t HRAM[1024];
//saving data into register file will be done using direct write
extern cl_int_t REGISTER_FILE[128];
//saving data into outside memory will be done using special function
extern cl_int_t OUTSIDE1[256];
extern cl_int_t OUTSIDE2[256];


// add peripherals here

// In real scenario, these definitions would be replaced by:
// extern cl_int_t MA


// metadata which should be saved into RF
extern const Cl_memory_area_t ma255;

// Register file memory
extern const Cl_memory_area_t ma1;

// LRAM memory: pretty stable
extern const Cl_memory_area_t ma10;
extern const Cl_memory_area_t ma11;


// HRAM memory: deleted quite often
extern const Cl_memory_area_t ma100;
extern const Cl_memory_area_t ma101;
extern const Cl_memory_area_t ma102;
extern const Cl_memory_area_t ma103;
extern const Cl_memory_area_t ma104;
extern const Cl_memory_area_t ma105;

// Peripheral memory: usually can be turned on or off
extern const Cl_peripheral_area_t ma200;
extern const Cl_peripheral_area_t ma201;
extern const Cl_peripheral_area_t ma202;
extern const Cl_peripheral_area_t ma203;
extern const Cl_peripheral_area_t ma204;




// L3 port




#endif