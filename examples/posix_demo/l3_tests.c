/*! 
 * \file      l2_tests.c
 * \brief     Test for library layer 3
 * \details   
 * 
 * Tests automatic saving and loading of context.
 *
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \note While I designed every test in this file, many of them were written using GPT or Copilot
 * \note Tests are commented out as it's really hard to check them all at once in their current state
 */
#include "context_manager.h"
#include "l3_tests.h"
#include "tests_helper.h"

void l3_t11()
{
    // 1.1 Protect memory, then save and load it repeatedly using area_off/area_on
    cl_clear_mem_area(ma10,NULL);
    hram_fill1();
    cl_protect_memory(100);
    cl_write_mode(CL_STOP);
    cl_area_off(100,NULL);
    hram_clear();
    cl_area_on(100,NULL);
    print_lram(0,10);
    print_hram(0,5);
}

void l3_t12()
{
    // 1.2 Protect peripheral, then save and load it repeatedly using area_off/area_on
    cl_clear_mem_area(ma10,NULL);
    uart0_fill();
    cl_protect_memory(200);
    cl_write_mode(CL_RUN);
    cl_area_off(200,NULL);
    cl_area_on(200,NULL);
    printf("1.2 EXPECTED: [0,<A>,2000,2001,...] [2000,2001,2002,2003,2004]\n");
    print_lram(0,20);
    print_uart0_regs();
    cl_area_off(200,NULL);
    cl_area_on(200,NULL);
    cl_area_off(200,NULL);
    cl_area_on(200,NULL);
    printf("1.2 EXPECTED: [0,<A>,2000,2001,...] [2000,2001,2002,2003,2004]\n");
    print_lram(0,30);
    print_uart0_regs();
}

void l3_t13()
{
    // 1.3 Protect multiple ma's, then load and save them repeatedly using area_off/area_on
    cl_clear_mem_area(ma10,NULL);
    hram_fill1();
    registers_fill();
    registers_print();
    cl_protect_memory(200);
    cl_protect_memory(201);
    cl_protect_memory(204);
    cl_protect_memory(203);
    cl_write_mode(CL_RUN);
    cl_area_off(200,NULL);
    uart0_clear();
    cl_area_off(201,NULL);
    spi0_clear();
    cl_area_on(200,NULL);
    cl_area_off(204,NULL);
    gpio_clear();
    cl_area_off(203,NULL);
    timer0_clear();
    printf("1.3 EXPECTED: [204,<A>,2040,2041...,201,<A>,2010,...,204,<A>,204x,...,203,<A>,2030,...,0,<A>,..]\n");
    print_lram(0,40);
}

void l3_t14()
{
    // 1.4 Protect multiple ma's, then load and save them repeatedly using area_off_area on
    cl_clear_mem_area(ma10,NULL);
    registers_fill();
    cl_protect_memory(201);
    cl_protect_memory(202);
    cl_protect_memory(203);
    cl_write_mode(CL_RUN);
    cl_area_off(203,NULL);
    timer0_clear();
    cl_area_on(203,NULL);
    print_timer0_regs();
    cl_area_off(202,NULL);
    i2c0_clear();
    cl_area_off(201,NULL);
    spi0_clear();
    cl_area_off(204,NULL);
    gpio_clear();
    cl_area_on(202,NULL);
    printf("1.4 EXPECTED: UART,I2C and TIMER have contents saved\n");
    registers_print();
    printf("1.4 EXPECTED: [0,<A>,2020,...,201,<A>,2010,...]\n");
    print_lram(0,40);
}

