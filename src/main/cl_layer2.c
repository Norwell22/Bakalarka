/*! 
 * \file      cl_layer2.c
 * \brief     Functions implementing second library layer
 * \details   
 * Main functions for saving and loading memory areas.
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \todo Merge with \c l2_private.c
 */
#include "../../include/main/cl_layer2.h"
#include "../../include/main/cl_layer2_priv.h"
#include "../../include/main/cl_layer1.h"

cl_int_t cl_clear_mem_area(Cl_memory_area_t area, enum Bare_save_type clear_type, void *custom_d)
{
    cl_save_f_t save_f = sel_save_f(clear_type);
    if (area.end_addr < area.start_addr){
        printf("ERROR:clear_mem_area: ending address is smaller than start "
                "address. Fix area definition ");
        return 1;
    }
    cl_addr_t current_addr = area.start_addr;
    while( current_addr != area.end_addr){
        // fill whole area with zeroes
        cl_raw_save_e(0x0,current_addr,custom_d);
        current_addr += 1;
    }
    // second element should be end address
    save_f((cl_int_t)area.end_addr, area.start_addr + 1,custom_d);
    printf("INFO\tclear_mem_area\tArea %ld set to [0,<end_addr>,0,0...]\n\n\n",area.id);
}

cl_int_t cl_save_mem_area(Cl_memory_area_t src_area, Cl_memory_area_t dst_area , enum Bare_save_type save_type, void *custom_d)
{
    printf("INFO\tsave_mem_area\tContext saving from area %ld to %ld started\n",src_area.id,dst_area.id);
    cl_save_f_t save_f = sel_save_f(save_type); // choose low-level technique for storing data
    cl_load_f_t load_f = sel_load_f(save_type); // choose low-level technique for loading data

    cl_addr_t target_addr = dst_area.start_addr; // pointer to area where data are to be stored
    cl_addr_t source_addr = src_area.start_addr; // pointer to area with source data

    cl_int_t cur_id = 0; // id of current block
    cl_int_t p_next_block_start;
    cl_addr_t next_block_start = 0; // address that marks end of current data block
    cl_int_t free_space; // free space from start to end of block
    cl_int_t saved_elements = 0; // number of data elements saved in current iteration

    while(target_addr < dst_area.end_addr){ // end when reached end of destination area
        // one iteration processes one block
        // start by loading current block metadata
        load_f(&cur_id, target_addr,custom_d);
        load_f(&p_next_block_start,target_addr + 1, custom_d);
        next_block_start = (cl_addr_t)p_next_block_start;
        printf("DEBUG\tsave_mem_area\tCurrent block: ID-%ld NEXT BLOCK-%ld\n",cur_id, (cl_int_t)next_block_start);
        // after that, either load data into block or skip block
        if (cur_id){ // this marks valid data block
            target_addr = next_block_start;
        }
        else{ // non-valid block reached: can be filled untill cur_block_end
            free_space = next_block_start - target_addr - 2;
            printf("DEBUG\tcl_save_mem\tfree space:%ld\n",free_space);

            //here, actual saving of data happens. number of saved elements are returned
            // based on saved_elements, program can determine if all data were written and where next block can begin
            saved_elements = fill_block(save_f, source_addr, src_area.end_addr, target_addr + 2, next_block_start,custom_d);
            printf("DEBUG\tcl_save_mem\tsaved elements:%ld\n",saved_elements);
            source_addr += saved_elements; // marks how many elements from source address were written
            switch(free_space - saved_elements){ // at the end of current block, new empty block can emerge
                case 0: // no new empty block
                    break;
                case 1: // one empty space: merged to current block
                    printf("INFO\tcl_save_mem\tOne empty element added to end of existing block\n");
                    saved_elements++;
                    break;
                default: // new empty block: gets filled with [0,<original_next_block_addr>]
                    printf("DEBUG\tcl_save_mem\tNew empty block created after the one currently created\n");

                    save_f(0x0,target_addr + 2 + saved_elements, custom_d);
                    save_f((cl_int_t)next_block_start, target_addr + 2 + saved_elements + 1,custom_d);
            }

            save_f(src_area.id, target_addr,custom_d);
            save_f( (cl_int_t)(target_addr + 2 + saved_elements), target_addr + 1, custom_d);
            if (source_addr == src_area.end_addr){
                printf("INFO\tcl_save_mem\tArea writing successfull\n\n\n");
                return 0;
            }
            target_addr += 2 + saved_elements;
        }  
    }
    printf("ERROR\tsave_mem_area\tFrom area %ld, %ld elements was not saved "
            "into %ld\n\n\n",src_area.id,src_area.end_addr - source_addr,dst_area.id);
    return 1;
}

