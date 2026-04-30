/*! 
 * \file      cl_layer2.c
 * \brief     Functions implementing second library layer
 * \details   
 * Main functions for saving and loading memory areas.
 * \author    Michal Zidzik
 * \date      02.03.2026
 */
#include "cl_layer2.h"
#include "cl_layer2_priv.h"
#include "cl_layer1.h"
#include "ulog.h"
#include "context_lib_port.h"

   
bool cl_clear_mem_area(Cl_memory_area_t area, void *custom_d)
{
    ULOG_INFO("cl_clear_mem_area:\tclear_mem_area started");
    cl_save_f_t save_f = sel_save_f(area.save_type);
    cl_addr_t current_addr = area.start_addr;
    while( current_addr <= area.end_addr){
        //ULOG_DEBUG("cl_clear_mem_area:\tin the cycle with address %ld",current_addr);
        // fill whole area with zeroes
        save_f(0x0,current_addr,custom_d);
        //a_save_e(0x0,current_addr,custom_d);
        current_addr += 1;
    }
    puts("AFTER CYCLE");
    save_f((cl_int_t)area.end_addr, area.start_addr + 1,custom_d);
    ULOG_INFO("cl_clear_mem_area:\tArea cleared\n\n\n");
    return true;
}

bool cl_save_mem_area(Cl_memory_area_t src_area, Cl_memory_area_t dst_area , void *custom_d)
{
    ULOG_INFO("cl_save_mem_area:\tContext saving started");
    cl_save_f_t s_save_f = sel_save_f(src_area.save_type); // choose low-level technique for storing data
    cl_load_f_t s_load_f = sel_load_f(src_area.save_type); // choose low-level technique for loading data
    cl_save_f_t d_save_f = sel_save_f(dst_area.save_type); // choose low-level technique for storing data
    cl_load_f_t d_load_f = sel_load_f(dst_area.save_type); // choose low-level technique for loading data

    cl_addr_t dst_addr = dst_area.start_addr; // pointer to area where data are to be stored
    cl_addr_t source_addr = src_area.start_addr; // pointer to area with source data

    cl_int_t cur_id = 0; // id of current block
    cl_int_t p_block_end;
    cl_addr_t block_end = 0; // address that marks end of current data block
    cl_int_t free_space; // free space from start to end of block
    cl_int_t saved_elements = 0; // number of data elements saved in current iteration

    while(dst_addr <= dst_area.end_addr){ // end when reached end of destination area
        // one iteration processes one block
        // start by loading current block metadata
        d_load_f(&cur_id, dst_addr,custom_d);
        d_load_f(&p_block_end,dst_addr + 1, custom_d);
        block_end = (cl_addr_t)p_block_end;
        ULOG_DEBUG("cl_save_mem_area:\tCurrent block: ID:%ld BLOCK END:%ld",cur_id, (cl_int_t)block_end);
        
        // after that, either load data into block or skip block
        if (cur_id && cur_id != src_area.id){ // this marks valid data block
            dst_addr = block_end + 1;
        }
        else{ // non-valid block reached: can be filled untill cur_block_end
            free_space = block_end - dst_addr - HEAD_LENGTH + 1;
            ULOG_DEBUG("cl_save_mem_area:\tfree space:%ld",free_space);

            //here, actual saving of data happens. number of saved elements are returned
            // based on saved_elements, program can determine if all data were written and where next block can begin
            saved_elements = fill_block(s_load_f, d_save_f, source_addr, src_area.end_addr, dst_addr + HEAD_LENGTH, block_end,custom_d);
            ULOG_DEBUG("cl_save_mem_area:\tsaved elements:%ld",saved_elements);
            source_addr += saved_elements; // marks how many elements from source address were written
            switch(free_space - saved_elements){ // at the end of current block, new empty block can emerge
                case 0: // no new empty block
                    break;
                case 1: // one empty space: merged to current block
                    ULOG_INFO("cl_save_mem_area:\tOne empty element added to end of existing block");
                    saved_elements++;
                    break;
                default: // new empty block: gets filled with [0,<original_next_block_addr>]
                    ULOG_DEBUG("cl_save_mem_area:\tjNew empty block created after the one currently created");

                    d_save_f(0x0,dst_addr + HEAD_LENGTH + saved_elements, custom_d);
                    d_save_f((cl_int_t)block_end, dst_addr + HEAD_LENGTH + saved_elements + 1,custom_d);
            }
            d_save_f(src_area.id, dst_addr,custom_d);
            d_save_f( (cl_int_t)(dst_addr + HEAD_LENGTH + saved_elements - 1), dst_addr + 1, custom_d);
            if (source_addr >= src_area.end_addr){
                ULOG_INFO("cl_save_mem_area:\tArea writing successful");
                return true;
            }
            dst_addr += HEAD_LENGTH + saved_elements;
        }  
    }
    ULOG_ERROR("cl_save_mem_area:\tFailed to save all elements");
    return false;
}

