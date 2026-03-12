/*! 
 * \file      l2_public.c
 * \brief     Part of functions implementing second library layer
 * \details   
 * Main functions for saving and loading memory areas.
 * Dependencies:
 * - "../../include/main/l1.h"
 * - "../../include/main/l2.h"
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \todo Merge with \c l2_private.c
 * \todo Implement \a peripheral functions
 */
#include "../../include/main/l2.h"
#include "../../include/main/l1.h"

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


cl_int_t cl_save_peripheral(Cl_peripheral_area_t src_area, Cl_peripheral_area_t dst_area, enum Bare_save_type save_type, void *custom_d)
{

}

cl_int_t cl_load_peripheral(Cl_peripheral_area_t dst_area, Cl_peripheral_area_t src_area, enum Bare_save_type save_type, void *custom_d)
{

}

cl_int_t cl_read_peripheral(Cl_peripheral_area_t dst_area, Cl_peripheral_area_t src_area, enum Bare_save_type save_type, void *custom_d)
{

}
