#ifndef CL_INCLUDE_LAYER_3
#define CL_INCLUDE_LAYER_3
/*! 
 * \file      l3.h
 * \brief     Automatic context management
 * \details   
 * Small set of functions that give user a way to automatically manage context.
 * After defining required metadata (refer to \c context_lib_port.h for details),
 * user can specify which areas he wants to be saved when memory is turned off. 
 * Then, when changing mode, he simply calls \c change_mode function and the rest
 * should happen automatically.
 * 
 * Dependencies:
 * - "../../platform/posix/context_lib_port.h"
 * \note In order to make third layer work, quite large set of metadata needs to
 * be declared in \c context_lib_port.h/c 
 * \todo Do second include in some better way
 * \author    Michal Zidzik
 * \date      02.03.2026
 */
#include "../../platform/posix/context_lib_port.h"

/*!
* \brief Inform the library, that the memory area has been turned on
*
* This function simulates the scenario, when memory area can be turned 
* on or off independently of power mode. In that case, area can be turned on 
* directly. 
* \todo Change parameter from id to memory area directly
*/
cl_int_t cl_area_on( cl_int_t id, void *other_d);

/*!
* \brief Mirrors \c cl_area_on
*/
cl_int_t cl_area_off( cl_int_t id, void *other_d);

/*!
* \brief Mark memory area as being protected in case it is turned off.
*
* If memory area that is marked as protected gets turned off, its content is loaded
* into area that serves for its protection.
* \todo Change parameter from id to memory area directly
*/
cl_int_t cl_protect_memory(cl_int_t id);

/*!
* \brief Mirrors \c cl_protect_memory
*/
cl_int_t cl_unprotect_memory(cl_int_t id);

/*!
* \brief Notifies library that mode has been changed and memory may need to be saved or loaded
*
* While the point of this function is relatively straightforward, its implementation is quite complicated.
* Function takes informations from several global variables that serve as metadata sources and it needs to
* compare quite a bit of data in order to determine which modes get turned on or off. 
*/
cl_int_t cl_change_mode(enum Cl_power_mode_t to_mode,void *other_d);

cl_int_t cl_unprotect_all();
cl_int_t cl_protect_all();

void cl_write_mode(enum Cl_power_mode_t mode);
enum Cl_power_mode_t cl_get_mode();

#endif