bool cl_save_peripheral(const Cl_peripheral_area_t *src_area, Cl_memory_area_t dst_area , void *custom_d)
{
    ULOG_INFO("cl_save_mem_area:\tContext saving started");
    cl_save_f_t s_save_f = sel_save_f(src_area->save_type); // choose low-level technique for storing data
    cl_load_f_t s_load_f = sel_load_f(src_area->save_type); // choose low-level technique for loading data
    cl_save_f_t d_save_f = sel_save_f(dst_area.save_type); // choose low-level technique for storing data
    cl_load_f_t d_load_f = sel_load_f(dst_area.save_type); // choose low-level technique for loading data

    cl_addr_t dst_addr = dst_area.start_addr; // pointer to area where data are to be stored
    cl_int_t src_i = 0;

    cl_int_t cur_id = 0; // id of current block
    cl_int_t p_next_block_start;
    cl_addr_t next_block_start = 0; // address that marks end of current data block
    cl_int_t free_space; // free space from start to end of block
    cl_int_t saved_elements = 0; // number of data elements saved in current iteration

    while(dst_addr <= dst_area.end_addr){ // end when reached end of destination area
        // one iteration processes one block
        // start by loading current block metadata
        d_load_f(&cur_id, dst_addr,custom_d);
        d_load_f(&p_next_block_start,dst_addr + 1, custom_d);
        next_block_start = (cl_addr_t)p_next_block_start;
        ULOG_DEBUG("cl_save_mem_area:\tCurrent block: ID:%ld NEXT BLOCK:%ld",cur_id, (cl_int_t)next_block_start);
        
        // after that, either load data into block or skip block
        if (cur_id && cur_id != src_area->id){ // this marks valid data block
            dst_addr = next_block_start;
        }
        else{ // non-valid block reached: can be filled untill cur_block_end
            free_space = next_block_start - dst_addr - HEAD_LENGTH;
            ULOG_DEBUG("cl_save_mem_area:\tfree space:%ld",free_space);

            //here, actual saving of data happens. number of saved elements are returned
            // based on saved_elements, program can determine if all data were written and where next block can begin
            saved_elements = save_block_peripheral(src_area, s_load_f, d_save_f, src_i, src_area->addr_num, dst_addr + HEAD_LENGTH, next_block_start,custom_d);
            ULOG_DEBUG("cl_save_mem_area:\tsaved elements:%ld",saved_elements);
            src_i += saved_elements; // marks how many elements from source address were written
            switch(free_space - saved_elements){ // at the end of current block, new empty block can emerge
                case 0: // no new empty block
                    break;
                case 1: // one empty space: merged to current block
                    ULOG_INFO("cl_save_mem_area:\tOne empty element added to end of existing block");
                    saved_elements++;
                    break;
                default: // new empty block: gets filled with [0,<original_next_block_addr>]
                    ULOG_DEBUG("cl_save_mem_area:\tjNew empty block created after the one currently created");

                    d_save_f(0x0,dst_addr + HEAD_LENGTH + saved_elements, custom_d);
                    d_save_f((cl_int_t)next_block_start, dst_addr + HEAD_LENGTH + saved_elements + 1,custom_d);
            }

            d_save_f(src_area->id, dst_addr,custom_d);
            d_save_f( (cl_int_t)(dst_addr + HEAD_LENGTH + saved_elements), dst_addr + 1, custom_d);
            if (src_i == src_area->addr_num){
                ULOG_INFO("cl_save_mem_area:\tArea writing successful");
                return true;
            }
            dst_addr += HEAD_LENGTH + saved_elements;
        }  
    }
    ULOG_ERROR("cl_save_mem_area:\tFailed to save all elements");
    return false;
}

bool cl_read_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area,void *custom_d)
{
    return read_load_mem_area(dst_area, src_area, custom_d,0);
}

