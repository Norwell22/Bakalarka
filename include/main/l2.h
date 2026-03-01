#include "types.h"

#include "../../platform/posix/context_lib_port.h"

cl_int_t cl_clear_mem_area(Cl_memory_area_t area, enum Bare_save_type clear_type, void *custom_other_data);

cl_int_t cl_save_mem_area(Cl_memory_area_t src_area, Cl_memory_area_t dst_area , enum Bare_save_type save_type, void *custom_other_data);

cl_int_t cl_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type, void *custom_other_data);

cl_int_t cl_read_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type, void *custom_other_data);

cl_int_t cl_save_peripheral(Cl_peripheral_area_t src_area, Cl_peripheral_area_t dst_area, enum Bare_save_type save_type,void *custom_other_data);

cl_int_t cl_load_peripheral(Cl_peripheral_area_t dst_area, Cl_peripheral_area_t src_area, enum Bare_save_type save_type, void *custom_other_data);

cl_int_t cl_read_peripheral(Cl_peripheral_area_t dst_area, Cl_peripheral_area_t src_area, enum Bare_save_type save_type, void *custom_other_data);



cl_save_f_t sel_save_f(enum Bare_save_type save_type);

cl_load_f_t sel_load_f(enum Bare_save_type save_type);

cl_int_t fill_block(cl_save_f_t save_f,cl_addr_t start_src_a, cl_addr_t end_src_a, cl_addr_t start_dst_a, cl_addr_t end_dst_a,void *custom_d);


cl_int_t load_block(cl_load_f_t load_f,cl_addr_t start_src_a, cl_addr_t end_src_a, cl_addr_t start_dst_a, cl_addr_t end_dst_a,void *custom_d);


cl_int_t read_load_mem_area(Cl_memory_area_t dst_area, Cl_memory_area_t src_area, enum Bare_save_type save_type,void *custom_d,uint8_t erase);