#include "../../include/main/context_manager.h"
#include <stdio.h> //this would be better if wasn't here
#include <stdbool.h> //this would be better if it wasn't here


#if ARCHITECTURE_BUS_SIZE == 8
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_save_B(e,addr,not_used);
}
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_send_B(e,addr,not_used);
}
cl_int_t cl_raw_custom_send_e(cl_int_t e, cl_addr_t addr, void *custom_other_data)
{
    return cl_raw_custom_send_B(e,addr,custom_other_data);
}
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_load_B(e,addr,not_used);
}
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_rcv_B(e,addr,not_used);
}
cl_int_t cl_raw_custom_rcv_e(cl_addr_t e, cl_addr_t addr, void *custom_other_data)
{
    return cl_raw_custom_rcv_B(e,addr,custom_other_data);
}
#elif ARCHITECTURE_BUS_SIZE == 16
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_save_hw(e,addr,not_used);
}
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_send_hw(e,addr,not_used);
}
cl_int_t cl_raw_custom_send_e(cl_int_t e, cl_addr_t addr, void *custom_other_data)
{
    return cl_raw_custom_send_hw(e,addr,custom_other_data);
}
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_load_hw(e,addr,not_used);
}
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_rcv_hw(e,addr,not_used);
}
cl_int_t cl_raw_custom_rcv_e(cl_addr_t e, cl_addr_t addr, void *custom_other_data)
{
    return cl_raw_custom_rcv_hw(e,addr,custom_other_data);
}
#elif ARCHITECTURE_BUS_SIZE == 32
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_save_w(e,addr,not_used);
}
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_send_w(e,addr,not_used);
}
cl_int_t cl_raw_custom_send_e(cl_int_t e, cl_addr_t addr, void *custom_other_data)
{
    return cl_raw_custom_send_w(e,addr,custom_other_data);
}
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_load_w(e,addr,not_used);
}
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_rcv_w(e,addr,not_used);
}
cl_int_t cl_raw_custom_rcv_e(cl_addr_t e, cl_addr_t addr, void *custom_other_data)
{
    return cl_raw_custom_rcv_w(e,addr,custom_other_data);
}
#elif ARCHITECTURE_BUS_SIZE == 64
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_save_dw(e,addr,not_used);
}
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_send_dw(e,addr,not_used);
}
cl_int_t cl_raw_custom_send_e(cl_int_t e, cl_addr_t addr, void *custom_other_data)
{
    return cl_raw_custom_send_dw(e,addr,custom_other_data);
}
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_load_dw(e,addr,not_used);
}
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return cl_raw_rcv_dw(e,addr,not_used);
}
cl_int_t cl_raw_custom_rcv_e(cl_addr_t e, cl_addr_t addr, void *custom_other_data)
{
    return cl_raw_custom_rcv_dw(e,addr,custom_other_data);
}
#endif