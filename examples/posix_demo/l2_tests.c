/*! 
 * \file      l2_tests.c
 * \brief     Test for library layer 2
 * \details   
 * These tests are mainly used to test saving and loading operations
 * over specific arrays. They test basic situation, edge cases and error
 * handling. 
 * 
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \todo Try to find out an easy way to automatize these tests
 * \note While I designed every test in this file, many of them were written using GPT or Copilot
 * \note Tests are commented out as it's really hard to check them all at once in their current state
 */
#include "context_manager.h"
#include "l2_tests.h"

void l2_test1()
{
    cl_clear_mem_area(ma10,NULL);
    cl_clear_mem_area(ma12,NULL);
    hram_fill1();
    cl_save_mem_area(ma100,ma10,NULL);
    printf("1.1 EXPECTED: [100,<A>,0,1,2,3,4,0,<A>,0,0]\n");
    print_lram(0,11);
    printf("\n\n\n\n");

    cl_save_mem_area(ma100,ma12,NULL);
    printf("1.2 EXPECTED: [100,<A>,0,1,2,0,0,0,0]\n");
    print_lram(120,129);
    printf("\n\n\n\n");

    cl_int_t arr3[20] = {55,(cl_int_t)(LRAM + 5),55,55,55,0,(cl_int_t)(LRAM + 10),0,0,0,0}; //1.3
    cl_int_t *parr3 = arr3;
    lram_fill2(parr3,0,20);
    cl_save_mem_area(ma100,ma13,NULL);
    printf("1.3 EXPECTED: [55,<A>,55,55,55,100,<A>,0,1,2,3,0]\n");
    print_lram(0,14);
    printf("\n\n\n\n");
    
    cl_int_t arr4[20] = {0,(cl_int_t)(LRAM + 6),0,0,0,0,55,(cl_int_t)(LRAM + 10),55,55,55,0,(cl_int_t)(LRAM + 10)}; //1.4
    cl_int_t *parr4 = arr4;
    lram_fill2(parr4,0,20);
    cl_save_mem_area(ma100,ma13,NULL);
    printf("1.4 EXPECTED: [100,<A>,0,1,2,3,55,<A>,55,55,55,0,<A>]\n");
    print_lram(0,14);
    printf("\n\n\n\n");

    cl_int_t arr5[20] = {0,(cl_int_t)(LRAM + 4),0,0,55,(cl_int_t)(LRAM + 7),55,0,(cl_int_t)(LRAM + 10),0,0};
    cl_int_t *parr5 = arr5;
    lram_fill2(parr5,0,20);
    cl_save_mem_area(ma100,ma13,NULL);
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
    cl_save_mem_area(ma100,ma10,NULL);
    printf("1.6 EXPECTED: [50,<A>,55,56,100,<A>,0,1,51,<A>,100,<A>,2,52,<A>,57,100,<A>,3,4,5]\n");
    print_lram(0,23);
    printf("\n\n\n\n");

    cl_int_t arr7[20] = {
        0,(cl_int_t)(LRAM + 5),0,0,0,50,(cl_int_t)(LRAM + 8),55,0,(cl_int_t)(LRAM + 14),0,0,0,0,51,
        (cl_int_t)(LRAM + 17),56,0,(cl_int_t)(LRAM + 20),0
    };
    cl_int_t *parr7 = arr7;
    lram_fill2(parr7,0,20);
    cl_save_mem_area(ma100,ma10,NULL);
    printf("1.7 EXPECTED: [100,<A>,0,1,2,50,<A>,55,100,<A>,3,4,0,<A>,51,<A>,56,0,<A>,0]\n");
    print_lram(0,20);

    cl_int_t arr8[25] = {
        50,(cl_int_t)(LRAM + 5),55,56,57,0,(cl_int_t)(LRAM + 11),0,0,0,0,51,(cl_int_t)(LRAM + 14),
        58,0,(cl_int_t)(LRAM + 18),0,0,52,(cl_int_t)(LRAM + 20),0,(cl_int_t)(LRAM + 23),0,53,(cl_int_t)(LRAM + 25)
    };
    cl_int_t *parr8 = arr8;
    lram_fill2(parr8,0,25);
    cl_save_mem_area(ma100,ma10,NULL);
    printf("1.8 EXPECTED: [50,<A>,55,56,57,100,<A>,0,1,2,3,51,<A>,58,100,<A>,4,0,52,<A>,0,<A>,0,53,<A>]\n");
    print_lram(0,25);

    cl_int_t arr9[10] = {50,(cl_int_t)(LRAM + 10)};
    cl_int_t *parr9 = arr9;
    lram_fill2(parr9,0,10);
    cl_save_mem_area(ma100,ma13,NULL);
    printf("1.9 EXPECTED: [50,<A>,0,0,0,0,0,0,0]\n");
    print_lram(0,10);
}

