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
 */
#include "cl_layer1.h"
#include "cl_layer2.h"
#include "cl_layer3.h"
#include "ulog.h"

#ifdef CL_ALLOW_L3

/*!
* \brief Simple function determining whether area is protected
*
* When context area is protected, it returns true, otherwise false.
* To save some space, area protection metadata is implemented over
* an 256-elements long bit array
*/
bool is_protected(cl_int_t id)
{
    cl_int_t protected;
    // mask bit that belongs to given id
    cl_int_t mask = (cl_int_t)1 << (id % ARCHITECTURE_BUS_SIZE);
    // load data element on right position
    cl_load_f_t load_f = sel_load_f(cl_metadata_ma.save_type);
    load_f(&protected,cl_metadata_ma.start_addr + id / ARCHITECTURE_BUS_SIZE, NULL);
    if (mask & protected){
        ULOG_DEBUG("is_protected:\tarea %lu is protected",id);
        return true;
    }
    return false;
}

enum Cl_power_mode_t cl_get_mode()
{
    cl_int_t mode;
    cl_load_f_t load_f = sel_load_f(cl_metadata_ma.save_type);
    load_f(&mode,cl_metadata_ma.end_addr, NULL);
    return (enum Cl_power_mode_t)mode;
}

void cl_write_mode(enum Cl_power_mode_t new_mode)
{
    cl_save_f_t save_f = sel_save_f(cl_metadata_ma.save_type);
    save_f((cl_int_t)new_mode,cl_metadata_ma.end_addr,NULL);
}

// turn on context area
bool cl_area_on( cl_int_t id, void *custom_d)
{
    enum Cl_power_mode_t mode = cl_get_mode();
    cl_int_t i;
    if (!is_protected(id)) // if not protected, nothing has to be done
    {
        ULOG_INFO("cl_area_on:\tArea %lu is not protected and therefore won't be loaded",id);
        return false;
    }
    for (i = 0; i < cl_area_backup_table_size; i++){
        if (cl_area_backup_table[i].area->id != id || cl_area_backup_table[i].mode != mode){
            continue;
        }
        ULOG_DEBUG("cl_area_on:\tFound area with id %lu",id);
        return cl_load_mem_area(*(cl_area_backup_table[i].area), *(cl_area_backup_table[i].backup_area),NULL);
    }
    for (i = 0; i < cl_peripheral_backup_table_size; i++){
        if (cl_peripheral_backup_table[i].area->id != id || cl_peripheral_backup_table[i].mode != mode){
            continue;
        }
        ULOG_DEBUG("cl_area_on:\tFound peripheral with id %lu",id);
        return cl_load_peripheral(cl_peripheral_backup_table[i].area, *(cl_peripheral_backup_table[i].backup_area),NULL);
    }
    return false;
}

bool cl_area_off( cl_int_t id, void *custom_d)
{
    enum Cl_power_mode_t current_mode = cl_get_mode();
    cl_int_t i;
    if (!is_protected(id))
    {
        ULOG_INFO("cl_area_off:\tArea %lu is not protected and therefore won't be saved",id);
        return false;
    }
    for (i = 0; i < cl_area_backup_table_size; i++){
        if (cl_area_backup_table[i].area->id != id){
            continue;
        }
        ULOG_DEBUG("cl_area_off:\tFound area with id %lu",id);
        return cl_save_mem_area(*(cl_area_backup_table[i].area), *(cl_area_backup_table[i].backup_area),NULL);
    }
    for (i = 0; i < cl_peripheral_backup_table_size; i++){
        if (cl_peripheral_backup_table[i].area->id != id){
            continue;
        }
        ULOG_DEBUG("cl_area_off:\tFound peripheral with id %lu",id);
        return cl_save_peripheral(cl_peripheral_backup_table[i].area, *(cl_peripheral_backup_table[i].backup_area),NULL);
    }
    return false;
}

/*!
* \brief Set every context area as protected
*/
static bool protect_all()
{
    cl_int_t i;
    bool success = true;
    for (i = 0; i < 256; i++){
        success &= cl_protect_memory(i);
    }
    return success;
}

/*!
* \brief Set every context area as unprotected
*/
static bool unprotect_all()
{
    cl_int_t i;
    bool success = true;
    for (i = 0; i < 256; i++){
        success &= cl_unprotect_memory(i);
    }
    return success;
}

