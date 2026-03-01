#include "types.h"

#include "../../platform/posix/context_lib_port.h"

cl_int_t cl_bare_save(cl_addr_t data, cl_addr_t addr, cl_int_t byte_size, enum Bare_save_type save_type, void *custom_other_data);

cl_int_t cl_bare_load(cl_addr_t buffer, cl_addr_t addr, cl_int_t byte_size, enum Bare_save_type load_type, void *custom_other_data); 

cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_custom_send_e(cl_int_t e, cl_addr_t addr, void *custom_other_data);

cl_int_t cl_raw_save_B(uint8_t B, uint8_t *addr, void *not_used);
cl_int_t cl_raw_send_B(uint8_t B, uint8_t *addr, void *not_used);
cl_int_t cl_raw_custom_send_B(uint8_t B, uint8_t *addr, void *custom_other_data);


cl_int_t cl_raw_save_hw(uint16_t hw, uint16_t *addr, void *not_used);
cl_int_t cl_raw_send_hw(uint16_t hw, uint16_t *addr, void *not_used);
cl_int_t cl_raw_custom_send_hw(uint16_t hw, uint16_t *addr, void *custom_other_data);



cl_int_t cl_raw_save_w(uint32_t w, uint32_t *addr, void *not_used);
cl_int_t cl_raw_send_w(uint32_t w, uint32_t *addr, void *not_used);
cl_int_t cl_raw_custom_send_w(uint32_t w, uint32_t *addr, void *custom_other_data);

cl_int_t cl_raw_save_dw(uint64_t dw, uint64_t *addr, void *not_used);
cl_int_t cl_raw_send_dw(uint64_t dw, uint64_t *addr, void *not_used);
cl_int_t cl_raw_custom_send_dw(uint64_t dw, uint64_t *addr, void *custom_other_data);


cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *not_used);
cl_int_t cl_raw_custom_rcv_e(cl_addr_t e, cl_addr_t addr, void *custom_other_data);

cl_int_t cl_raw_load_B(uint8_t *B, uint8_t *addr, void *not_used);
cl_int_t cl_raw_rcv_B(uint8_t *B, uint8_t *addr, void *not_used);
cl_int_t cl_raw_custom_rcv_B(uint8_t *B, uint8_t *addr, void *custom_other_data);


cl_int_t cl_raw_load_hw(uint16_t *hw, uint16_t *addr, void *not_used);
cl_int_t cl_raw_rcv_hw(uint16_t *hw, uint16_t *addr, void *not_used);
cl_int_t cl_raw_custom_rcv_hw(uint16_t *hw, uint16_t *addr, void *custom_other_data);


cl_int_t cl_raw_load_w(uint32_t *w, uint32_t *addr, void *not_used);
cl_int_t cl_raw_rcv_w(uint32_t *w, uint32_t *addr, void *not_used);
cl_int_t cl_raw_custom_rcv_w(uint32_t *w, uint32_t *addr, void *custom_other_data);

cl_int_t cl_raw_load_dw(uint64_t *w, uint64_t *addr, void *not_used);
cl_int_t cl_raw_rcv_dw(uint64_t *w, uint64_t *addr, void *not_used);
cl_int_t cl_raw_custom_rcv_dw(uint64_t *w, uint64_t *addr, void *custom_other_data);



/*
uint32_t cl_raw_save_arr_B(uint8_t *data, uint8_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_save_arr_hw(uint16_t *data, uint16_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_save_arr_w(uint32_t *data, uint32_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_B(uint8_t *buffer, uint8_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_hw(uint16_t *buffer, uint16_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_w(uint32_t *buffer, uint32_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
*/