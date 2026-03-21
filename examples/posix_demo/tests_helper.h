#ifndef INCLUDE_TESTS_HELPER
#define INCLUDE_TESTS_HELPER
/*! 
 * \file      tests_helper.h
 * \brief     Helper functions for testing
 * \details   
 * Set of simple and short functions for printing, clearing
 * and filling with set of default values for tested memory and
 * peripheral areas.
 * 
 * \author    Michal Zidzik
 * \date      02.03.2026
 */
#include "context_manager.h"

/*!
* \name Clear functions
* @{
* 
* \details
* These functions fill memory areas with zeroes to simulate
* their erasure.
*/
void lram_clear();
void hram_clear();
void rf_clear();
void outside1_clear();
void outside2_clear();
void flash_clear();
void gpio_clear();
void uart0_clear();
void spi0_clear();
void i2c0_clear();
void timer0_clear();
void registers_clear();
void clear_all();
/*! @}*/

/*!
* \name Print functions
* @{
* 
* \details
* Functions use \c stdio.h to print contents
* of context areas. For the longer ones, print
* interval can be specified.
*/
void print_lram(cl_int_t start,cl_int_t end);
void print_hram(cl_int_t start,cl_int_t end);
void print_rf(cl_int_t start,cl_int_t end);
void print_rf2(cl_int_t start,cl_int_t end);
void print_uart0_regs();
void print_spi0_regs();
void print_i2c0_regs();
void print_timer0_regs();
void print_gpio_regs();
void registers_print();
/*! @}*/


/*!
* \name Fill functions
* @{
* 
* \details
* Functions fill memory areas with values for testing
*/
void uart0_fill();
void spi0_fill();
void i2c0_fill();
void timer0_fill();
void gpio_fill();
void registers_fill();
void hram_fill1();
void lram_fill1();
void lram_fill2(cl_int_t *array,cl_int_t start, cl_int_t elements);
void hram_fill2(cl_int_t *array,cl_int_t start, cl_int_t elements); 
/*! @}*/
#endif