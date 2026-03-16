/*! 
 * \file      tests.c
 * \brief     Testbench for general version of this library
 * \details   
 * Dependencies:
 - "../../include/main/context_manager.h"
 - "use_cases.h"
 * While big part of this library depends on specifics of microcontrollers and their memories,
 * many functions are designed to be platform independent. This file provides moderately large
 * set of tests for those functions 
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \pre       Needs to include config.h with valid configuration declarations (TODO)
 * \note Tests are designed using \a posix pseudo port in mind.
 * \note While I designed tests in this file, many of them were written using GPT or Copilot
 * \todo Break this file into several smaller ones
 */
#include "../../include/main/context_manager.h"
#include "use_cases.h"

/*
==== Testbench for L1 + L2 ====
1. cl_save_mem_area
    1.1 save data into empty array: SUCCESS
    1.2 save part of data into small empty array: +1 bug where end address is not actually end address, but one behind
    1.3 save part of data into array occupied at the start: see 1.2
    1.4 save part of data into array occupied at the end: see 1.2
    1.5 save part of data into array occupied in the middle: see 1.2
    1.6 save data into complicated array 1: SUCCESS
    1.7 save data into complicated array 2: SUCCESS
    1.8 save data into complicated array 3: SUCCESS
    1.10 refuse to save data into full array: SUCCESS
2. cl_load_mem_area
    2.1 load whole dataset: SUCCESS
    2.2 load data from begining: SUCCESS
    2.3 load data from end: SUCCESS
    2.4 load part of data: SUCCESS
    2.5 load two parts of data: SUCCESS
    2.6 load three parts of data: SUCCESS
3. cl_save/load_peripheral
    3.1 save and then load peripheral area
4. mem_area functions combined
    4.1 save-read-load: SUCCESS
    4.2 read: SUCCESS
    4.3 read-load: SUCCESS
    4.4 save-save-read-load: SUCCESS
    4.5 save-save-load-read: SUCCESS
    4.6 load-save-save-load-save-load: SUCCESS
    4.7 save-save-save-save-load-load-read-load-save-load-save-save-save-load: SUCCESS
5. tests with special functions
    5.1 run 1.5 using special function
    5.2 run 1.7 using special function
    5.3 run 1.11 using special function
    5.4 run 2.5 using special function
    5.5 run 2.6 using special function
    5.6 run 4.4 using special function
    5.7 run 4.6 using special function
    5.8 run 4.7 using special function
6. Edge cases
    6.1 Save area with one free space


*/

void lram_clear()
{
    cl_int_t i;
    for (i = 0; i < 1024; i++){
        LRAM[i] = 0;
    }
}

void hram_clear()
{
    cl_int_t i;
    for (i = 0; i < 1024; i++){
        HRAM[i] = 0;
    }
}

void rf_clear()
{
    cl_int_t i;
    for (i = 0; i < 128; i++){
        REGISTER_FILE[i] = 0;
    }
}

void outside1_clear()
{
    cl_int_t i;
    for (i = 0; i < 256; i++){
        OUTSIDE1[i] = 0;
    }
}

void outside2_clear()
{
    cl_int_t i;
    for (i = 0; i < 256; i++){
        OUTSIDE2[i] = 0;
    }
}

void flash_clear()
{
    cl_int_t i;
    for (i = 0; i < 1024; i++){
        FLASH[i] = 0;
    }
}

void gpio_clear()
{
    cl_int_t i;
    for (i = 0; i < 16; i++){
        GPIO_REGS[i] = 0;
    }
}   

void uart0_clear()
{
    cl_int_t i;
    for (i = 0; i < 8; i++){
        UART0_REGS[i] = 0;
    }
}

void spi0_clear()
{
    cl_int_t i;
    for (i = 0; i < 6; i++){
        SPI0_REGS[i] = 0;
    }
}

void i2c0_clear()
{
    cl_int_t i;
    for (i = 0; i < 6; i++){
        I2C0_REGS[i] = 0;
    }
} 

void timer0_clear()
{
    cl_int_t i;
    for (i = 0; i < 10; i++){
        TIMER0_REGS[i] = 0;
    }
}

void registers_clear()
{
    gpio_clear();
    uart0_clear();
    spi0_clear();
    i2c0_clear();
    timer0_clear();
}

