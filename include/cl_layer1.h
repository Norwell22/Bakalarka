#ifndef CL_INCLUDE_LAYER_1
#define CL_INCLUDE_LAYER_1

/*! 
 * \file      cl_layer1.h
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
* \name Saving abstract layer
* @{
* \brief Wrapper over saving functions that simply calls one of them based on bus size.
* \todo This would work better as a macro
*/
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d);
/*! @}*/


/*!
* \name Loading abstract layer
* @{
* \brief Wrapper over loading functions that simply calls one of them based on bus size.
* \todo This would work better as a macro
*/
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d);
/*! @} */

#endif