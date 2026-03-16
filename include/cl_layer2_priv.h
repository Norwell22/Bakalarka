#ifndef CL_INCLUDE_LAYER_2_PRIV
#define CL_INCLUDE_LAYER_2_PRIV

/*! 
 * \file      cl_layer2_priv.h
 * \brief     Helper functions for second library layer
 * \details   
 * This set of types and functions gives user a way to define memory areas
 * and peripherals that he wishes to protect. Saving on this level is structured,
 * contains some metadata and is hugely dependent on contents of \c context_lib_port.c :
 * functions and types defined there should probably be studied before these ones.
 * Dependencies:
 * - "../../platform/posix/context_lib_port.h"
 * 
 * \note Context management works primarily on the base of memory areas
 * \note Areas can be used as either source or destination areas: we do not recommend mixing that up
 * \todo Do second include in some better way
 * \todo Move non-api functions to some better place
 * \author    Michal Zidzik
 * \date      02.03.2026
 */
#include "../../platform/posix/context_lib_port.h"

/*!
* \brief Helper function that chooses between save/send/custom function for storing data.
*
* Simple function that returns save/send/custom_e function. Used to make L2 functions bit easier
* to understand
* \return One of \c cl_save_e , \c cl_send_e , \c cl_custom_send_e functions
*/
cl_save_f_t sel_save_f(enum Bare_save_type save_type);

/*!
* \brief Helper function that chooses between load/rcv/custom function for loading data.
*
* Simple function that returns load/rcv/custom_e function. Used to make L2 functions bit easier
* to understand
* \return One of \c cl_load_e , \c cl_rcv_e , \c cl_custom_rcv_e functions
*/
cl_load_f_t sel_load_f(enum Bare_save_type save_type);

/*!
* \brief Function that moves data from one memory block to another
*
* Helper function that moves data, byte by byte from source addresses to destination addresses.
* It ends by either saving every element from source or running out of space in destination. It
* is used as a helper function to make L2 functions easier to understand.
* \param save_f Function used for saving individual elements
* \return Number of saved elements
*/
cl_int_t fill_block(cl_save_f_t save_f,cl_addr_t start_src_a, cl_addr_t end_src_a, cl_addr_t start_dst_a, cl_addr_t end_dst_a,void *custom_d);


/*!
* \brief Load version of \c fill_block
* \return Number of loaded elements
* \todo Check if it cannot be replaced by \c fill_block
*/
cl_int_t load_block(cl_load_f_t load_f,cl_addr_t start_src_a, cl_addr_t end_src_a, cl_addr_t start_dst_a, cl_addr_t end_dst_a,void *custom_d);

/*!
* \brief Actual implementation of reading and loading function
*
* API functions \c cl_read_mem_area and \c cl_load_mem_area are both very similar in functionality. 
* They basically just serve as formal ad-on over this function, which actually implements their 
* functionality. 
* \param erase Chooses between \a read and \a load functionality
* \todo Param should be of type \c bool 
*/
cl_int_t read_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area,void *custom_d,uint8_t erase);

cl_int_t read_load_peripheral_area(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, void *custom_d, uint8_t erase);

#endif