void l3_t15()
{
    // 1.5 Protect memory, then save and load it repeatedly using change_mode
    cl_clear_mem_area(ma10,NULL);
    hram_fill1();
    cl_protect_memory(100);
    cl_write_mode(CL_RUN);
    cl_change_mode(CL_STOP,NULL);
    hram_clear();
    cl_change_mode(CL_RUN,NULL);
    printf("1.5 EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    cl_change_mode(CL_STOP,NULL);
    hram_clear();
    cl_change_mode(CL_RUN,NULL);
    printf("1.5 EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    print_lram(0,10);
}

void l3_t16()
{
    // 1.6 Protect peripheral, then save and load it repeatedly using change_mode
    cl_clear_mem_area(ma1,NULL);
    registers_fill();
    cl_protect_memory(204);
    cl_write_mode(CL_RUN);
    cl_change_mode(CL_VLLS,NULL);
    registers_clear();
    cl_change_mode(CL_RUN,NULL);
    print_gpio_regs();
    cl_change_mode(CL_VLLS,NULL);
    registers_clear();
    cl_change_mode(CL_RUN,NULL);
    printf("1.6 EXPECTED: [2040,2041,...]\n");
    print_gpio_regs();
}

void l3_t17()
{
    // 1.7 Protect multiple ma's, then load and save them repeatedly using change_mode
    puts("L3 T1.7");
    cl_clear_mem_area(ma10,NULL);
    hram_fill1();
    cl_protect_memory(102);
    cl_protect_memory(103);
    cl_protect_memory(104);
    cl_write_mode(CL_RUN);
    cl_change_mode(CL_STOP,NULL);
    hram_clear();
    cl_change_mode(CL_RUN,NULL);
    printf("1.7 EXPECTED: [10,11,12,13,14] [15,16,17,18,19,20] [20,21,22,23,24,25,26]\n");
    print_hram(20,25);
    print_hram(30,36);
    print_hram(40,47);
    cl_protect_memory(105);
    cl_unprotect_memory(103);
    cl_unprotect_memory(102);
    hram_fill1();
    cl_change_mode(CL_STOP,NULL);
    hram_clear();
    cl_change_mode(CL_RUN,NULL);
    printf("1.7 EXPECTED: [0,0,0,0,0] [0,0,0,0,0,0] [20,21,22,23,24,25,26] [25,26,27,28]\n");
    print_hram(20,25);
    print_hram(30,36);
    print_hram(40,47);
    print_hram(50,54);
    print_lram(0,40);
}
void l3_t21()
{
    // 2.1 With A->B->C, change into mode that turns off A and B
    // FAILED
    cl_write_mode(CL_RUN);
    cl_clear_mem_area(ma10,NULL);
    cl_clear_mem_area(ma1,NULL);

    hram_fill1();   // naplní A

    cl_protect_memory(100); // A
    cl_protect_memory(10);  // B

    cl_change_mode(CL_VLLS,NULL);
    hram_clear();
    lram_clear();
    printf("2.1 EXPECTED: [10,<A>,100,<A>,0,1,2,3,4,0,<A>\n");
    print_rf(0,15);       // C contains data from B
}

void l3_t22()
{
    // 2.2 With A->B->C, change into mode that turns on A and B
    // this test needs to be run after 2.1 
    // FAILED
    cl_change_mode(CL_RUN,NULL);
    printf("2.2 EXPECTED: [0,<A>,0,1,2,3,4,0,<A>] [0,1,2,3,4]\n");
    print_lram(0,10);
    print_hram(0,5);
}

void l3_t23()
{
    // 2.3 With A->B->C->D, change into mode that turns off A and B, then turn off C
    cl_clear_mem_area(ma10,NULL);
    cl_clear_mem_area(ma1,NULL);
    cl_clear_mem_area(ma2,NULL);

    hram_fill1();

    cl_protect_memory(100); // A
    cl_protect_memory(10);  // B
    cl_protect_memory(1);   // C

    cl_write_mode(CL_RUN);

    cl_change_mode(CL_VLLS,NULL);
    hram_clear();
    lram_clear();
    cl_change_mode(CL_VLLS0,NULL);
    rf_clear();
    printf("2.3 EXPECTED: [1,<A>,10,<A>,100,<A>,0,1,2,3,4,0,<A>\n");
    print_rf2(0,20);
}

void l3_t24()
{
    // 2.4 With A->B->C->D, change into mode that turns off A and B and C
    cl_clear_mem_area(ma10,NULL);
    cl_clear_mem_area(ma1,NULL);
    cl_clear_mem_area(ma2,NULL);

    hram_fill1();

    cl_protect_memory(100); // A
    cl_protect_memory(10);  // B
    cl_protect_memory(1);   // C

    cl_write_mode(CL_RUN);
    cl_change_mode(CL_VLLS0,NULL);
    hram_clear();
    lram_clear();
    rf_clear();
    printf("2.4 EXPECTED: [1,<A>,10,<A>,100,<A>,0,1,2,3,4,0,<A>\n");
    print_rf2(0,20);
} 

void l3_t25() {
    // 2.5 With A->B->C->D, change into mode that turns on C and D
    // currently won't work
    // run after 2.3
    cl_change_mode(CL_STOP,NULL);
    printf("2.5 EXPECTED: (no clue honestly)\n");
    print_rf(0,15);
    print_lram(0,10);
    print_hram(0,5);
}

void l3_t26() {
    // 2.6 With A->B->C->D, change into mode that turns on A and B and C
    // run after 2.4
    cl_change_mode(CL_RUN,NULL);
    printf("2.6 EXPECTED: no clue honestly\n");
    print_rf(0,10);
    print_lram(0,10);
    print_hram(0,5);
}

void l3_t27() {
    // 2.7 With A->B->C, first turn off A, then turn off B
    // SUCCESS
    cl_clear_mem_area(ma10,NULL);
    cl_clear_mem_area(ma1,NULL);
    hram_fill1();
    cl_protect_memory(100);
    cl_protect_memory(10);
    cl_write_mode(CL_RUN);
    cl_change_mode(CL_STOP,NULL);   // vypne A (A->B)
    hram_clear();
    cl_change_mode(CL_VLLS,NULL);  // vypne B (B->C)
    lram_clear();
    printf("2.7 EXPECTED: [10,<A>,100,<A>,0,1,2,3,4,0,<A>\n");
    print_rf(0,12);
}

void l3_t28() {
    // 2.8 With A->B->C, first turn on B, then turn on A
    // need to run 2.7 or 2.1 first
    // SUCCESS
    cl_change_mode(CL_STOP,NULL);  // restore B from C
    cl_change_mode(CL_RUN,NULL);   // restore A from B

    printf("2.8 EXPECTED: [0,<A>,0,1,2,3,4,0,<A>] [0,1,2,3,4]\n");
    print_lram(0,10);
    print_hram(0,5);
}

void l3_test1()
{
    // l3_t11(); //v0.5.0 : success
    // l3_t12(); //v0.5.0 : success
    // l3_t13(); //v0.5.0 : success
    // l3_t14(); //v0.5.0 : success
    // l3_t15(); //v0.5.0 : success
    // l3_t16(); //v0.5.0 : success
    l3_t17(); //v0.5.0 : success
}
void l3_test2()
{
    //1: FAILURE: I have not seen situation like this in any real-life scenario, it would be good if it worked but not necessary
    // l3_t27();
    // l3_t28();
    //2:
    // l3_t27();
    // l3_t22();
    //3:
    // l3_t21();
    // l3_t28();
    //4:
    // l3_t21();
    // l3_t22();

    // l3_t21();
    // l3_t22();
    // l3_t23();
    // l3_t24();
    // l3_t25();
    // l3_t26();
    // l3_t27();
    // l3_t28();
}