void clear_all()
{
    lram_clear();
    hram_clear();
    rf_clear();
    outside1_clear();
    outside2_clear();
    flash_clear();
    gpio_clear();
    uart0_clear();
    spi0_clear();
    i2c0_clear();
    timer0_clear();
}

void uart0_fill()
{
    cl_int_t i;
    for (i = 0; i < 8; i++){
        UART0_REGS[i] = 2000 + i;
    }
}

void spi0_fill()
{
    cl_int_t i;
    for (i = 0; i < 6; i++){
        SPI0_REGS[i] = 2010 + i;
    }
}

void i2c0_fill()
{
    cl_int_t i;
    for (i = 0; i < 6; i++){
        I2C0_REGS[i] = 2020 + i;
    }
}

void timer0_fill()
{
    cl_int_t i;
    for (i = 0; i < 10; i++){
        TIMER0_REGS[i] = 2030 + i;
    }
}

void gpio_fill()
{
    cl_int_t i;
    for (i = 0; i < 16; i++){
        GPIO_REGS[i] = 2040 + i;
    }
}

void registers_fill()
{
    uart0_fill();
    spi0_fill();
    i2c0_fill();
    timer0_fill();
    gpio_fill();
}

void hram_fill1()
{
    cl_int_t i,j,k;
    cl_int_t arr1[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    for(i = 0; i < 5; i++){
        HRAM[i] = arr1[i];
    }
    for(i = 0; i < 5; i++){
        HRAM[i + 10] = arr1[i + 5];
    }
    for(i = 0; i < 5; i++){
        HRAM[i + 20] = arr1[i + 10];
    }
    for(i = 0; i < 6; i++){
        HRAM[i + 30] = arr1[i + 15];
    }
    for(i = 0; i < 7; i++){
        HRAM[i + 40] = arr1[i + 20];
    }
    for(i = 0; i < 4; i++){
        HRAM[i + 50] = arr1[i + 25];
    }
}

void lram_fill2(cl_int_t *array,cl_int_t start, cl_int_t elements)
{
    cl_int_t i;
    for (i = start; i < start + elements; i++){
        LRAM[i] = array[i];
    }
}

void hram_fill2(cl_int_t *array,cl_int_t start, cl_int_t elements)
{
    cl_int_t i;
    for (i = start; i < start + elements; i++){
        HRAM[i] = array[i];
    }
}

void print_lram(cl_int_t start_i,cl_int_t end_i)
{
    printf("LRAM[%lu-%lu]:\n",start_i,end_i);
    cl_int_t i;
    for (i = start_i; i < end_i; i++){
        printf("%lu,",LRAM[i]);
    }
    printf("\n");
}

void print_hram(cl_int_t start_i,cl_int_t end_i)
{
    printf("HRAM[%lu-%lu]:\n",start_i,end_i);
    cl_int_t i;
    for (i = start_i; i < end_i; i++){
        printf("%lu,",HRAM[i]);
    }
    printf("\n");
}

void print_rf(cl_int_t start_i,cl_int_t end_i)
{
    printf("REGISTER_FILE[%lu-%lu]:\n",start_i,end_i);
    cl_int_t i;
    for (i = start_i; i < end_i; i++){
        printf("%lu,",REGISTER_FILE[i]);
    }
    printf("\n");
}

void print_rf2(cl_int_t start_i,cl_int_t end_i)
{
    printf("REGISTER_FILE2[%lu-%lu]:\n",start_i,end_i);
    cl_int_t i;
    for (i = start_i; i < end_i; i++){
        printf("%lu,",REGISTER_FILE2[i]);
    }
    printf("\n");
}

void print_uart0_regs()
{
    printf("UART0_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 8; i++){
        printf("%lu,",UART0_REGS[i]);
    }
    printf("\n");
}

void print_spi0_regs()
{
    printf("SPI0_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 6; i++){
        printf("%lu,",SPI0_REGS[i]);
    }
    printf("\n");
}

void print_i2c0_regs()
{
    printf("I2C0_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 6; i++){
        printf("%lu,",I2C0_REGS[i]);
    }
    printf("\n");
}

void print_timer0_regs()
{
    printf("TIMER0_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 10; i++){
        printf("%lu,",TIMER0_REGS[i]);
    }
    printf("\n");
}

void print_gpio_regs()
{
    printf("GPIO_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 16; i++){
        printf("%lu,",GPIO_REGS[i]);
    }
    printf("\n");
}

void registers_print()
{
    print_uart0_regs();
    print_spi0_regs();
    print_i2c0_regs();
    print_timer0_regs();
    print_gpio_regs();
}

// some tests were generated using AI
void l2_test1()
{
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_clear_mem_area(ma12,RAM_WRITE,NULL);
    hram_fill1();
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("1.1 EXPECTED: [100,<A>,0,1,2,3,4,0,<A>,0,0]\n");
    print_lram(0,11);
    printf("\n\n\n\n");

    cl_save_mem_area(ma100,ma12,RAM_WRITE,NULL);
    printf("1.2 EXPECTED: [100,<A>,0,1,2,0,0,0,0]\n");
    print_lram(120,129);
    printf("\n\n\n\n");

    cl_int_t arr3[20] = {55,(cl_int_t)(LRAM + 5),55,55,55,0,(cl_int_t)(LRAM + 10),0,0,0,0}; //1.3
    cl_int_t *parr3 = arr3;
    lram_fill2(parr3,0,20);
    cl_save_mem_area(ma100,ma13,RAM_WRITE,NULL);
    printf("1.3 EXPECTED: [55,<A>,55,55,55,100,<A>,0,1,2,3,0]\n");
    print_lram(0,14);
    printf("\n\n\n\n");
    
    cl_int_t arr4[20] = {0,(cl_int_t)(LRAM + 6),0,0,0,0,55,(cl_int_t)(LRAM + 10),55,55,55,0,(cl_int_t)(LRAM + 10)}; //1.4
    cl_int_t *parr4 = arr4;
    lram_fill2(parr4,0,20);
    cl_save_mem_area(ma100,ma13,RAM_WRITE,NULL);
    printf("1.4 EXPECTED: [100,<A>,0,1,2,3,55,<A>,55,55,55,0,<A>]\n");
    print_lram(0,14);
    printf("\n\n\n\n");

    cl_int_t arr5[20] = {0,(cl_int_t)(LRAM + 4),0,0,55,(cl_int_t)(LRAM + 7),55,0,(cl_int_t)(LRAM + 10),0,0};
    cl_int_t *parr5 = arr5;
    lram_fill2(parr5,0,20);
    cl_save_mem_area(ma100,ma13,RAM_WRITE,NULL);
    printf("1.5 EXPECTED: [100,<A>,0,1,55,<A>,55,100,<A>,2,3]\n");
    print_lram(0,14);
    printf("\n\n\n\n");

    // 1.6
    cl_int_t arr6[20] = {
        50,(cl_int_t)(LRAM + 4),55,56,0,(cl_int_t)(LRAM + 8),0,0,51,(cl_int_t)(LRAM + 10),0,
        (cl_int_t)(LRAM + 13),0,52,(cl_int_t)(LRAM + 16),57,0,(cl_int_t)(LRAM + 100),0,0
    };
    cl_int_t *parr6 = arr6;
    lram_fill2(parr6,0,20);
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("1.6 EXPECTED: [50,<A>,55,56,100,<A>,0,1,51,<A>,100,<A>,2,52,<A>,57,100,<A>,3,4,5]\n");
    print_lram(0,23);
    printf("\n\n\n\n");

    cl_int_t arr7[20] = {
        0,(cl_int_t)(LRAM + 5),0,0,0,50,(cl_int_t)(LRAM + 8),55,0,(cl_int_t)(LRAM + 14),0,0,0,0,51,
        (cl_int_t)(LRAM + 17),56,0,(cl_int_t)(LRAM + 20),0
    };
    cl_int_t *parr7 = arr7;
    lram_fill2(parr7,0,20);
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("1.7 EXPECTED: [100,<A>,0,1,2,50,<A>,55,100,<A>,3,4,0,<A>,51,<A>,56,0,<A>,0]\n");
    print_lram(0,20);

    cl_int_t arr8[25] = {
        50,(cl_int_t)(LRAM + 5),55,56,57,0,(cl_int_t)(LRAM + 11),0,0,0,0,51,(cl_int_t)(LRAM + 14),
        58,0,(cl_int_t)(LRAM + 18),0,0,52,(cl_int_t)(LRAM + 20),0,(cl_int_t)(LRAM + 23),0,53,(cl_int_t)(LRAM + 25)
    };
    cl_int_t *parr8 = arr8;
    lram_fill2(parr8,0,25);
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("1.8 EXPECTED: [50,<A>,55,56,57,100,<A>,0,1,2,3,51,<A>,58,100,<A>,4,0,52,<A>,0,<A>,0,53,<A>]\n");
    print_lram(0,25);

    cl_int_t arr9[10] = {50,(cl_int_t)(LRAM + 10)};
    cl_int_t *parr9 = arr9;
    lram_fill2(parr9,0,10);
    cl_save_mem_area(ma100,ma13,RAM_WRITE,NULL);
    printf("1.9 EXPECTED: [50,<A>,0,0,0,0,0,0,0]\n");
    print_lram(0,10);
}

void l2_test2()
{
    cl_int_t arr1[10] = {100,(cl_int_t)(LRAM + 7),0,1,2,3,4,0,(cl_int_t)(LRAM + 100)};
    cl_int_t *parr1 = arr1;
    lram_fill2(parr1,0,10);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("2.1 EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    print_lram(0,10);

    hram_clear();
    cl_int_t arr3[25] = {
        0,(cl_int_t)(LRAM + 5),0,0,0,100,(cl_int_t)(LRAM + 12),
        100,101,102,103,104,50,
        (cl_int_t)(LRAM + 20),55,55,55
    };
    cl_int_t *parr3 = arr3;
    lram_fill2(parr3,0,25);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("2.3 EXPECTED: [100,101,102,103,104]\n");
    print_hram(0,5);
    print_lram(0,25);

    // 2.4
    hram_clear();
    cl_int_t arr4[25] = {
        0,(cl_int_t)(LRAM + 5),0,0,0,100,(cl_int_t)(LRAM + 10),
        100,101,102,50,
        (cl_int_t)(LRAM + 100),55,55,55
    };
    cl_int_t *parr4 = arr4;
    lram_fill2(parr4,0,25);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("2.4 EXPECTED: [100,101,102,0,0]\n");
    print_hram(0,5);
    print_lram(0,25);

    // 2.5
    cl_int_t arr5[27] = {
        100,(cl_int_t)(LRAM + 4),101,102,0,(cl_int_t)(LRAM + 8),0,66,50,
        (cl_int_t)(LRAM + 14),
        55,56,57,58,0,(cl_int_t)(LRAM + 21),
        66,66,66,66,66,
        100,(cl_int_t)(LRAM + 25),103,104,0,(cl_int_t)(LRAM + 99)
    };
    cl_int_t *parr5 = arr5;
    lram_fill2(parr5,0,27);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("2.5 EXPECTED: [100,101,102,103,104]\n");
    print_hram(0,5);
    print_lram(0,25);

    // 2.6
    cl_int_t arr6[25] = {
        50,(cl_int_t)(LRAM + 3),55,100,(cl_int_t)(LRAM + 6),
        101,50,(cl_int_t)(LRAM + 10),55,56,0,
        (cl_int_t)(LRAM + 14),0,0,100,(cl_int_t)(LRAM + 18),
        102,103,0,(cl_int_t)(LRAM + 20),
        100,(cl_int_t)(LRAM + 23),
        104,50,(cl_int_t)(LRAM + 99)
    };
    cl_int_t *parr6 = arr6;
    lram_fill2(parr6,0,25);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("2.6 EXPECTED: [100,101,102,103,104]\n");
    print_hram(0,5);
    print_lram(0,25);

}

void l2_test3()
{
    spi0_fill();
    print_spi0_regs();
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    printf("MA201:%p\n",&ma201);
    cl_save_peripheral(&ma201,ma10,RAM_WRITE,NULL);
    printf("3.1 EXPECTED: [201,<A>,2010,2011,2012,2013,...]\n");
    print_lram(0,20);

    spi0_clear();
    cl_load_peripheral(&ma201,ma10,RAM_WRITE,NULL);
    printf("3.1 EXPECTED: [2010,2011,2012,2013...]\n");
    print_spi0_regs();

}

void l2_test4()
{
    hram_fill1();
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    hram_clear();
    cl_read_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("4.1 SAVE-READ EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    print_lram(0,10);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("4.1 +LOAD EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    print_lram(0,10);

    hram_clear();
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_read_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("4.2 READ EXPECTED: [0,0,0,0,0]\n");
    print_hram(0,5);
    print_lram(0,10);

    hram_clear();
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_read_mem_area(ma100,ma10,RAM_WRITE,NULL);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("4.3 READ-LOAD EXPECTED: [0,0,0,0,0]\n");
    print_hram(0,5);
    print_lram(0,10);

    hram_fill1();
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma101,ma10,RAM_WRITE,NULL);
    hram_clear();
    cl_read_mem_area(ma101,ma10,RAM_WRITE,NULL);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("4.3 SAVE-SAVE-READ-LOAD EXPECTED: [0,1,2,3,4],[5,6,7,8,9]\n");
    print_hram(0,5);
    print_hram(10,15);
    print_lram(0,16);

    hram_fill1();
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma101,ma10,RAM_WRITE,NULL);
    hram_clear();
    cl_load_mem_area(ma101,ma10,RAM_WRITE,NULL);
    cl_read_mem_area(ma101,ma10,RAM_WRITE,NULL);
    printf("4.3 SAVE-SAVE-LOAD-READ EXPECTED: [0,0,0,0,0],[5,6,7,8,9]\n");
    print_hram(0,5);
    print_hram(10,15);
    print_lram(0,16);

    hram_fill1();
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma101,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("4.3 LOAD-SAVE-SAVE EXPECTED: [101,<A>,5,6,7,8,9,100,<A>,0,1,2,3,4,0,<A>,0,0]\n");
    print_lram(0,13);
    cl_load_mem_area(ma101,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma102,ma10,RAM_WRITE,NULL);
    cl_load_mem_area(ma100,ma10,RAM_WRITE,NULL);
    printf("4.3 +LOAD-SAVE-LOAD EXPECTED: [102,<A>,10,11,12,13,14,0,<A>,1,2,3,4,0,<A>\n");
    print_lram(0,16);

    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma104,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma102,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma105,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma103,ma10,RAM_WRITE,NULL);
    printf("4.4 4xSAVE:\n");
    print_lram(0,16);
    hram_clear();
    cl_load_mem_area(ma105,ma10,RAM_WRITE,NULL);
    cl_load_mem_area(ma102,ma10,RAM_WRITE,NULL);
    cl_read_mem_area(ma103,ma10,RAM_WRITE,NULL);
    cl_load_mem_area(ma102,ma10,RAM_WRITE,NULL);
    printf("4.4 LOAD-LOAD-READ-LOAD EXPECTED [10,11,12,13,14][15,16,17,18,19,20][0,0,0,0,0,0,0][25,26,27,28,29]");
    print_hram(20,25);
    print_hram(30,36);
    print_hram(40,47);
    print_hram(50,54);
    print_lram(0,40);
    hram_fill1();
    cl_save_mem_area(ma100,ma10,RAM_WRITE,NULL);
    cl_save_mem_area(ma101,ma10,RAM_WRITE,NULL);
    cl_load_mem_area(ma103,ma10,RAM_WRITE,NULL);
    printf("4.4 EXPECTED [104,<A>,20,21,22,23,24,25,26,100,<A>,0,1,2,3,4,101,<A>,5,6,7,8,0,<A>,15,16,17,18,19,20,101,<A>,9,0,<A>,0");
    print_lram(0,40);

}

