#ifndef INCLUDE_L2_TESTS
#define INCLUDE_L2_TESTS
/*! 
 * \file      l2_tests.h
 * \brief     Layer 2 testbench
 * \details   
 * 
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \todo Try to find out an easy way to automatize these tests
 * \note While I designed tests in this file, many of them were written using GPT or Copilot
 * \note Refer to \c tests.c documentation for concrete tests and their results
 */

 #include "tests_helper.h"

/*!
* \brief Test \c cl_save_mem_area
* 
* This function tests context saving into various destination arrays (empty, partially filled,
* filled in more complex ways).
*/
void l2_test1();

/*!
* \brief Test \c cl_load_mem_area
* 
* This function tests context loading from various destination arrays. Test cases are very similar to \c l2_test1
* tests. 
*/
void l2_test2();

/*! 
* \brief Test loading and saving of \a peripheral areas
*
* \todo Certainly add more tests here
*/
void l2_test3();

/*!
* \brief Test complex work with memory areas
*
* These test cases test saving and loading operations in different order and over different memory areas
* ranging to simple to more complex. 
*/
void l2_test4();
#endif