cl_int_t cl_read_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type,void *custom_d)
{
    read_load_mem_area(dst_area, src_area, save_type, custom_d,0);
}

cl_int_t cl_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type,void *custom_d)
{
    read_load_mem_area(dst_area, src_area, save_type, custom_d,1);
}

// function generated by ChatGPT
cl_int_t cl_save_peripheral(const Cl_peripheral_area_t *src_area,
                                 Cl_memory_area_t dst_area,
                                 enum Bare_save_type save_type,
                                 void *custom_d)
{
    printf("INFO\tsave_peripheral_area\tContext saving from peripheral area %ld to %ld started\n",
           src_area->id, dst_area.id);

    cl_save_f_t save_f = sel_save_f(save_type);
    cl_load_f_t load_f = sel_load_f(save_type);

    cl_addr_t target_addr = dst_area.start_addr;

    cl_int_t source_index = 0;          // index in addresses[]
    cl_int_t cur_id = 0;
    cl_int_t p_next_block_start;
    cl_addr_t next_block_start = 0;

    cl_int_t free_space;
    cl_int_t saved_elements = 0;
    printf("MA201:%p, SOURCE AREA: %p\n",&ma201,src_area);
    printf("ID: %ld\n",src_area->id);

    cl_int_t i;
    puts("SPI:");
    for (i = 0; i < 6; i++){
        printf("%ld, ",*src_area->addresses[i]);
    }
    puts("");

    while (target_addr < dst_area.end_addr) {

        load_f(&cur_id, target_addr, custom_d);
        load_f(&p_next_block_start, target_addr + 1, custom_d);
        next_block_start = (cl_addr_t)p_next_block_start;

        printf("DEBUG\tsave_peripheral_area\tCurrent block: ID-%ld NEXT BLOCK-%ld\n",
               cur_id, (cl_int_t)next_block_start);

        if (cur_id) {               // valid block → skip
            target_addr = next_block_start;
        }
        else {                      // empty block → fill
            free_space = next_block_start - target_addr - 2;
            printf("DEBUG\tcl_save_peripheral\tfree space:%ld\n", free_space);

            saved_elements = 0;

            while (saved_elements < free_space &&
                   source_index < src_area->addr_num) {

                cl_int_t val;
                load_f(&val, src_area->addresses[source_index], custom_d);

                save_f(val,
                       target_addr + 2 + saved_elements,
                       custom_d);

                saved_elements++;
                source_index++;
            }

            printf("DEBUG\tcl_save_peripheral\tsaved elements:%ld\n", saved_elements);

            switch (free_space - saved_elements) {
                case 0:
                    break;

                case 1:
                    printf("INFO\tcl_save_peripheral\tOne empty element added to end of existing block\n");
                    saved_elements++;
                    break;

                default:
                    printf("DEBUG\tcl_save_peripheral\tNew empty block created after the one currently created\n");

                    save_f(0x0, target_addr + 2 + saved_elements, custom_d);
                    save_f((cl_int_t)next_block_start,
                           target_addr + 2 + saved_elements + 1,
                           custom_d);
            }

            save_f(src_area->id, target_addr, custom_d);
            save_f((cl_int_t)(target_addr + 2 + saved_elements),
                   target_addr + 1,
                   custom_d);

            if (source_index == src_area->addr_num) {
                printf("INFO\tcl_save_peripheral\tArea writing successful\n\n\n");
                return 0;
            }

            target_addr += 2 + saved_elements;
        }
    }

    printf("ERROR\tsave_peripheral_area\tFrom area %ld, %ld elements were not saved into %ld\n\n\n",
           src_area->id,
           src_area->addr_num - source_index,
           dst_area.id);

    return 1;
}