void l3_t11()
{
    // 1.1 Protect memory, then save and load it repeatedly using area_off/area_on
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    hram_fill1();
    cl_protect_memory(100);
    cl_area_off(100,STOP,NULL);
    hram_clear();
    cl_area_on(100,STOP,NULL);
    print_lram(0,10);
    print_hram(0,5);
}

void l3_t12()
{
    // 1.2 Protect peripheral, then save and load it repeatedly using area_off/area_on
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    uart0_fill();
    cl_protect_memory(200);
    cl_area_off(200,RUN,NULL);
    cl_area_on(200,RUN,NULL);
    printf("1.2 EXPECTED: [0,<A>,2000,2001,...] [2000,2001,2002,2003,2004]\n");
    print_lram(0,20);
    print_uart0_regs();
    cl_area_off(200,RUN,NULL);
    cl_area_on(200,RUN,NULL);
    cl_area_off(200,RUN,NULL);
    cl_area_on(200,RUN,NULL);
    printf("1.2 EXPECTED: [0,<A>,2000,2001,...] [2000,2001,2002,2003,2004]\n");
    print_lram(0,30);
    print_uart0_regs();
}

void l3_t13()
{
    // 1.3 Protect multiple ma's, then load and save them repeatedly using area_off/area_on
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    hram_fill1();
    registers_fill();
    registers_print();
    cl_protect_memory(200);
    cl_protect_memory(201);
    cl_protect_memory(204);
    cl_protect_memory(203);
    cl_area_off(200,RUN,NULL);
    uart0_clear();
    cl_area_off(201,RUN,NULL);
    spi0_clear();
    cl_area_on(200,RUN,NULL);
    cl_area_off(204,RUN,NULL);
    gpio_clear();
    cl_area_off(203,RUN,NULL);
    timer0_clear();
    printf("1.3 EXPECTED: [204,<A>,2040,2041...,201,<A>,2010,...,204,<A>,204x,...,203,<A>,2030,...,0,<A>,..]\n");
    print_lram(0,40);
}

