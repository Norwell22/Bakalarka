#include <stdio.h>
#include "../../platform/posix/context_lib_port.h"


/*
==== Testbench for L1 + L2 ====
1. cl_save_mem_area
    1.1 save data into empty array: SUCCESS
    1.2 save part of data into small empty array: SUCCESS
    1.3 save part of data into array occupied at the start: SUCCESS
    1.4 save part of data into array occupied at the end: SUCCESS
    1.5 save part of data into array occupied in the middle: SUCCESS
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

*/


    // cl_int_t test_dst_arr[20] = {55,(cl_int_t)(LRAM_MEM + 5),55,55,55,0,(cl_int_t)(LRAM_MEM + 10),0,0,0,0}; //1.3
    // cl_int_t test_dst_arr[20] = {0,(cl_int_t)(LRAM_MEM + 6),0,0,0,0,55,(cl_int_t)(LRAM_MEM + 10),55,55,55,0,(cl_int_t)(LRAM_MEM + 10)}; //1.4
    // cl_int_t test_dst_arr[20] = {0,(cl_int_t)(LRAM_MEM + 4),0,0,55,(cl_int_t)(LRAM_MEM + 7),55,0,(cl_int_t)(LRAM_MEM + 10),0,0}; //1.5
    // cl_int_t test_dst_arr[20] = {50,(cl_int_t)(LRAM_MEM + 4),55,56,0,(cl_int_t)(LRAM_MEM + 8),0,0,51,(cl_int_t)(LRAM_MEM + 10),0, //1.6
    //    (cl_int_t)(LRAM_MEM + 13),0,52,(cl_int_t)(LRAM_MEM + 16),57,0,(cl_int_t)(LRAM_MEM + 20),0,0}; //1.6
    // cl_int_t test_dst_arr[20] = {0,(cl_int_t)(LRAM_MEM + 5),0,0,0,50,(cl_int_t)(LRAM_MEM + 8),55,0,(cl_int_t)(LRAM_MEM + 14),0,0,0,0,51, // 1.7
    //    (cl_int_t)(LRAM_MEM + 17),56,0,(cl_int_t)(LRAM_MEM + 20),0}; // 1.7
    // cl_int_t test_dst_arr[25] = {50,(cl_int_t)(LRAM_MEM + 5),55,56,57,0,(cl_int_t)(LRAM_MEM + 11),0,0,0,0,51,(cl_int_t)(LRAM_MEM + 14), //1.8
    //     58,0,(cl_int_t)(LRAM_MEM + 18),0,0,52,(cl_int_t)(LRAM_MEM + 20),0,(cl_int_t)(LRAM_MEM + 23),0,53,(cl_int_t)(LRAM_MEM + 25)}; //1.8
    // cl_int_t test_dst_arr[10] = {50,(cl_int_t)(LRAM_MEM + 10)}; // 1.9
    //cl_int_t test_dst_arr[25] = {0,(cl_int_t)(LRAM_MEM + 5),0,0,0,100,(cl_int_t)(LRAM_MEM + 12),100,101,102,103,104,50, // 2.3
    //  (cl_int_t)(LRAM_MEM + 20),55,55,55}; // 2.3
    // cl_int_t test_dst_arr[25] = {0,(cl_int_t)(LRAM_MEM + 5),0,0,0,100,(cl_int_t)(LRAM_MEM + 10),100,101,102,50, // 2.4
    // (cl_int_t)(LRAM_MEM + 25),55,55,55}; // 2.4

    // cl_int_t test_dst_arr[25] = {100,(cl_int_t)(LRAM_MEM + 4),101,102,0,(cl_int_t)(LRAM_MEM + 8),0,66,50,(cl_int_t)(LRAM_MEM + 14), // 2.5
    //  55,56,57,58,0,(cl_int_t)(LRAM_MEM + 21), 66,66,66,66,66,100,(cl_int_t)(LRAM_MEM + 25),103,104}; // 2.5
    // cl_int_t test_dst_arr[25] = {50,(cl_int_t)(LRAM_MEM + 3),55,100,(cl_int_t)(LRAM_MEM + 6), 101,50,(cl_int_t)(LRAM_MEM + 10),55,56,0, // 2.6
    //      (cl_int_t)(LRAM_MEM + 14),0,0,100,(cl_int_t)(LRAM_MEM + 18),102,103,0,(cl_int_t)(LRAM_MEM + 20),100,(cl_int_t)(LRAM_MEM + 23), // 2.6
    //      104,50,(cl_int_t)(LRAM_MEM + 25)}; // 2.6
    

    // write data to less protected parts of memory(HRAM)
    cl_int_t arr100[] = {1,2,3,4,5};
    for (i = 0; i < 5; i++){
        HRAM_MEM[i] = arr100[i];
    }

    cl_int_t arr101[] = {11,12,13,14,15};
    for (i = 0; i < 5; i++){
        HRAM_MEM[i + 10] = arr101[i];
    }

    cl_int_t arr102[] = {21,22,23,24};
    for (i = 0; i < 4; i++){
        HRAM_MEM[i + 20] = arr102[i];
    }
    
    cl_int_t arr103[] = {31,32,33};
    for (i = 0; i < 3; i++){
        HRAM_MEM[i + 30] = arr103[i];
    }

    // prepare for sleep : save context

    cl_clear_mem_area(ma1,RAM_WRITE,NULL);

    cl_save_mem_area(ma102,ma1,RAM_WRITE,NULL);
    cl_save_mem_area(ma100,ma1,RAM_WRITE,NULL);
    cl_save_mem_area(ma103,ma1,RAM_WRITE,NULL);
    cl_save_mem_area(ma101,ma1,RAM_WRITE,NULL);
    printf("ma1:  ");
    for (i = 0; i < 40; i++){
        printf("%ld,  ",LRAM_MEM[i]);
    }
    puts("");


    for (i = 0; i < 1024; i++){
        HRAM_MEM[i] = 0;
    }

    cl_load_mem_area(ma103,ma1,RAM_WRITE,NULL);
    cl_load_mem_area(ma100,ma1,RAM_WRITE,NULL);
    cl_read_mem_area(ma101,ma1,RAM_WRITE,NULL);
    cl_load_mem_area(ma100,ma1,RAM_WRITE,NULL);
    for (i = 0; i < 40; i++){
        printf("%ld,  ",LRAM_MEM[i]);
    }
    puts("");

    cl_save_mem_area(ma100,ma1,RAM_WRITE,NULL);
    cl_save_mem_area(ma103,ma1,RAM_WRITE,NULL);
    cl_save_mem_area(ma103,ma1,RAM_WRITE,NULL);
    cl_load_mem_area(ma103,ma1,RAM_WRITE,NULL);

    for (i = 0; i < 40; i++){
        printf("%ld,  ",LRAM_MEM[i]);
    }
    puts("");

    // simulate sleep: erase lesser protected areas

    for (i = 0; i < 1024; i++){
        HRAM_MEM[i] = 0;
    }

    // wakeup : retrieve context
    
    cl_load_mem_area(ma100,ma1,RAM_WRITE,NULL);
    cl_save_mem_area(ma100,ma1,RAM_WRITE,NULL);
    for (i = 0; i < 1024; i++){
        HRAM_MEM[i] = 0;
    }
    cl_load_mem_area(ma100,ma1,RAM_WRITE,NULL);


    printf("ma100:  ");
    for (i = 0; i < 5; i++){
        printf("%ld,  ",HRAM_MEM[i]);
    }
    puts("");

    printf("ma101:  ");
    for (i = 0; i < 5; i++){
        printf("%ld,  ",HRAM_MEM[i + 10]);
    }
    puts("");

    printf("ma1:  ");
    for (i = 0; i < 40; i++){
        printf("%ld,  ",LRAM_MEM[i]);
    }
    puts("");


/* ======= Tests for L3
    cl_protect_memory(1);
    cl_protect_memory(30);
    cl_protect_memory(31);
    cl_protect_memory(32);
    cl_protect_memory(62);
    cl_protect_memory(63);
    cl_protect_memory(64);
    cl_protect_memory(100);
    cl_protect_memory(101);
    cl_protect_memory(102);
    cl_protect_memory(200);
    cl_unprotect_memory(1);
    cl_unprotect_memory(31);
    cl_unprotect_memory(63);
    cl_unprotect_memory(60);
    cl_unprotect_memory(100);
    for (i = 0; i < 4; i++){
        print_bits_uint64(CL_PROTECTED_MEM[i]);
    }

*/
