#ifndef CL_INCLUDE_LAYER_1_PRIV
#define CL_INCLUDE_LAYER_1_PRIV

/*! 
 * \file      cl_l1_priv.h
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
* \name Save/load byte
* @{
* \brief Lowest level data storage functions
*
* These functions serve for \c save versions of functions manipulating
* with data. They simply copy given byte to given address. 
* \note They may be reimplemented although it is not advised 
*/
static cl_int_t save_byte(uint8_t b, uint8_t *addr);
cl_int_t load_byte(uint8_t *b, uint8_t *addr);
/*! @}*/

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
cl_int_t raw_save_B(uint8_t B, uint8_t *addr, void *not_used);
cl_int_t raw_send_B(uint8_t B, uint8_t *addr, void *not_used);
cl_int_t raw_custom_send_B(uint8_t B, uint8_t *addr, void *custom_other_data);
cl_int_t raw_save_hw(uint16_t hw, uint16_t *addr, void *not_used);
cl_int_t raw_send_hw(uint16_t hw, uint16_t *addr, void *not_used);
cl_int_t raw_custom_send_hw(uint16_t hw, uint16_t *addr, void *custom_other_data);
cl_int_t raw_save_w(uint32_t w, uint32_t *addr, void *not_used);
cl_int_t raw_send_w(uint32_t w, uint32_t *addr, void *not_used);
cl_int_t raw_custom_send_w(uint32_t w, uint32_t *addr, void *custom_other_data);
cl_int_t raw_save_dw(uint64_t dw, uint64_t *addr, void *not_used);
cl_int_t raw_send_dw(uint64_t dw, uint64_t *addr, void *not_used);
cl_int_t raw_custom_send_dw(uint64_t dw, uint64_t *addr, void *custom_other_data);
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
cl_int_t raw_load_B(uint8_t *B, uint8_t *addr, void *not_used);
cl_int_t raw_rcv_B(uint8_t *B, uint8_t *addr, void *not_used);
cl_int_t raw_custom_rcv_B(uint8_t *B, uint8_t *addr, void *custom_other_data);
cl_int_t raw_load_hw(uint16_t *hw, uint16_t *addr, void *not_used);
cl_int_t raw_rcv_hw(uint16_t *hw, uint16_t *addr, void *not_used);
cl_int_t raw_custom_rcv_hw(uint16_t *hw, uint16_t *addr, void *custom_other_data);
cl_int_t raw_load_w(uint32_t *w, uint32_t *addr, void *not_used);
cl_int_t raw_rcv_w(uint32_t *w, uint32_t *addr, void *not_used);
cl_int_t raw_custom_rcv_w(uint32_t *w, uint32_t *addr, void *custom_other_data);
cl_int_t raw_load_dw(uint64_t *w, uint64_t *addr, void *not_used);
cl_int_t raw_rcv_dw(uint64_t *w, uint64_t *addr, void *not_used);
cl_int_t raw_custom_rcv_dw(uint64_t *w, uint64_t *addr, void *custom_other_data);
/*! @}*/


#endif