void l3_t14()
{
    // 1.4 Protect multiple ma's, then load and save them repeatedly using area_off_area on
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    registers_fill();
    cl_protect_memory(201);
    cl_protect_memory(202);
    cl_protect_memory(203);
    cl_area_off(203,RUN,NULL);
    timer0_clear();
    cl_area_on(203,RUN,NULL);
    print_timer0_regs();
    cl_area_off(202,RUN,NULL);
    i2c0_clear();
    cl_area_off(201,RUN,NULL);
    spi0_clear();
    cl_area_off(204,RUN,NULL);
    gpio_clear();
    cl_area_on(202,RUN,NULL);
    printf("1.4 EXPECTED: UART,I2C and TIMER have contents saved\n");
    registers_print();
    printf("1.4 EXPECTED: [0,<A>,2020,...,201,<A>,2010,...]\n");
    print_lram(0,40);
}

void l3_t15()
{
    // 1.5 Protect memory, then save and load it repeatedly using change_mode
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    hram_fill1();
    cl_protect_memory(100);
    cl_change_mode(RUN,STOP,NULL);
    hram_clear();
    cl_change_mode(STOP,RUN,NULL);
    printf("1.5 EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    cl_change_mode(RUN,STOP,NULL);
    hram_clear();
    cl_change_mode(STOP,RUN,NULL);
    printf("1.5 EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    print_lram(0,10);
}

void l3_t16()
{
    // 1.6 Protect peripheral, then save and load it repeatedly using change_mode
    cl_clear_mem_area(ma1,RAM_WRITE,NULL);
    registers_fill();
    cl_protect_memory(204);
    cl_change_mode(RUN,VLLS,NULL);
    registers_clear();
    cl_change_mode(VLLS,RUN,NULL);
    print_gpio_regs();
    cl_change_mode(RUN,VLLS,NULL);
    registers_clear();
    cl_change_mode(VLLS,RUN,NULL);
    printf("1.6 EXPECTED: [2040,2041,...]\n");
    print_gpio_regs();
}

void l3_t17()
{
    // 1.7 Protect multiple ma's, then load and save them repeatedly using change_mode
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    hram_fill1();
    cl_protect_memory(102);
    cl_protect_memory(103);
    cl_protect_memory(104);
    cl_change_mode(RUN,STOP,NULL);
    hram_clear();
    cl_change_mode(STOP,RUN,NULL);
    printf("1.7 EXPECTED: [10,11,12,13,14] [15,16,17,18,19,20] [20,21,22,23,24,25,26]\n");
    print_hram(20,25);
    print_hram(30,36);
    print_hram(40,47);
    cl_protect_memory(105);
    cl_unprotect_memory(103);
    cl_unprotect_memory(102);
    hram_fill1();
    cl_change_mode(RUN,STOP,NULL);
    hram_clear();
    cl_change_mode(STOP,RUN,NULL);
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
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_clear_mem_area(ma1,RAM_WRITE,NULL);

    hram_fill1();   // naplní A

    cl_protect_memory(100); // A
    cl_protect_memory(10);  // B

    cl_change_mode(RUN,VLLS,NULL);
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
    cl_change_mode(VLLS,RUN,NULL);
    printf("2.2 EXPECTED: [0,<A>,0,1,2,3,4,0,<A>] [0,1,2,3,4]\n");
    print_lram(0,10);
    print_hram(0,5);
}

void l3_t23()
{
    // 2.3 With A->B->C->D, change into mode that turns off A and B, then turn off C
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_clear_mem_area(ma1,RAM_WRITE,NULL);
    cl_clear_mem_area(ma2,RAM_WRITE,NULL);

    hram_fill1();

    cl_protect_memory(100); // A
    cl_protect_memory(10);  // B
    cl_protect_memory(1);   // C

    cl_change_mode(RUN,VLLS,NULL);
    hram_clear();
    lram_clear();
    cl_change_mode(VLLS,VLLS0,NULL);
    rf_clear();
    printf("2.3 EXPECTED: [1,<A>,10,<A>,100,<A>,0,1,2,3,4,0,<A>\n");
    print_rf2(0,20);
}

void l3_t24()
{
    // 2.4 With A->B->C->D, change into mode that turns off A and B and C
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_clear_mem_area(ma1,RAM_WRITE,NULL);
    cl_clear_mem_area(ma2,RAM_WRITE,NULL);

    hram_fill1();

    cl_protect_memory(100); // A
    cl_protect_memory(10);  // B
    cl_protect_memory(1);   // C
    cl_change_mode(RUN,VLLS0,NULL);
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
    cl_change_mode(VLLS0,STOP,NULL);
    printf("2.5 EXPECTED: (no clue honestly)\n");
    print_rf(0,15);
    print_lram(0,10);
    print_hram(0,5);
}

void l3_t26() {
    // 2.6 With A->B->C->D, change into mode that turns on A and B and C
    // run after 2.4
    cl_change_mode(VLLS0,RUN,NULL);
    printf("2.6 EXPECTED: no clue honestly\n");
    print_rf(0,10);
    print_lram(0,10);
    print_hram(0,5);
}

void l3_t27() {
    // 2.7 With A->B->C, first turn off A, then turn off B
    // SUCCESS
    cl_clear_mem_area(ma10,RAM_WRITE,NULL);
    cl_clear_mem_area(ma1,RAM_WRITE,NULL);
    hram_fill1();
    cl_protect_memory(100);
    cl_protect_memory(10);
    cl_change_mode(RUN,STOP,NULL);   // vypne A (A->B)
    hram_clear();
    cl_change_mode(STOP,VLLS,NULL);  // vypne B (B->C)
    lram_clear();
    printf("2.7 EXPECTED: [10,<A>,100,<A>,0,1,2,3,4,0,<A>\n");
    print_rf(0,12);
}

void l3_t28() {
    // 2.8 With A->B->C, first turn on B, then turn on A
    // need to run 2.7 or 2.1 first
    // SUCCESS
    cl_change_mode(VLLS,STOP,NULL);  // restore B from C
    cl_change_mode(STOP,RUN,NULL);   // restore A from B

    printf("2.8 EXPECTED: [0,<A>,0,1,2,3,4,0,<A>] [0,1,2,3,4]\n");
    print_lram(0,10);
    print_hram(0,5);
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

void l3_test1()
{
    // l3_t11(); v0.5.0 : success
    // l3_t12(); v0.5.0 : success
    // l3_t13(); v0.5.0 : success
    // l3_t14(); v0.5.0 : success
    // l3_t15(); v0.5.0 : success
    // l3_t16(); v0.5.0 : success
    // l3_t17(); v0.5.0 : success
}

/* === Testbench for L3
2. Recursive load-save
    2.1 With A->B->C, change into mode that turns off A and B
    2.2 With A->B->C, change into mode that turns on A and B
    2.3 With A->B->C->D, change into mode that turns off A and B
    2.4 With A->B->C->D, change into mode that turns off A and B and C
    2.5 With A->B->C->D, change into mode that turns on A and B
    2.6 With A->B->C->D, change into mode that turns on A and B and C
    2.7 With A->B->C, first turn off A, then turn off B
    2.8 With A->B->C, first turn on B, then turn on A
3. Errors
    3.1 Protect area which will be too big to store
    3.2 Protect two areas which will be too big to store
    3.3 Protect area which at first could be stored and then not
    3.4 With A->B->C, protect A so that it can be stored into B, but not into C

*/

cl_int_t main()
{
    // l2_test1();
    // l2_test2();
    // l2_test3();
    // l2_test4();
    // l3_test1();
    l3_test2();
}