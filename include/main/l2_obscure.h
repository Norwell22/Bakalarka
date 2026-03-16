#ifndef CL_INCLUDE_LAYER_2
#define CL_INCLUDE_LAYER_2

/*! 
 * \file      l2.h
 * \brief     Memory areas definition, context loading and storage
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
* \brief Function that prepares memory area for context saving
*
* This function, once called initialize area to [0,<end_address>,0,0,0,0,...]
* this content is necessary for correct data storage and must therefore be called
* for every memory area that serves as storage destination
*/
cl_int_t cl_clear_mem_area(Cl_memory_area_t area, enum Bare_save_type clear_type, void *custom_other_data);

/*!
* \name Memory area management functions
* @{
*/

/*!
* \brief Function that saves contents of one memory area into another
*
* This function takes contents of one area and stores it into another in a structured way (with some metadata).
* It stores data in blocks, with each block being in format 
* \code [<area_id>,<block_end_addr>,<data_B1>,<data_B2>,...] \endcode
*/
cl_int_t cl_save_mem_area(Cl_memory_area_t src_area, Cl_memory_area_t dst_area , enum Bare_save_type save_type, void *custom_other_data);

/*!
* \brief This function loads data stored using \c cl_save_mem_area() function. 
* 
* It does so by searching source area and loading
* data from blocks with ID matching destination area
*/
cl_int_t cl_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type, void *custom_other_data);

/*!
* \brief This function reads data stored using \c cl_save_mem_area() function.
* 
* \note \b Loading and \b reading are very closely related terms: they almost mean the same thing. Only difference between
* them is that after loading, block in source area is marked as empty and can therefore be filled with new data while reading
* simply reads data into destination area without modifying source.
*/
cl_int_t cl_read_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type, void *custom_other_data);
/*! @}*/

/*!
* \name Peripheral management functions 
* @{
* \brief Equivalents of \c save,load,read functions, just for peripherals.
*
* \note Even peripheral functions use memory areas as a destinations
* \todo functions should use \c memory_area as destination. Change that
*/
cl_int_t cl_save_peripheral(const Cl_peripheral_area_t *src_area, Cl_memory_area_t dst_area, enum Bare_save_type save_type,void *custom_other_data);
cl_int_t cl_load_peripheral(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type, void *custom_other_data);
cl_int_t cl_read_peripheral(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type, void *custom_other_data);
/*! @}*/


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
cl_int_t read_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type,void *custom_d,uint8_t erase);

cl_int_t read_load_peripheral_area(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type,void *custom_d, uint8_t erase);

#endif