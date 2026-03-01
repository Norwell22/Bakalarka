
#include "../../include/main/context_manager.h"
#include "../../include/main/l2.h"
#include "../../include/main/l1.h"
// #include "../../platform/posix/context_lib_port.h"
#include <stdio.h> //this would be better if wasn't here
#include <stdbool.h> //this would be better if it wasn't here



cl_save_f_t sel_save_f(enum Bare_save_type save_type)
{
    switch (save_type){
        case RAM_WRITE:
            return cl_raw_save_e;
        case SEND:
            return cl_raw_send_e;
        case CUSTOM_SEND:
            return cl_raw_custom_send_e;
    }
}

cl_load_f_t sel_load_f(enum Bare_save_type save_type)
{
    switch (save_type){
        case RAM_WRITE:
            return cl_raw_load_e;
        case SEND:
            return cl_raw_rcv_e;
        case CUSTOM_SEND:
            return cl_raw_custom_rcv_e;
    }
}



cl_int_t fill_block(cl_save_f_t save_f,cl_addr_t start_src_a, cl_addr_t end_src_a, cl_addr_t start_dst_a, cl_addr_t end_dst_a,void *custom_d)
{
    cl_int_t loaded_blocks = 0;
    while(1){
        if (start_src_a >= end_src_a){ // loading ended successfully
            puts("DEBUG\tfill_block\tAll elements were saved\n");
            return loaded_blocks;
        }
        if (start_dst_a >= end_dst_a){ // some data were left not loaded
            puts("DEBUG\tfill block\tSome elements were NOT saved\n");
            return loaded_blocks;
        }
        save_f(*start_src_a,start_dst_a,custom_d);
        start_src_a++;
        start_dst_a++;
        loaded_blocks++;
    }
}


cl_int_t load_block(cl_load_f_t load_f,cl_addr_t start_src_a, cl_addr_t end_src_a, cl_addr_t start_dst_a, cl_addr_t end_dst_a,void *custom_d)
{
    cl_int_t loaded_blocks = 0;
    while(1){
        if (start_src_a >= end_src_a){ // loading ended successfully
            printf("DEBUG\tload_block\tAll elements were loaded successfully\n");
            return loaded_blocks;
        }
        if (start_dst_a >= end_dst_a){ // some data were left not loaded
            printf("DEBUG\tload_block\tSome elements were NOT loaded\n");
            return loaded_blocks;
        }
        // printf("putting %ld where %ld was before\n",*start_dst_a,*start_src_a);
        load_f(start_src_a,start_dst_a,custom_d);
        start_src_a++;
        start_dst_a++;
        loaded_blocks++;
    }
}


cl_int_t read_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type,void *custom_d,uint8_t erase)
{
    printf("INFO\tload_mem_area\tContext loading from area %ld to %ld started\n",src_area.id,dst_area.id);
    cl_save_f_t save_f = sel_save_f(save_type); // choose low-level technique for storing data
    cl_load_f_t load_f = sel_load_f(save_type); // choose low-level technique for loading data

    cl_int_t id = dst_area.id;
    cl_int_t block_id;
    cl_addr_t block_addr = src_area.start_addr;
    cl_addr_t next_block_addr;
    cl_int_t i_next_block_addr;
    cl_addr_t dst_addr = dst_area.start_addr;
    cl_int_t loaded_e;
    while (block_addr < src_area.end_addr){
        load_f(&block_id,block_addr,custom_d);
        load_f(&i_next_block_addr, block_addr + 1,custom_d);
        next_block_addr = (cl_addr_t)i_next_block_addr;
        printf("DEBUG\tload_mem_area\tCurrent block: ID-%ld Next block address-%ld\n",block_id,(cl_int_t)next_block_addr);
        if(block_id == id){
            //dst_addr += load_block(load_f,block_addr + 2,next_block_addr,dst_addr,dst_area.end_addr,custom_d);
            dst_addr += load_block(load_f, dst_addr,dst_area.end_addr,block_addr + 2,next_block_addr,custom_d);
            //loaded_e += load_block(load_f,block_addr + 2,next_block_addr,dst_addr,dst_area.end_addr,custom_d);
            if (erase){
                save_f(0x0,block_addr,custom_d);
            }
            if (dst_addr == dst_area.end_addr){
                puts("INFO\tload_mem_area\tSuccessfully loaded all elements\n\n\n");
                return 0;
            }
        }
        else{
            block_addr = next_block_addr;
        }
    }
    printf("ERROR\tcl_load_mem_area\t%ld elements from area %ld to %ld were not loaded\n\n\n",
            dst_area.end_addr - dst_addr,src_area.id,dst_area.id);
}