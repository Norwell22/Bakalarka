#ifndef CL_INCLUDE_LAYER_3_PRIV
#define CL_INCLUDE_LAYER_3_PRIV

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