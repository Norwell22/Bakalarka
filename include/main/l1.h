#ifndef CL_INCLUDE_LAYER_1
#define CL_INCLUDE_LAYER_1

/*! 
 * \file      l1.h
 * \brief     Low-level functions for storing and loading data elements
 * \details   
 * On its lowest level, this library simply moves bytes of data from one place to another.
 * In context of embedded systems, this can be done in various ways: simple read/write to address, 
 * write to some external memory, sending/receiving data over line etc. Purpose of functions in this file
 * is to provide ways for implementing those, possibly very variable functions and create some simple abstract
 * layer over them. 
 * Dependencies:
 * - "../../platform/posix/context_lib_port.h"
 * 
 * \todo Do second include in some better way
 * \todo Some of these would probably work much more efficient as macros
 * \todo Most of these functions should be probably refactored to private ones
 * \todo Instructions should contain description for creating custom L1 function
 * \note \c save and \c load functions are already implemented and they work with 
 * addresses in standard C way
 * \note \c send \c rcv functions can be implemented and used for various types of data storage
 * \author    Michal Zidzik
 * \date      02.03.2026
 */
#include "../../platform/posix/context_lib_port.h"

/*!
* \name Saving functions
* @{
* \brief Functions for saving data.
*
* These functions simply take given value and store it as-is to given address
*
* \c save versions are basically one line long: 
* - \code *addr = B; \endcode
*
* \c send versions are not implemented as they are meant to cover wide variety of
* possible data management techniques. If one wishes to store data into new device, it's
* necesssary to provide implementation of function for sending bytes
*/
cl_int_t cl_raw_save_B(uint8_t B, uint8_t *addr, void *not_used);
cl_int_t cl_raw_send_B(uint8_t B, uint8_t *addr, void *not_used);
cl_int_t cl_raw_custom_send_B(uint8_t B, uint8_t *addr, void *custom_other_data);
cl_int_t cl_raw_save_hw(uint16_t hw, uint16_t *addr, void *not_used);
cl_int_t cl_raw_send_hw(uint16_t hw, uint16_t *addr, void *not_used);
cl_int_t cl_raw_custom_send_hw(uint16_t hw, uint16_t *addr, void *custom_other_data);
cl_int_t cl_raw_save_w(uint32_t w, uint32_t *addr, void *not_used);
cl_int_t cl_raw_send_w(uint32_t w, uint32_t *addr, void *not_used);
cl_int_t cl_raw_custom_send_w(uint32_t w, uint32_t *addr, void *custom_other_data);
cl_int_t cl_raw_save_dw(uint64_t dw, uint64_t *addr, void *not_used);
cl_int_t cl_raw_send_dw(uint64_t dw, uint64_t *addr, void *not_used);
cl_int_t cl_raw_custom_send_dw(uint64_t dw, uint64_t *addr, void *custom_other_data);
/*! @}*/

/*!
* \name Saving abstract layer
* @{
* \brief Wrapper over saving functions that simply calls one of them based on bus size.
* \todo This would work better as a macro
*/
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_custom_send_e(cl_int_t e, cl_addr_t addr, void *custom_other_data);
/*! @}*/


/*!
* \name Loading functions
* @{
* \brief Functions for loading data.
* These functions simply take value from one address and store it as-is to another address
* \c load versions are basically one line long: 
* - \code *b = *addr; \endcode
* \c rcv versions are not implemented as they are meant to cover wide variety of
* possible data management techniques. If one wishes to load data from new device, it's
* necesssary to provide implementation of function for sending bytes
*/
cl_int_t cl_raw_load_B(uint8_t *B, uint8_t *addr, void *not_used);
cl_int_t cl_raw_rcv_B(uint8_t *B, uint8_t *addr, void *not_used);
cl_int_t cl_raw_custom_rcv_B(uint8_t *B, uint8_t *addr, void *custom_other_data);
cl_int_t cl_raw_load_hw(uint16_t *hw, uint16_t *addr, void *not_used);
cl_int_t cl_raw_rcv_hw(uint16_t *hw, uint16_t *addr, void *not_used);
cl_int_t cl_raw_custom_rcv_hw(uint16_t *hw, uint16_t *addr, void *custom_other_data);
cl_int_t cl_raw_load_w(uint32_t *w, uint32_t *addr, void *not_used);
cl_int_t cl_raw_rcv_w(uint32_t *w, uint32_t *addr, void *not_used);
cl_int_t cl_raw_custom_rcv_w(uint32_t *w, uint32_t *addr, void *custom_other_data);
cl_int_t cl_raw_load_dw(uint64_t *w, uint64_t *addr, void *not_used);
cl_int_t cl_raw_rcv_dw(uint64_t *w, uint64_t *addr, void *not_used);
cl_int_t cl_raw_custom_rcv_dw(uint64_t *w, uint64_t *addr, void *custom_other_data);
/*! @}*/

/*!
* \name Loading abstract layer
* @{
* \brief Wrapper over loading functions that simply calls one of them based on bus size.
* \todo This would work better as a macro
*/
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_custom_rcv_e(cl_addr_t e, cl_addr_t addr, void *custom_other_data);
/*! @} */

/*
TODO: either delete or use this somehow
cl_int_t cl_bare_save(cl_addr_t data, cl_addr_t addr, cl_int_t byte_size, enum Bare_save_type save_type, void *custom_other_data);
cl_int_t cl_bare_load(cl_addr_t buffer, cl_addr_t addr, cl_int_t byte_size, enum Bare_save_type load_type, void *custom_other_data); 
uint32_t cl_raw_save_arr_B(uint8_t *data, uint8_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_save_arr_hw(uint16_t *data, uint16_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_save_arr_w(uint32_t *data, uint32_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_B(uint8_t *buffer, uint8_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_hw(uint16_t *buffer, uint16_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_w(uint32_t *buffer, uint32_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
*/

#endif