bool cl_protect_memory(cl_int_t id)
{
    if (id >= 256){ // max allowed id
        ULOG_WARNING("cl_protect_memory:\tID should be in range 0 - 255, please adjust memory area accordingly");
        return false;
    }
    cl_int_t mask = (cl_int_t)1 << (id % ARCHITECTURE_BUS_SIZE);
    ULOG_DEBUG("cl_protect_memory:\tid mod ABS is %lu",id % ARCHITECTURE_BUS_SIZE);
    ULOG_DEBUG("cl_protect_memory:\tmask is %lu",mask);
    CL_PROTECTED_MEM[id / ARCHITECTURE_BUS_SIZE] |= mask;
    return true;
}

bool cl_unprotect_memory(cl_int_t id)
{
    if (id >= 256){ // max allowed id
        ULOG_WARNING("cl_unprotect_memory:\tID should be in range 0 - 255, please adjust memory area accordingly");
        return false;
    }
    cl_int_t mask = ~( (cl_int_t)1 << (id % ARCHITECTURE_BUS_SIZE));
    ULOG_DEBUG("cl_unprotect_memory:\tid mod ABS is %lu",id % ARCHITECTURE_BUS_SIZE);
    ULOG_DEBUG("cl_unprotect_memory:\tmask is %lu",mask);
    CL_PROTECTED_MEM[id / ARCHITECTURE_BUS_SIZE] &= mask;
    return true;
}

/*!
* \brief Finds intersection of two address ranges
* 
* \note This function has been generated by ChatGPT
* \note Should be obsolete
* \todo Check if obsolete
*/
bool find_match(cl_addr_t start_a1, cl_addr_t end_a1, cl_addr_t start_a2,
                cl_addr_t end_a2, cl_addr_t *start, cl_addr_t *end)
{
    if (start_a1 > end_a1 || start_a2 > end_a2) {
        return false;
    }

    cl_addr_t s = (start_a1 > start_a2) ? start_a1 : start_a2;
    cl_addr_t e = (end_a1   < end_a2)   ? end_a1   : end_a2;

    if (s >= e) {
        return false;
    }
    ULOG_DEBUG("find_match:\tsize of match is %lu",e - s);

    if (start) *start = s;
    if (end)   *end   = e;

    return true;
}


bool cl_change_mode(enum Cl_power_mode_t to_mode,void *custom_d)
{
    enum Cl_power_mode_t from_mode = cl_get_mode();
    cl_int_t i;
    bool success = true;
    for (i = 0; i < cl_area_backup_table_size; i++){
        if (cl_area_backup_table[i].mode == to_mode &&
             is_protected(cl_area_backup_table[i].area->id) &&
            !cl_area_backup_table[i].default_on){
            success &= cl_save_mem_area(*(cl_area_backup_table[i].area), *(cl_area_backup_table[i].backup_area),NULL);
        }
        if (cl_area_backup_table[i].mode == from_mode && 
            is_protected(cl_area_backup_table[i].area->id) && 
            !cl_area_backup_table[i].default_on){
            success &= cl_load_mem_area(*(cl_area_backup_table[i].area), *(cl_area_backup_table[i].backup_area),NULL);
        }
    }
    for (i = 0; i < cl_peripheral_backup_table_size; i++){
        if (cl_peripheral_backup_table[i].mode == to_mode && 
            is_protected(cl_peripheral_backup_table[i].area->id) && 
            !cl_peripheral_backup_table[i].default_on){
            success &= cl_save_peripheral(cl_peripheral_backup_table[i].area, *(cl_peripheral_backup_table[i].backup_area),NULL);
        }
        if (cl_peripheral_backup_table[i].mode == from_mode 
            && is_protected(cl_peripheral_backup_table[i].area->id) 
            && !cl_peripheral_backup_table[i].default_on){
            success &=  cl_load_peripheral(cl_peripheral_backup_table[i].area, *(cl_peripheral_backup_table[i].backup_area),NULL);
        }
    }
    cl_write_mode(to_mode);
    return success;
}

bool l3_init()
{
    cl_write_mode(CL_DEFAULT_MODE);
    cl_int_t i;
    for (i = 0; i < cl_area_backup_table_size; i++){
        cl_clear_mem_area(*(cl_area_backup_table[i].backup_area),NULL);
    }
    for (i = 0; i < cl_peripheral_backup_table_size; i++){
        cl_clear_mem_area(*(cl_peripheral_backup_table[i].backup_area),NULL);
    }
    #ifdef CL_DEFAULT_PROTECT
    protect_all();
    #else
    unprotect_all();
    cl_protect_memory(255);
    #endif
    // for unprotect all, protect at least 255
    return true;
}
#else
bool l3_init()
{
    return true;
}
#endif