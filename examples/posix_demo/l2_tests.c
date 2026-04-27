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

void clear_a_mem(void)
{
    for (int i = 0; i < 40; i++){
        A_MEM[i] = 0;
    }
}

void clear_b_mem(void)
{
    for (int i = 0; i < 40; i++){
        B_MEM[i] = 0;
    }
}

void fill_a_mem(void)
{
    a_save_e(0x10,0,NULL);
    a_save_e(0x11,8,NULL);
    a_save_e(0x12,16,NULL);
    a_save_e(0x13,24,NULL);
    a_save_e(0x14,32,NULL);
    a_save_e(0x15,40,NULL);
    a_save_e(0x16,48,NULL);
}

void fill_b_mem(void)
{
    b_save_e(0x60,0,NULL);
    b_save_e(0x61,8,NULL);
    b_save_e(0x62,16,NULL);
    b_save_e(0x63,24,NULL);
    b_save_e(0x64,32,NULL);
}

void print_a_mem(void)
{
    printf("A_MEM: ");
    for (int i = 0; i < 40; i++){
        printf("%lx,",A_MEM[i]);
    }
    puts("");
    return;
}

void print_b_mem(void)
{
    printf("B_MEM: ");
    for (int i = 0; i < 40; i++){
        printf("%lx,",B_MEM[i]);
    }
    puts("");
    return;
}

void l2_test11()
{
    cl_clear_mem_area(ma10,NULL);
    cl_clear_mem_area(ma12,NULL);
    hram_fill1();
    cl_save_mem_area(ma100,ma10,NULL);
    printf("1.1 EXPECTED: [100,<A>,0,1,2,3,4,0,<A>,0,0]\n");
    print_lram(0,11);
    printf("\n\n\n\n");
}

void l2_test12()
{
    cl_clear_mem_area(ma10,NULL);
    cl_clear_mem_area(ma12,NULL);
    hram_fill1();
    cl_save_mem_area(ma100,ma12,NULL);
    printf("1.2 EXPECTED: [100,<A>,0,1,2,0,0,0,0]\n");
    print_lram(120,129);
    printf("\n\n\n\n");
}

void l2_test13()
{
    hram_fill1();
    cl_int_t arr3[20] = {55,(cl_int_t)(LRAM + 4),55,55,55,0,(cl_int_t)(LRAM + 10),0,0,0,0}; //1.3
    cl_int_t *parr3 = arr3;
    lram_fill2(parr3,0,20);
    cl_save_mem_area(ma100,ma13,NULL);
    printf("1.3 EXPECTED: [55,<A>,55,55,55,100,<A>,0,1,2,3,0]\n");
    print_lram(0,14);
    printf("\n\n\n\n");
}

void l2_test14()
{
    hram_fill1();
    cl_int_t arr4[20] = {0,(cl_int_t)(LRAM + 5),0,0,0,0,55,(cl_int_t)(LRAM + 9),55,55,55,0,(cl_int_t)(LRAM + 9)}; //1.4
    cl_int_t *parr4 = arr4;
    lram_fill2(parr4,0,20);
    cl_save_mem_area(ma100,ma13,NULL);
    printf("1.4 EXPECTED: [100,<A>,0,1,2,3,55,<A>,55,55,55,0,<A>]\n");
    print_lram(0,14);
    printf("\n\n\n\n");
}

void l2_test15()
{
    hram_fill1();
    cl_int_t arr5[20] = {0,(cl_int_t)(LRAM + 3),0,0,55,(cl_int_t)(LRAM + 6),55,0,(cl_int_t)(LRAM + 10),0,0};
    cl_int_t *parr5 = arr5;
    lram_fill2(parr5,0,20);
    cl_save_mem_area(ma100,ma13,NULL);
    printf("1.5 EXPECTED: [100,<A>,0,1,55,<A>,55,100,<A>,2,3]\n");
    print_lram(0,14);
    printf("\n\n\n\n");
}

void l2_test16()
{

    // 1.6
    hram_fill1();
    cl_int_t arr6[20] = {
        50,(cl_int_t)(LRAM + 3),55,56,0,(cl_int_t)(LRAM + 7),0,0,51,(cl_int_t)(LRAM + 9),0,
        (cl_int_t)(LRAM + 12),0,52,(cl_int_t)(LRAM + 15),57,0,(cl_int_t)(LRAM + 99),0,0
    };
    cl_int_t *parr6 = arr6;
    lram_fill2(parr6,0,20);
    cl_save_mem_area(ma100,ma10,NULL);
    printf("1.6 EXPECTED: [50,<A>,55,56,100,<A>,0,1,51,<A>,100,<A>,2,52,<A>,57,100,<A>,3,4,5]\n");
    print_lram(0,23);
    printf("\n\n\n\n");

}

