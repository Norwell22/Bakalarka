/*! 
 * \file      tests.c
 * \brief     Testbench for general version of this library
 * \details   
 * Dependencies:
 - "../../include/main/context_manager.h"
 - "use_cases.h"
 * While big part of this library depends on specifics of microcontrollers and their memories,
 * many functions are designed to be platform independent. This file provides moderately large
 * set of tests for those functions. Currently none of these tests are automatized and they work
 * on simple run and compare expected vs actual output manually principle.
 * 
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \todo Try to find out an easy way to automatize these tests
 * \note While I designed tests in this file, many of them were written using GPT or Copilot
 * \note Tests are commented out as it's really hard to check them all at once in their current state
 */
#include <stdio.h>
#include "context_manager.h"
#ifdef CL_ALLOW_L3

#include "tests_helper.h"
#include "l2_tests.h"
#include "l3_tests.h"

/*!
* \brief Layer 2 tests
* 
* \details 
* 1. cl_save_mem_area
*    1.1 save data into empty array: SUCCESS
*    1.2 save part of data into small empty array: SUCCESS
*    1.3 save part of data into array occupied at the start: SUCCESS
*    1.4 save part of data into array occupied at the end: SUCCESS
*    1.5 save part of data into array occupied in the middle: SUCCESS
*    1.6 save data into complicated array 1: SUCCESS
*    1.7 save data into complicated array 2: SUCCESS
*    1.8 save data into complicated array 3: SUCCESS
*    1.10 refuse to save data into full array: SUCCESS
*
* 2. cl_load_mem_area: SUCCESS
*    2.1 load whole dataset: SUCCESS
*    2.2 load data from begining: SUCCESS
*    2.3 load data from end: SUCCESS
*    2.4 load part of data: SUCCESS
*    2.5 load two parts of data: SUCCESS
*    2.6 load three parts of data: SUCCESS
*
* 3. cl_save/load_peripheral
*    3.1 save and then load peripheral area: SUCCESS
*
* 4. mem_area functions combined
*    4.1 save-read-load:
*    4.2 read:
*    4.3 read-load:
*    4.4 save-save-read-load:
*    4.5 save-save-load-read: 
*    4.6 load-save-save-load-save-load: 
*    4.7 save-save-save-save-load-load-read-load-save-load-save-save-save-load: 
*
*  5. save into areas that use special functions
*   5.1 save data into area that uses special function: SUCCESS
*   5.2 save and load data from area that uses special function: SUCCESS
*   5.3 save part of data into area that uses special function: SUCCESS
*   5.4 save and load part of data from area that uses special function: SUCCESS
*
*
* \note Not all tests have been yet implemented
* \todo Implement rest of tests
*/
void l2_tests()
{
    l2_test1();
    l2_test2();
    l2_test3();
    l2_test4();
    l2_test5();
}

/*!
* \brief Layer 3 tests
* 
* \details
*   1.1 Protect memory, then save and load it repeatedly using area_off/area_on
*   1.2 Protect peripheral, then save and load it repeatedly using area_off/area_on
*   1.3 Protect multiple ma's, then load and save them repeatedly using area_off/area_on
*   1.4 Protect multiple ma's, then load and save them repeatedly using area_off_area on
*   1.5 Protect memory, then save and load it repeatedly using change_mode
*   1.6 Protect peripheral, then save and load it repeatedly using change_mode
*   1.7 Protect multiple ma's, then load and save them repeatedly using change_mode
*
* 2. Recursive load-save
*     2.1 With A->B->C, change into mode that turns off A and B
*     2.2 With A->B->C, change into mode that turns on A and B
*     2.3 With A->B->C->D, change into mode that turns off A and B
*     2.4 With A->B->C->D, change into mode that turns off A and B and C
*     2.5 With A->B->C->D, change into mode that turns on A and B
*     2.6 With A->B->C->D, change into mode that turns on A and B and C
*     2.7 With A->B->C, first turn off A, then turn off B
*     2.8 With A->B->C, first turn on B, then turn on A
* 3. Errors
*     3.1 Protect area which will be too big to store
*     3.2 Protect two areas which will be too big to store
*     3.3 Protect area which at first could be stored and then not
*     3.4 With A->B->C, protect A so that it can be stored into B, but not into C
* 
* \note Not all tests have been yet implemented
* \todo Implement rest of tests
*/
void l3_tests()
{
    // 2.1 - 2.8
    l3_test1();
    
    //3.1 - 3.4
    //l3_test2();
}



cl_int_t main()
{
    cl_init();
    l2_tests();
    //l3_tests();
}
#else
int main()
{
    puts("tests\tLayer 3 not allowed, tests cannot be executed");
}
#endif