bool cl_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area,void *custom_d)
{
    return read_load_mem_area(dst_area, src_area, custom_d,1);
}

 bool cl_load_peripheral(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, void *custom_d)
{
    return read_load_peripheral_area(dst_area, src_area, custom_d,true);
}

bool cl_read_peripheral(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area, void *custom_d)
{

    return read_load_peripheral_area(dst_area, src_area, custom_d,false);
}

// todo: move this to layer 1 functions?
// layer 1 could absolutely be reworked to some more user-friendly way
cl_save_f_t sel_save_f(enum Bare_save_type save_type)
{
    switch (save_type){
        case CL_CPU:
            return cl_raw_save_e;
        case CL_DEVICE:
            return cl_raw_send_e;
        #ifdef CL_PLATFORM_POSIX
        case CL_A:
            return a_save_e;
        #endif
        #ifdef CL_PLATFORM_POSIX
        case CL_B:
            return b_save_e;
        #endif
        #ifdef CL_PLATFORM_FRDM
        case CL_MCUXPRESSO_GPIO:
        	return cl_sdk_save_gpio_e;
        #endif
        #ifdef CL_PLATFORM_FRDM
        case CL_EEPROM:
        	return cl_eeprom_save_e;
        #endif
        #ifdef CL_PLATFORM_PICO
        case CL_EEPROM_PICO:
            return cl_eeprom_pico_save_e;
        #endif

        //add more cases here
        default:
            return NULL;
    }
}

cl_load_f_t sel_load_f(enum Bare_save_type save_type)
{
    switch (save_type){
        case CL_CPU:
            return cl_raw_load_e;
        case CL_DEVICE:
            return cl_raw_rcv_e;
        #ifdef CL_PLATFORM_POSIX
        case CL_A:
            return a_load_e;
        #endif
        #ifdef CL_PLATFORM_POSIX
        case CL_B:
            return b_load_e;
        #endif
        #ifdef CL_PLATFORM_FRDM
        case CL_MCUXPRESSO_GPIO:
        	return cl_sdk_load_gpio_e;
        #endif
        #ifdef CL_PLATFORM_FRDM
        case CL_EEPROM:
        	return cl_eeprom_load_e;
        #endif
        #ifdef CL_PLATFORM_PICO:
            case CL_EEPROM_PICO:
                return cl_eeprom_pico_load_e;
        #endif

        //add more cases here
        default:
            return NULL;
    }
}

cl_int_t fill_block(cl_load_f_t s_load_f,cl_save_f_t d_save_f, cl_addr_t start_src_a, cl_addr_t end_src_a, cl_addr_t start_dst_a, cl_addr_t end_dst_a,void *custom_d)
{
    cl_int_t loaded_blocks = 0;
    cl_int_t loaded_data;
    while(1){
        if (start_src_a > end_src_a){ // loading ended successfully
            ULOG_DEBUG("cl_fill_block:\tAll elements were saved");
            return loaded_blocks;
        }
        if (start_dst_a > end_dst_a){ // some data were left not loaded
            ULOG_DEBUG("cl_fill_block:\tSome elements were NOT saved");
            return loaded_blocks;
        }
        s_load_f(&loaded_data,start_src_a,custom_d);
        ULOG_DEBUG("cl_fill_block:\tLOADED ELEMENT: %lx",loaded_data);
        d_save_f(loaded_data,start_dst_a,custom_d);
        start_src_a++;
        start_dst_a++;
        loaded_blocks++;
    }
}

cl_int_t save_block_peripheral(Cl_peripheral_area_t *src_a, cl_load_f_t s_load_f,cl_save_f_t d_save_f, cl_int_t src_i, cl_int_t max_i, 
    cl_addr_t start_dst_a, cl_addr_t end_dst_a, void *custom_d)
{
    cl_int_t loaded_blocks = 0;
    cl_int_t loaded_data;
    while(1){
        if (src_i >= max_i){ // loading ended successfully
            ULOG_DEBUG("save_block_peripheral:\tAll elements were saved");
            return loaded_blocks;
        }
        if (start_dst_a >= end_dst_a){ // some data were left not loaded
            ULOG_DEBUG("save_block_peripheral:\tSome elements were NOT saved");
            return loaded_blocks;
        }
        s_load_f(&loaded_data,src_a->addresses[src_i],custom_d);
        ULOG_DEBUG("save_block_peripheral:\tLOADED ELEMENT: %lx",loaded_data);
        d_save_f(loaded_data,start_dst_a,custom_d);
        src_i++;
        start_dst_a++;
        loaded_blocks++;
    }
}

