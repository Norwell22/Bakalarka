#ifndef CL_INCLUDE_PORT
#define CL_INCLUDE_PORT


/*! 
 * \file      context_lib_port.h
 * \brief     Example of port for simulated microcontroler.
 * \details   
 * Dependencies:
 * - "../../include/main/types.h"
 * Before using this library on new microcontroller, port like this needs
 * to be created for that particular MCU. This means defining some functions
 * and variables with MCU-specific values, which in vast majority happens in 
 * this file and also in \c context_lib_port.h file. This file contains function and
 * variable declarations and descriptions needed for port implementation.
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \note Port creation is highly guided process. Follow comments in this file or instructions in
 * TODO and you should avoid most problems.
 * \note Port creation requires knowledge of power modes, memory map and memory retention for your 
 * specific microcontroller. Use Reference manual (chapters on Memory management) when unsure.
 * \todo In current form, this file is too large and complex. It should
 * be more minimalistic.
 */
#include "types.h"

/*!
* \name Layer 1 functions
* @{
* \brief Lowest-level functions for data storage
*/

/*!
* \todo Merge this with custom_send_byte(), no need for two separate functions
*/
uint32_t send_byte(uint8_t b, uint8_t *addr); 

/*!
* \brief User specified function for storing one byte in non-standard way.
*
* On its lowest level, this library works with function for storing or loading
* individual data bytes. This can be done in standard C way by \b writing \b byte
* \b to \b address or in (possibly more) custom device-specific ways.  
* This function gives user a way to specify function for sending data in specific way.
* Most prominent use case for this is expected to be sending data to external storage (E.g. SD card)
* \todo Library should also allow for adding similar functions
* \note Port creator or user can implement this function to execute byte saving in any needed way
*/
uint32_t custom_send_byte(uint8_t b, uint8_t *addr,void *other_data);

/*!
* \todo Merge this with custom_rcv_byte(), no need for two separate functions
*/
uint32_t rcv_byte(uint8_t *b, uint8_t *addr);

/*!
* \brief User specified function for loading data in non-standard way.
*
* On its lowest level, this library works with function for storing or loading
* individual data bytes. This can be done in standard C way by \b writing \b byte
* This function gives user a way to specify function for loading data in specific way.
* Most prominent use case for this is expected to be loading data from external storage (E.g. SD card)
* \b from \b one \b address \b to \b another or in (possibly more) custom device-specific ways.  
* \todo Library should also allow for adding similar functions
* \note Port creator or user can implement this function to execute byte saving in any needed way
*/
uint32_t custom_rcv_byte(uint8_t *b, uint8_t *addr, void *other_data);
/*! @}*/




/*!
* \name Simulated memory arrays
* \brief Example of memory protection for memory area.
*
* These arrays simulate parts of microcontroller memory map that can be found within a common device. 
* They serve as an example for anyone working with this library and are also used in its testbench.
*
* Library itself has no way to protect memory from being erased. This is due to fact that dynamic
* allocation is generally not supported on embedded systems and any static allocation that would happen
* inside dedicated function would obviously lose effect after return from the function. Library user must 
* therefore make sure that parts of the memory used by the library will be left untouched by other parts of
* the program and will stay 'allocated' for the entirety of its runtime. Expected way to do it is by declaring
* array globally and define memory areas using those addresses.
* \note All of these areas should be declared here and defined in \c context_lib_port.c file
* \note Saving data into LRAM or HRAM should be possible using __attribute__
* \todo Replace PROTECTED_MEM, better sooner than later
* \todo Consider saving data into flash
* \todo Find out how to save data directly into register file
* I won't probably have
* @{
*/
extern cl_int_t FLASH[1024];
extern cl_int_t CL_PROTECTED_MEM[10];
extern cl_int_t LRAM[1024];
extern cl_int_t HRAM[1024];
extern cl_int_t REGISTER_FILE[128];
extern cl_int_t REGISTER_FILE2[256];
extern cl_int_t OUTSIDE1[256];
extern cl_int_t OUTSIDE2[256];
extern cl_int_t I2C1_REG0;
extern cl_int_t I2C1_REG1;
extern cl_int_t I2C1_REG2;
extern cl_int_t I2C1_REG3;
extern cl_int_t I2C1_REG4;
extern cl_int_t I2C1_REG5;
extern cl_int_t GPIO_REGS[16];
extern cl_int_t UART0_REGS[8];
extern cl_int_t SPI0_REGS[6];
extern cl_int_t I2C0_REGS[6];
extern cl_int_t TIMER0_REGS[10];
/** @} */


/*!
* \brief Library metadata which should allways be protected
* 
* This is the declaration of reserved memory area that contains metadata for third layer of library.
* If the third layer is to be used, this area must be defined.
* It is advised to define it using addresses of best protected part of memory. For example: if device
* contains 32-byte, allways on memory area called Register file, user may define areas for this file this way:
* - \code const Cl_memory_area_t ma255 = {255,REGISTER_FILE_START_ADDR, REGISTER_FILE_START_ADDR + N}; \endcode
* - \code const Cl_memory_area_t rf = {1,REGISTER_FILE_START_ADDR + N + 1,REGISTER_FILE_START_ADDR + 32}; \endcode
* rf can be used for protection of most important data while ma255 should be left untouched
* \todo Specify its size
* \todo Probably rename ma255
*/
extern const Cl_memory_area_t ma255;

/*!
* \brief RegF2: Best-protected memory area. Serves as an example
*
* After defining arrays used for memory storage, library user must define memory areas
* using these arrays. Examples of this can be seen in any \c context_lib_port.c file
*
* This area simulates Register file 2: Memory area that is protected in every
* power mode that this MCU provides. It is used mainly for testing.
*
* \note Every memory area needs to be declared like this in this file. 
*/
extern const Cl_memory_area_t ma2;

/*!
* \brief RegF: Very well protected memory area. Serves as an example
* 
* This area simulates Register file. Small memory area that is protected in almost
* every power mode. It is used mainly for testing. 
*/
extern const Cl_memory_area_t ma1;

/*!
* \name LRAM Memory areas
* @{
* \brief Reasonably well protected memory areas.
*
* These areas simulate part of RAM memory. Big memory area, protected in all modes
* except Very low leakage stop modes.
*/
extern const Cl_memory_area_t ma10;
extern const Cl_memory_area_t ma11;
extern const Cl_memory_area_t ma12;
extern const Cl_memory_area_t ma13;
/*! @} */


/*!
* \name HRAM Memory areas
* @{
* \brief Moderately protected memory area.
*
* This area simulates part of RAM memory. Big memory area, not protected in Low leakage
* stop modes.
*/
extern const Cl_memory_area_t ma100;
extern const Cl_memory_area_t ma101;
extern const Cl_memory_area_t ma102;
extern const Cl_memory_area_t ma103;
extern const Cl_memory_area_t ma104;
extern const Cl_memory_area_t ma105;
/*! @} */

/*!
* \name Peripheral Memory areas
* @{
* \brief Peripherals: Can be turned on or off independently of power mode 
* \note Definitions of these areas were generated by ChatGPT
*/
extern const Cl_peripheral_area_t ma200;
extern const Cl_peripheral_area_t ma201;
extern const Cl_peripheral_area_t ma202;
extern const Cl_peripheral_area_t ma203;
extern const Cl_peripheral_area_t ma204;
/*! @} */

#endif