void l2_test17()
{

    hram_fill1();
    cl_int_t arr7[20] = {
        0,(cl_int_t)(LRAM + 4),0,0,0,50,(cl_int_t)(LRAM + 7),55,0,(cl_int_t)(LRAM + 13),0,0,0,0,51,
        (cl_int_t)(LRAM + 16),56,0,(cl_int_t)(LRAM + 20),0
    };
    cl_int_t *parr7 = arr7;
    lram_fill2(parr7,0,20);
    cl_save_mem_area(ma100,ma10,NULL);
    printf("1.7 EXPECTED: [100,<A>,0,1,2,50,<A>,55,100,<A>,3,4,0,<A>,51,<A>,56,0,<A>,0]\n");
    print_lram(0,20);
}

void l2_test18()
{

    hram_fill1();
    cl_int_t arr8[25] = {
        50,(cl_int_t)(LRAM + 4),55,56,57,0,(cl_int_t)(LRAM + 10),0,0,0,0,51,(cl_int_t)(LRAM + 13),
        58,0,(cl_int_t)(LRAM + 17),0,0,52,(cl_int_t)(LRAM + 19),0,(cl_int_t)(LRAM + 22),0,53,(cl_int_t)(LRAM + 24)
    };
    cl_int_t *parr8 = arr8;
    lram_fill2(parr8,0,25);
    cl_save_mem_area(ma100,ma10,NULL);
    printf("1.8 EXPECTED: [50,<A>,55,56,57,100,<A>,0,1,2,3,51,<A>,58,100,<A>,4,0,52,<A>,0,<A>,0,53,<A>]\n");
    print_lram(0,25);
}

void l2_test19()
{

    hram_fill1();
    cl_int_t arr9[10] = {50,(cl_int_t)(LRAM + 9)};
    cl_int_t *parr9 = arr9;
    lram_fill2(parr9,0,10);
    cl_save_mem_area(ma100,ma13,NULL);
    printf("1.9 EXPECTED: [50,<A>,0,0,0,0,0,0,0]\n");
    print_lram(0,10);
}

void l2_test21()
{

    hram_fill1();
    cl_int_t arr1[10] = {100,(cl_int_t)(LRAM + 6),0,1,2,3,4,0,(cl_int_t)(LRAM + 99)};
    cl_int_t *parr1 = arr1;
    lram_fill2(parr1,0,10);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("2.1 EXPECTED: [0,1,2,3,4]\n");
    print_hram(0,5);
    print_lram(0,10);
}

void l2_test22()
{
    printf("Empty test\n");
}

void l2_test23()
{
    hram_clear();
    cl_int_t arr3[25] = {
        0,(cl_int_t)(LRAM + 4),0,0,0,100,(cl_int_t)(LRAM + 11),
        100,101,102,103,104,50,
        (cl_int_t)(LRAM + 99),55,55,55
    };
    cl_int_t *parr3 = arr3;
    lram_fill2(parr3,0,25);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("2.3 EXPECTED: [100,101,102,103,104]\n");
    print_hram(0,5);
    print_lram(0,25);
}

void l2_test24()
{
    hram_clear();
    cl_int_t arr4[25] = {
        0,(cl_int_t)(LRAM + 4),0,0,0,100,(cl_int_t)(LRAM + 9),
        100,101,102,50,
        (cl_int_t)(LRAM + 100),55,55,55
    };
    cl_int_t *parr4 = arr4;
    lram_fill2(parr4,0,25);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("2.4 EXPECTED: [100,101,102,0,0]\n");
    print_hram(0,5);
    print_lram(0,25);
}

void l2_test25()
{
    cl_int_t arr5[27] = {
        100,(cl_int_t)(LRAM + 3),101,102,0,(cl_int_t)(LRAM + 7),0,66,50,
        (cl_int_t)(LRAM + 13),
        55,56,57,58,0,(cl_int_t)(LRAM + 20),
        66,66,66,66,66,
        100,(cl_int_t)(LRAM + 24),103,104,0,(cl_int_t)(LRAM + 99)
    };
    cl_int_t *parr5 = arr5;
    lram_fill2(parr5,0,27);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("2.5 EXPECTED: [101,102,103,104,0]\n");
    print_hram(0,5);
    print_lram(0,25);
}

