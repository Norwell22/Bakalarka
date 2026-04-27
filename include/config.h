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
* Logging in this library is implemented via third party ulog library 
* \a (see \c \ulog \a subfolder). If this macro is defined, logging library translates
* and logging output is created.
*
* \note Disable logging by commenting this line out
* \todo Try to do this in some better way, now ulog has to include this file
*/

/*
typedef enum {
  ULOG_TRACE_LEVEL=100,
  ULOG_DEBUG_LEVEL,
  ULOG_INFO_LEVEL,
  ULOG_WARNING_LEVEL,
  ULOG_ERROR_LEVEL,
  ULOG_CRITICAL_LEVEL,
  ULOG_ALWAYS_LEVEL
} ulog_level_t;
*/

#define ULOG_ENABLED
#define ULOG_CONSOLE_ENABLE
#define ULOG_CONSOLE_LEVEL ULOG_INFO_LEVEL
//#define ULOG_FILE_ENABLE 
#define ULOG_FILE_LEVEL ULOG_DEBUG_LEVEL
#define ULOG_FILE_NAME "cl_logging.txt"
#define ULOG_CUSTOM_ENABLE

/*!
* \brief Allow layer 3 of the library (automatic context management)
* 
* Layers 2 and 3 are relatively independent parts of this library API (with 
* L3 building upon L2). Because layer 3 comes up with a lot of metadata and 
* additional functions, there is an option to turn it off. While this reduces
* library size and complexity, usefulness of this version of library is questionable
*/

#define CL_ALLOW_L3

/*!
* \brief Determine, whether areas should be protected by default
*
* If this macro is defined, every context area starts in protected mode 
* and is saved in case it is going to be erased. If it's not defined, 
* every context area starts in unprotected mode. This default behaviour
* can be overwritten using \c cl_protect_memory and \c cl_unprotect_memory
* functions
*/
//#define CL_DEFAULT_PROTECT

#endif