cl_int_t cl_load_peripheral(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type, void *custom_d)
{
    read_load_peripheral_area(dst_area, src_area, save_type, custom_d,1);
}

cl_int_t cl_read_peripheral(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type, void *custom_d)
{

    read_load_peripheral_area(dst_area, src_area, save_type, custom_d,0);
}

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

    cl_int_t block_id, i_next_block_addr, loaded_e;
    cl_int_t id = dst_area.id;
    cl_addr_t next_block_addr;
    cl_addr_t block_addr = src_area.start_addr;
    cl_addr_t dst_addr = dst_area.start_addr;

    // iterate once for every block 
    while (block_addr < src_area.end_addr){ // if end of source area is reached, some elements could not be stored
        load_f(&block_id,block_addr,custom_d); // load id of current block
        load_f(&i_next_block_addr, block_addr + 1,custom_d); //! load end of the block address 
        next_block_addr = (cl_addr_t)i_next_block_addr;
        printf("DEBUG\tload_mem_area\tCurrent block: ID-%ld Next block address-%ld\n",block_id,(cl_int_t)next_block_addr);
        if(block_id == id){ // matching id, read data in this block
            dst_addr += load_block(load_f, dst_addr,dst_area.end_addr,block_addr + 2,next_block_addr,custom_d);
            // mark block as invalid (for load, not for read functions)
            if (erase){
                save_f(0x0,block_addr,custom_d);
            }
            if (dst_addr == dst_area.end_addr){ // all elements were loaded
                puts("INFO\tload_mem_area\tSuccessfully loaded all elements\n\n\n");
                return 0;
            }
        }
        else{ // not matching id, simply skip to next block
            block_addr = next_block_addr;
        }
    }
    printf("ERROR\tcl_load_mem_area\t%ld elements from area %ld to %ld were not loaded\n\n\n",
            dst_area.end_addr - dst_addr,src_area.id,dst_area.id);
}

// generated by chat gpt
cl_int_t read_load_peripheral_area(const Cl_peripheral_area_t *dst_area,
                                   Cl_memory_area_t src_area,
                                   enum Bare_save_type save_type,
                                   void *custom_d,
                                   uint8_t erase)
{
    printf("INFO\tload_mem_area\tContext loading from area %ld to peripheral area %ld started\n",
           src_area.id, dst_area->id);

    cl_save_f_t save_f = sel_save_f(save_type);
    cl_load_f_t load_f = sel_load_f(save_type);

    cl_int_t block_id, i_next_block_addr;
    cl_int_t id = dst_area->id;

    cl_addr_t next_block_addr;
    cl_addr_t block_addr = src_area.start_addr;

    cl_int_t loaded = 0;

    // iterate once for every block
    while (block_addr < src_area.end_addr) {

        load_f(&block_id, block_addr, custom_d);
        load_f(&i_next_block_addr, block_addr + 1, custom_d);

        next_block_addr = (cl_addr_t)i_next_block_addr;

        printf("DEBUG\tload_mem_area\tCurrent block: ID-%ld Next block address-%ld\n",
               block_id, (cl_int_t)next_block_addr);

        if (block_id == id) {

            cl_addr_t data_addr = block_addr + 2;

            while (data_addr < next_block_addr && loaded < dst_area->addr_num) {

                cl_int_t value;
                load_f(&value, data_addr, custom_d);

                save_f(value, dst_area->addresses[loaded], custom_d);

                loaded++;
                data_addr++;
            }

            if (erase) {
                save_f(0x0, block_addr, custom_d);
            }

            if (loaded == dst_area->addr_num) {
                puts("INFO\tload_mem_area\tSuccessfully loaded all elements\n\n\n");
                return 0;
            }

            block_addr = next_block_addr;
        }
        else {
            block_addr = next_block_addr;
        }
    }

    printf("ERROR\tcl_load_mem_area\t%ld peripheral elements from area %ld were not loaded\n\n\n",
           dst_area->addr_num - loaded, src_area.id);

    return 1;
}