void l2_test26()
{
    cl_int_t arr6[25] = {
        50,(cl_int_t)(LRAM + 2),55,100,(cl_int_t)(LRAM + 5),
        101,50,(cl_int_t)(LRAM + 9),55,56,0,
        (cl_int_t)(LRAM + 13),0,0,100,(cl_int_t)(LRAM + 17),
        102,103,0,(cl_int_t)(LRAM + 19),
        100,(cl_int_t)(LRAM + 22),
        104,50,(cl_int_t)(LRAM + 99)
    };
    cl_int_t *parr6 = arr6;
    lram_fill2(parr6,0,25);
    cl_load_mem_area(ma100,ma10,NULL);
    printf("2.6 EXPECTED: [101,102,103,104,0]\n");
    print_hram(0,5);
    print_lram(0,25);
}

void l2_test31()
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

void l2_test41()
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
}

void l2_test42()
{
    hram_clear();
    cl_clear_mem_area(ma10,NULL);
    cl_read_mem_area(ma100,ma10,NULL);
    printf("4.2 READ EXPECTED: [0,0,0,0,0]\n");
    print_hram(0,5);
    print_lram(0,10);
}

void l2_test43()
{
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

}

void l2_test44()
{
    cl_clear_mem_area(ma10,NULL);
    hram_fill1();
    cl_save_mem_area(ma104,ma10,NULL);
    cl_save_mem_area(ma102,ma10,NULL);
    cl_save_mem_area(ma105,ma10,NULL);
    cl_save_mem_area(ma103,ma10,NULL);
    printf("4.4 4xSAVE:\n");
    print_lram(0,30);
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

void l2_test51()
{
    cl_init();
    clear_a_mem();
    clear_b_mem();
    cl_clear_mem_area(ma150,NULL);
    fill_b_mem();
    cl_save_mem_area(ma151,ma150,NULL);
    printf("5.1 Expected: 0,0,0,0,0,0,0,0,0,0,aa,97,aa,30,aa,60,aa,61,aa,62,aa,63,aa,64,0,0,0,0,0,0,0 \n");
    print_a_mem();
}

void l2_test52()
{
    cl_init();
    clear_a_mem();
    clear_b_mem();
    cl_clear_mem_area(ma150,NULL);
    fill_b_mem();
    cl_save_mem_area(ma151,ma150,NULL);
    clear_b_mem();
    cl_load_mem_area(ma151,ma150,NULL);
    printf("5.2 Expected: 0,0,...,bb,bb,bb,bb,bb,60,61,62,63,64,bb,bb,bb,bb,bb,0,...\n");
    print_b_mem();

}

void l2_test53()
{
    cl_init();
    clear_a_mem();
    clear_b_mem();
    cl_clear_mem_area(ma151,NULL);
    fill_a_mem();
    cl_save_mem_area(ma150,ma151,NULL);
    printf("5.3 Expected: 0,0,0,...,bb,bb,bb,bb,bb,ID:96,ADDR:20,10,11,12,bb,bb,bb,bb,bb,0,...\n");
    print_b_mem();
}

void l2_test54()
{
    cl_init();
    clear_a_mem();
    clear_b_mem();
    cl_clear_mem_area(ma151,NULL);
    print_b_mem();
    fill_a_mem();
    cl_save_mem_area(ma150,ma151,NULL);
    clear_a_mem();
    print_b_mem();
    cl_load_mem_area(ma150,ma151,NULL);
    printf("5.4 Expected: 0,0,0,...,aa,10,aa,11,aa,12,0,0,0,0,..\n");
    print_a_mem();

}


void l2_test1()
{
    // l2_test11();
    // l2_test12();
    // l2_test13();
    // l2_test14();
    // l2_test15();
    // l2_test16();
    // l2_test17();
    // l2_test18();
    // l2_test19();
}

void l2_test2()
{
    // l2_test21();
    // l2_test22();
    // l2_test23();
    // l2_test24();
    // l2_test25();
    // l2_test26(); 
}

void l2_test3()
{
    // l2_test31();
}

void l2_test4()
{
    // l2_test41();
    // l2_test42();
    // l2_test43();
    l2_test44();
}

void l2_test5()
{
    // l2_test51();
    // l2_test52();
    // l2_test53();
    // l2_test54();
}