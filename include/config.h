#ifndef CL_INCLUDE_CONFIG
#define CL_INCLUDE_CONFIG

/*! 
 * \file      config.h
 * \brief     User preferences and platform-specific configuration
 * \details   
 * This file allows for several different options for compliling and working 
 * with context management library. Any changes are done simply by commenting, 
 * uncommenting or modifying macros specified below. While default options are
 * allways given, user of this library should pay attention to contents of this 
 * file. 
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \note Users are expected to modify contents of this file
 * \pre       Needs to include config.h with valid configuration declarations (TODO)
 */


/*!
* \brief Bus size of CPU used in target mcu
*
* This value has to be changed to bus width of your MCU. 
* Value has to be either 8,16,32 or 64 with the default option
* (expected on most modern microcontrollers) is 32.
* 32 and 64 are also the only values for which
* the library has been extensively tested.
* \todo For final version, change this to 32.
*/
#define ARCHITECTURE_BUS_SIZE 64

/*!
* \brief Allow logging
*
* 
*
* \todo Add once logging is implemented
*/
#define CL_LOGGING 1

/*!
* \brief Allow layer 3 of the library (automatic context management)
* 
* Layers 2 and 3 are relatively independent parts of this library API (with 
* L3 building upon L2). Because layer 3 comes up with a lot of metadata and 
* additional functions, there is an option to turn it off. While this reduces
* library size and complexity, usefulness of this version of library is questionable
*/
#define CL_ALLOW_L3

#endif