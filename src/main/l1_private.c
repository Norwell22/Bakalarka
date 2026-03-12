/*! 
 * \file      l1_private.c
 * \brief     Part of functions implementing first library layer
 * \details   
 * Dependencies:
 * - "../../include/main/l1.h"
 * Implementation of two lowest-level, possibly user implemented functions
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \todo Merge with \c l1_public.c
 */
#include "../../include/main/l1.h"

__attribute__((weak)) cl_int_t save_byte(uint8_t b, uint8_t *addr)
{
   *addr = b; 
   return 0;
}

__attribute__((weak)) cl_int_t load_byte(uint8_t *b, uint8_t *addr)
{
   *b = *addr;
   return 0;
}