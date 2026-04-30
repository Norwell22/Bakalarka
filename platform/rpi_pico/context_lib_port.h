#ifndef CL_INCLUDE_PORT
#define CL_INCLUDE_PORT


/*! 
 * \file      context_lib_port.h
 * \brief     Empty port example. Serves as template for new port
 * \details   
 * Before using this library on new microcontroller, new port needs
 * to be implemented. Vast majority of this implementation happens inside
 * this file and inside \c context_lib_port.c with every exception being
 * clearly marked inside this file. When creating port, please go through
 * functions in this file one by one. 
 * \author    Michal Zidzik
 * \date      21.03.2026
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
* \brief User specified function for storing one byte in non-standard way.
*
* On its lowest level, this library works with function for storing or loading
* individual data bytes. This can be done in standard C way by \b writing \b byte
* \b to \b address or in (possibly more) custom device-specific ways.  
* This function gives user a way to specify function for sending data in specific way.
* Most prominent use case for this is expected to be sending data to external storage (E.g. SD card)
* 
* 
* \todo Library should also allow for adding similar functions
* \todo After reworking L1, add instructions for creating more functions.
* \note Port creator or user can implement this function to execute byte saving in any needed way
* \note Port creator or user can add more functions with same type here provided that he follows
* instructions in this comment.(TBD)
*/
uint32_t send_byte(uint8_t b, uint8_t *addr,void *other_d); 


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
* \note Port creator or user can add more functions with same type here provided that he follows
* instructions in this comment.(TBD)
*/
uint32_t rcv_byte(uint8_t *b, uint8_t *addr,void *other_d);
/*! @}*/



/*!
* \name Simulated memory arrays
* \brief Example of memory protection for memory area.
*
* Library itself has no way to protect memory from being erased. This is due to fact that dynamic
* allocation is generally not supported on embedded systems and any static allocation that would happen
* inside dedicated function would obviously lose effect after return from the function. Library user must 
* therefore make sure that parts of the memory used by the library will be left untouched by other parts of
* the program and will stay 'allocated' for the entirety of its runtime. Expected way to do it is by declaring
* arrays globally and define memory areas using those addresses.
* 
* Here you can add global declarations of every array that you will use. Don't forget to also define it in 
* \c .c equivalent of this file. 
*
* \note All of these areas should be declared here and defined in \c context_lib_port.c file
* \note Saving data into LRAM or HRAM should be possible using __attribute__
* @{
*/
extern cl_int_t MEMORY_ARR1[100];
extern cl_int_t MEMORY_ARR2[100];
/** @} */

/*!
* \name Simulated registers addresses
* \brief Example of address definition for peripheral areas.
*
* Principle here is the same as for memory areas but instead of arrays, you define specific addresses. Expected
* usage is that one address will represent register of a device.
* 
* Here you can add global declarations of every array that you will use. Don't forget to also define it in 
* \c .c equivalent of this file. 
*
* \note All of these areas should be declared here and defined in \c context_lib_port.c file
* \note Saving data into LRAM or HRAM should be possible using __attribute__
* @{
*/
extern const cl_addr_t reg_addr1;
extern const cl_addr_t reg_addr2;
extern const cl_addr_t reg_addr3;
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
* rf can be used for protection of most important data while metadata will be left untouched
* 
* This area therefore needs to be defined in \c .c equivalent of this file
* 
* \note Its size should be ( 256 / ARCHITECTURE_BUS_SIZE ) + 1
*/
extern const Cl_memory_area_t cl_metadata_ma;

/*!
* \name Memory areas
* @{
* \brief Examples of memory areas
* 
* In similar manner to metadata memory area, you can define as many areas as you want. These areas are backbone of
* this library, so pay good attention to them when creating it. Also don't forget to actually define them in \c .c
* equivalent of this file.
*/
extern const Cl_memory_area_t memory_area_example1;
extern const Cl_memory_area_t memory_area_example2;
/*! @}*/

/*!
* \name Peripheral areas
* @{
* \brief Examples of peripheral areas
* 
* In similar manner to metadata memory area, you can define as many areas as you want. These areas are backbone of
* this library, so pay good attention to them when creating it. Also don't forget to actually define them in \c .c
* equivalent of this file.
*/
extern const Cl_peripheral_area_t peripheral_area_example1;
/*! @} */

bool eeprom_write_byte(uint8_t data, uint8_t *addr);
bool eeprom_read_byte(uint8_t *data_out, uint8_t *mem_addr);


//void cl_eeprom_pico_save_e(cl_int_t e, cl_addr_t addr, void *not_used);
//void cl_eeprom_pico_load_e(cl_addr_t e, cl_addr_t addr, void *not_used);

#endif