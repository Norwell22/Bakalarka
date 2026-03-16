#ifndef CL_INCLUDE_LAYER_2
#define CL_INCLUDE_LAYER_2

/*! 
 * \file      cl_layer2.h
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
cl_int_t cl_clear_mem_area(Cl_memory_area_t area, void *other_d);

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
cl_int_t cl_save_mem_area(Cl_memory_area_t src_area, Cl_memory_area_t dst_area , void *other_d);

/*!
* \brief This function loads data stored using \c cl_save_mem_area() function. 
* 
* It does so by searching source area and loading
* data from blocks with ID matching destination area
*/
cl_int_t cl_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, void *other_d);

/*!
* \brief This function reads data stored using \c cl_save_mem_area() function.
* 
* \note \b Loading and \b reading are very closely related terms: they almost mean the same thing. Only difference between
* them is that after loading, block in source area is marked as empty and can therefore be filled with new data while reading
* simply reads data into destination area without modifying source.
*/
cl_int_t cl_read_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, void *other_d);
/*! @}*/

/*!
* \name Peripheral management functions 
* @{
* \brief Equivalents of \c save,load,read functions, just for peripherals.
*
* \note Even peripheral functions use memory areas as a destinations
* \todo functions should use \c memory_area as destination. Change that
*/
cl_int_t cl_save_peripheral(const Cl_peripheral_area_t *src_area, Cl_memory_area_t dst_area,void *other_d);
cl_int_t cl_load_peripheral(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, void *other_d);
cl_int_t cl_read_peripheral(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, void *other_d);
/*! @}*/
#endif