void l2_test2()
{
    cl_int_t arr1[10] = {100,(cl_int_t)(LRAM + 7),0,1,2,3,4,0,(cl_int_t)(LRAM + 100)};
    cl_int_t *parr1 = arr1;
    lram_fill2(parr1,0,10);
    cl_load_mem_area(ma100,ma10,NULL);
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
    cl_load_mem_area(ma100,ma10,NULL);
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
    cl_load_mem_area(ma100,ma10,NULL);
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
    cl_load_mem_area(ma100,ma10,NULL);
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
    cl_load_mem_area(ma100,ma10,NULL);
    printf("2.6 EXPECTED: [100,101,102,103,104]\n");
    print_hram(0,5);
    print_lram(0,25);

}

void l2_test3()
{
    spi0_fill();
    print_spi0_regs();
    cl_clear_mem_area(ma10,NULL);
    printf("MA201:%p\n",&ma201);
    cl_save_peripheral(&ma201,ma10,NULL);
    printf("3.1 EXPECTED: [201,<A>,2010,2011,2012,2013,...]\n");
    print_lram(0,20);

    spi0_clear();
    cl_load_peripheral(&ma201,ma10,NULL);
    printf("3.1 EXPECTED: [2010,2011,2012,2013...]\n");
    print_spi0_regs();

}

void l2_test4()
{
    hram_fill1();
    cl_clear_mem_area(ma10,NULL);
    cl_save_mem_area(ma100,ma10,NULL);
    hram_clear();
    cl_read_mem_area(ma100,ma10,NULL);
    printf("4.1 SAVE-READ EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    print_lram(0,10);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("4.1 +LOAD EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    print_lram(0,10);

    hram_clear();
    cl_clear_mem_area(ma10,NULL);
    cl_read_mem_area(ma100,ma10,NULL);
    printf("4.2 READ EXPECTED: [0,0,0,0,0]\n");
    print_hram(0,5);
    print_lram(0,10);

    hram_clear();
    cl_clear_mem_area(ma10,NULL);
    cl_read_mem_area(ma100,ma10,NULL);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("4.3 READ-LOAD EXPECTED: [0,0,0,0,0]\n");
    print_hram(0,5);
    print_lram(0,10);

    hram_fill1();
    cl_clear_mem_area(ma10,NULL);
    cl_save_mem_area(ma100,ma10,NULL);
    cl_save_mem_area(ma101,ma10,NULL);
    hram_clear();
    cl_read_mem_area(ma101,ma10,NULL);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("4.3 SAVE-SAVE-READ-LOAD EXPECTED: [0,1,2,3,4],[5,6,7,8,9]\n");
    print_hram(0,5);
    print_hram(10,15);
    print_lram(0,16);

    hram_fill1();
    cl_clear_mem_area(ma10,NULL);
    cl_save_mem_area(ma100,ma10,NULL);
    cl_save_mem_area(ma101,ma10,NULL);
    hram_clear();
    cl_load_mem_area(ma101,ma10,NULL);
    cl_read_mem_area(ma101,ma10,NULL);
    printf("4.3 SAVE-SAVE-LOAD-READ EXPECTED: [0,0,0,0,0],[5,6,7,8,9]\n");
    print_hram(0,5);
    print_hram(10,15);
    print_lram(0,16);

    hram_fill1();
    cl_clear_mem_area(ma10,NULL);
    cl_load_mem_area(ma100,ma10,NULL);
    cl_save_mem_area(ma101,ma10,NULL);
    cl_save_mem_area(ma100,ma10,NULL);
    printf("4.3 LOAD-SAVE-SAVE EXPECTED: [101,<A>,5,6,7,8,9,100,<A>,0,1,2,3,4,0,<A>,0,0]\n");
    print_lram(0,13);
    cl_load_mem_area(ma101,ma10,NULL);
    cl_save_mem_area(ma102,ma10,NULL);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("4.3 +LOAD-SAVE-LOAD EXPECTED: [102,<A>,10,11,12,13,14,0,<A>,1,2,3,4,0,<A>\n");
    print_lram(0,16);

    cl_clear_mem_area(ma10,NULL);
    cl_save_mem_area(ma104,ma10,NULL);
    cl_save_mem_area(ma102,ma10,NULL);
    cl_save_mem_area(ma105,ma10,NULL);
    cl_save_mem_area(ma103,ma10,NULL);
    printf("4.4 4xSAVE:\n");
    print_lram(0,16);
    hram_clear();
    cl_load_mem_area(ma105,ma10,NULL);
    cl_load_mem_area(ma102,ma10,NULL);
    cl_read_mem_area(ma103,ma10,NULL);
    cl_load_mem_area(ma102,ma10,NULL);
    printf("4.4 LOAD-LOAD-READ-LOAD EXPECTED [10,11,12,13,14][15,16,17,18,19,20][0,0,0,0,0,0,0][25,26,27,28,29]");
    print_hram(20,25);
    print_hram(30,36);
    print_hram(40,47);
    print_hram(50,54);
    print_lram(0,40);
    hram_fill1();
    cl_save_mem_area(ma100,ma10,NULL);
    cl_save_mem_area(ma101,ma10,NULL);
    cl_load_mem_area(ma103,ma10,NULL);
    printf("4.4 EXPECTED [104,<A>,20,21,22,23,24,25,26,100,<A>,0,1,2,3,4,101,<A>,5,6,7,8,0,<A>,15,16,17,18,19,20,101,<A>,9,0,<A>,0");
    print_lram(0,40);

}