cl_int_t load_block_peripheral(Cl_peripheral_area_t *dst_a, cl_load_f_t s_load_f,cl_save_f_t d_save_f, cl_int_t dst_i, cl_int_t max_i, 
    cl_addr_t start_src_a, cl_addr_t end_src_a, void *custom_d)
{
    cl_int_t loaded_blocks = 0;
    cl_int_t loaded_data;
    while(1){
        if (dst_i >= max_i){ // loading ended successfully
            ULOG_DEBUG("load_block_peripheral:\tAll elements were saved");
            return loaded_blocks;
        }
        if (start_src_a >= end_src_a){ // some data were left not loaded
            ULOG_DEBUG("load_block_peripheral:\tSome elements were NOT saved");
            return loaded_blocks;
        }
        s_load_f(&loaded_data,start_src_a,custom_d);
        ULOG_DEBUG("save_block_peripheral:\tLOADED ELEMENT: %lx",loaded_data);
        d_save_f(loaded_data,dst_a->addresses[dst_i],custom_d);
        dst_i++;
        start_src_a++;
        loaded_blocks++;
    }
}


bool read_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area,void *custom_d,bool erase)
{
    ULOG_INFO("cl_load_mem_area:\tContext loading from area %ld to %ld started", src_area.id, dst_area.id);
    cl_save_f_t s_save_f = sel_save_f(src_area.save_type); // choose low-level technique for storing data
    cl_load_f_t s_load_f = sel_load_f(src_area.save_type); // choose low-level technique for loading data
    cl_save_f_t d_save_f = sel_save_f(dst_area.save_type); // choose low-level technique for storing data
    cl_load_f_t d_load_f = sel_load_f(dst_area.save_type); // choose low-level technique for loading data

    cl_int_t block_id, i_block_end, loaded_e,next_block_id,i_next_block_end;
    cl_int_t id = dst_area.id;
    cl_addr_t block_end,next_block_end;
    cl_addr_t src_addr = src_area.start_addr;
    cl_addr_t dst_addr = dst_area.start_addr;

    // iterate once for every block 
    while (src_addr <= src_area.end_addr){ // if end of source area is reached, some elements could not be stored
        s_load_f(&block_id,src_addr,custom_d); // load id of current block
        s_load_f(&i_block_end, src_addr + 1,custom_d); //! load end of the block address 
        block_end = (cl_addr_t)i_block_end;
        ULOG_DEBUG("BLOCK END: %x END_ADDR:%x",block_end, src_area.end_addr);
        if (block_end < src_area.end_addr){
            s_load_f(&next_block_id,block_end + 1,custom_d);
            if (next_block_id == 0 && (block_id == 0 || (block_id == id) && erase)){ // merge two empty blocks
                s_load_f(&i_next_block_end, block_end + 2,custom_d); //! load end of the block address 
                next_block_end = (cl_addr_t)i_next_block_end;
                ULOG_DEBUG("cl_load_mem_area:\tMerging two empty blocks");
                s_save_f((cl_int_t)next_block_end,src_addr + 1,custom_d); // added after v0.5.0
            }
        }
        ULOG_DEBUG("cl_load_mem_area:\tCurrent block: ID:%ld End block address:%ld",block_id,(cl_int_t)block_end);
        if(block_id == id){ // matching id, read data in this block
            puts("before load block");
            //dst_addr += fill_block(s_load_f, dst_addr,dst_area.end_addr,src_addr + HEAD_LENGTH,next_block_addr,custom_d);
            dst_addr += fill_block(s_load_f, d_save_f, src_addr + HEAD_LENGTH,block_end, dst_addr,dst_area.end_addr,custom_d);
            puts("after load block");
            // mark block as invalid (for load, not for read functions)
            if (erase){
                s_save_f(0x0,src_addr,custom_d);
            }
            if (dst_addr >= dst_area.end_addr){ // all elements were loaded
                ULOG_INFO("cl_load_mem_area:\tSuccessfully loaded all elements");
                return true;
            }
        }
        else{ // not matching id, simply skip to next block
            src_addr = block_end + 1;
        }
    }
    ULOG_ERROR("cl_load_mem_area:\t%ld elements from area %ld to %ld were not loaded", dst_area.end_addr - dst_addr, src_area.id, dst_area.id);
    return false;
}


bool read_load_peripheral_area(const Cl_peripheral_area_t *dst_area, Cl_memory_area_t src_area,void *custom_d,bool erase)
{
    ULOG_INFO("cl_load_mem_area:\tContext loading from area %ld to %ld started", src_area.id, dst_area->id);
    cl_save_f_t s_save_f = sel_save_f(src_area.save_type); // choose low-level technique for storing data
    cl_load_f_t s_load_f = sel_load_f(src_area.save_type); // choose low-level technique for loading data
    cl_save_f_t d_save_f = sel_save_f(dst_area->save_type); // choose low-level technique for storing data
    cl_load_f_t d_load_f = sel_load_f(dst_area->save_type); // choose low-level technique for loading data

    cl_int_t block_id, i_next_block_addr, loaded_e,next_block_id,i_next_next_block_addr;
    cl_int_t id = dst_area->id;
    cl_addr_t next_block_addr,next_next_block_addr;
    cl_addr_t src_addr = src_area.start_addr;
    cl_int_t dst_i = 0;

    // iterate once for every block 
    while (src_addr <= src_area.end_addr){ // if end of source area is reached, some elements could not be stored
        s_load_f(&block_id,src_addr,custom_d); // load id of current block
        s_load_f(&i_next_block_addr, src_addr + 1,custom_d); //! load end of the block address 
        next_block_addr = (cl_addr_t)i_next_block_addr;
        s_load_f(&next_block_id,next_block_addr,custom_d);
        ULOG_DEBUG("cl_load_mem_area:\tCurrent block: ID:%ld Next block address:%ld",block_id,(cl_int_t)next_block_addr);
        // added after v0.5.0
        if (next_block_id == 0 && (block_id == 0 || (block_id == id) && erase)){ // merge two empty blocks
            s_load_f(&i_next_next_block_addr, next_block_addr + 1,custom_d); //! load end of the block address 
            next_next_block_addr = (cl_addr_t)i_next_next_block_addr;
            ULOG_DEBUG("cl_load_mem_area:\tMerging two empty blocks");
            s_save_f((cl_int_t)next_next_block_addr,src_addr + 1,custom_d); // added after v0.5.0
        }
        if(block_id == id){ // matching id, read data in this block
            puts("before load block");
            //dst_addr += fill_block(s_load_f, dst_addr,dst_area.end_addr,src_addr + HEAD_LENGTH,next_block_addr,custom_d);
            dst_i += load_block_peripheral(dst_area,s_load_f, d_save_f,dst_i,dst_area->addr_num, src_addr + HEAD_LENGTH, next_block_addr, custom_d);
            puts("after load block");
            // mark block as invalid (for load, not for read functions)
            if (erase){
                s_save_f(0x0,src_addr,custom_d);
            }
            if (dst_i == dst_area->addr_num){ // all elements were loaded
                ULOG_INFO("cl_load_mem_area:\tSuccessfully loaded all elements");
                return true;
            }
        }
        else{ // not matching id, simply skip to next block
            src_addr = next_block_addr;
        }
    }
    ULOG_ERROR("cl_load_mem_area:\t%ld elements from area %ld to %ld were not loaded", dst_area->addr_num - dst_i, src_area.id, dst_area->id);
    return false;
}



bool cl_init()
{
    #ifndef ULOG_CONSOLE_LEVEL
    #define ULOG_CONSOLE_LEVEL ULOG_DEBUG_LEVEL
    #endif
    #ifndef ULOG_FILE_LEVEL
    #define ULOG_FILE_LEVEL ULOG_INFO_LEVEL
    #endif
    #ifndef ULOG_FILE_NAME
    #define ULOG_FILE_NAME "cl_logging.txt"
    #endif
    l3_init();
    ULOG_INIT();

    #ifdef ULOG_CONSOLE_ENABLE
    ULOG_SUBSCRIBE(console_log,ULOG_DEBUG_LEVEL);
    #endif

    #ifdef ULOG_FILE_ENABLE
    ULOG_SUBSCRIBE(file_log,ULOG_FILE_LEVEL);
    #endif

    ULOG_SUBSCRIBE(mcuxpresso_log,ULOG_TRACE_LEVEL);

    #ifdef ULOG_CUSTOM_ENABLE
    // here, add your logging functions subscriptions
    #endif
    
    return true;
}
