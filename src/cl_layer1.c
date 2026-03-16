/*! 
 * \file      cl_layer1.c
 * \brief     Functions implementing first library layer
 * \details   
 * Dependencies:
 * - "../../include/main/l1.h"
 * Implementation of private, low level functions used for working
 * with individual bytes of data. In general, functions simply read, write
 * and shuffle bytes.
 * \author    Michal Zidzik
 * \date      02.03.2026
 */
#include "cl_layer1.h"
//#include "../../include/main/cl_layer1_priv.h"

static cl_int_t save_byte(uint8_t b, uint8_t *addr)
{
   *addr = b; 
   return 0;
}
static cl_int_t load_byte(uint8_t *b, uint8_t *addr)
{
   *b = *addr;
   return 0;
}


/* 
* Save functions 
*/

cl_int_t raw_save_B(uint8_t B, uint8_t *addr, void *not_used)
{
   save_byte( B, addr);
   return 0;
}

cl_int_t raw_send_B(uint8_t B, uint8_t *addr, void *other_d)
{
   send_byte( B, addr, other_d);
   return 0;
}


cl_int_t raw_save_hw(uint16_t hw, uint16_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b0 = (uint8_t)(hw & 0xFF);
    uint8_t b1 = (uint8_t)((hw >> 8) & 0xFF);
    save_byte(b0, dst);
    save_byte(b1, dst + 1);
    return 0;
}

cl_int_t raw_send_hw(uint16_t hw, uint16_t *addr, void *other_d)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b0 = (uint8_t)(hw & 0xFF);
    uint8_t b1 = (uint8_t)((hw >> 8) & 0xFF);
    send_byte(b0, dst,other_d);
    send_byte(b1, dst + 1,other_d);
    return 0;
}


cl_int_t raw_save_w(uint32_t w, uint32_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;

    save_byte((uint8_t)( w        & 0xFF), dst);
    save_byte((uint8_t)((w >> 8 ) & 0xFF), dst + 1);
    save_byte((uint8_t)((w >> 16) & 0xFF), dst + 2);
    save_byte((uint8_t)((w >> 24) & 0xFF), dst + 3);

    return 0;
}

/*
* Send functions
*/

cl_int_t raw_send_w(uint32_t w, uint32_t *addr, void *other_d)
{
    uint8_t *dst = (uint8_t*)addr;
    send_byte((uint8_t)( w        & 0xFF), dst,other_d);
    send_byte((uint8_t)((w >> 8 ) & 0xFF), dst + 1,other_d);
    send_byte((uint8_t)((w >> 16) & 0xFF), dst + 2,other_d);
    send_byte((uint8_t)((w >> 24) & 0xFF), dst + 3,other_d);
    return 0;
}


cl_int_t raw_save_dw(uint64_t dw, uint64_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    save_byte((uint8_t)( dw        & 0xFF), dst);
    save_byte((uint8_t)((dw >> 8 ) & 0xFF), dst + 1);
    save_byte((uint8_t)((dw >> 16) & 0xFF), dst + 2);
    save_byte((uint8_t)((dw >> 24) & 0xFF), dst + 3);
    save_byte((uint8_t)( dw >> 32  & 0xFF), dst + 4);
    save_byte((uint8_t)((dw >> 40) & 0xFF), dst + 5);
    save_byte((uint8_t)((dw >> 48) & 0xFF), dst + 6);
    save_byte((uint8_t)((dw >> 56) & 0xFF), dst + 7);
    return 0;
}

cl_int_t raw_send_dw(uint64_t dw, uint64_t *addr, void *other_d)
{
    uint8_t *dst = (uint8_t*)addr;
    send_byte((uint8_t)( dw        & 0xFF), dst,other_d);
    send_byte((uint8_t)((dw >> 8 ) & 0xFF), dst + 1,other_d);
    send_byte((uint8_t)((dw >> 16) & 0xFF), dst + 2,other_d);
    send_byte((uint8_t)((dw >> 24) & 0xFF), dst + 3,other_d);
    send_byte((uint8_t)( dw >> 32  & 0xFF), dst + 4,other_d);
    send_byte((uint8_t)((dw >> 40) & 0xFF), dst + 5,other_d);
    send_byte((uint8_t)((dw >> 48) & 0xFF), dst + 6,other_d);
    send_byte((uint8_t)((dw >> 56) & 0xFF), dst + 7,other_d);
    return 0;
}


cl_int_t raw_load_B(uint8_t *B, uint8_t *addr, void *not_used)
{
   load_byte( B, addr);
   return 0;
}

cl_int_t raw_rcv_B(uint8_t *B, uint8_t *addr, void *other_d)
{
   rcv_byte( B, addr,other_d);
   return 0;
}


cl_int_t raw_load_hw(uint16_t *hw, uint16_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    load_byte(&b0,src);
    load_byte(&b1,src + 1);
    *hw =  (uint16_t)b0 | ((uint16_t)b1 << 8);
    return 0;
}

cl_int_t raw_rcv_hw(uint16_t *hw, uint16_t *addr, void *other_d)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    rcv_byte(&b0,src,other_d);
    rcv_byte(&b1,src + 1,other_d);
    *hw =  (uint16_t)b0 | ((uint16_t)b1 << 8);
    return 0;
}


cl_int_t raw_load_w(uint32_t *w, uint32_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    load_byte(&b0,src);
    load_byte(&b1,src + 1);
    load_byte(&b2,src + 2);
    load_byte(&b3,src + 3);
    *w =  (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
    return 0;
}

cl_int_t raw_rcv_w(uint32_t *w, uint32_t *addr, void *other_d)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    rcv_byte(&b0,src,other_d);
    rcv_byte(&b1,src + 1,other_d);
    rcv_byte(&b2,src + 2,other_d);
    rcv_byte(&b3,src + 3,other_d);
    *w =  (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
    return 0;
}


cl_int_t raw_load_dw(uint64_t *dw, uint64_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0, b1, b2, b3, b4, b5, b6, b7;
    load_byte(&b0,src);
    load_byte(&b1,src + 1);
    load_byte(&b2,src + 2);
    load_byte(&b3,src + 3);
    load_byte(&b4,src + 4);
    load_byte(&b5,src + 5);
    load_byte(&b6,src + 6);
    load_byte(&b7,src + 7);
    *dw =  (uint64_t)b0 | ((uint64_t)b1 << 8) | ((uint64_t)b2 << 16) | ((uint64_t)b3 << 24)
               | ((uint64_t)b4 << 32) | ((uint64_t)b5 << 40)  | ((uint64_t)b6 << 48) | ((uint64_t)b7 << 56);
    return 0;
}

cl_int_t raw_rcv_dw(uint64_t *dw, uint64_t *addr, void *other_d)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0, b1, b2, b3, b4, b5, b6, b7;
    rcv_byte(&b0,src,other_d);
    rcv_byte(&b1,src + 1,other_d);
    rcv_byte(&b2,src + 2,other_d);
    rcv_byte(&b3,src + 3,other_d);
    rcv_byte(&b4,src + 4,other_d);
    rcv_byte(&b5,src + 5,other_d);
    rcv_byte(&b6,src + 6,other_d);
    rcv_byte(&b7,src + 7,other_d);
    *dw =  (uint64_t)b0 | ((uint64_t)b1 << 8) | ((uint64_t)b2 << 16) | ((uint64_t)b3 << 24)
               | ((uint64_t)b4 << 32) | ((uint64_t)b5 << 40)  | ((uint64_t)b6 << 48) | ((uint64_t)b7 << 56);
    return 0;
}



// save element functions are chosen based on architecture size
#if ARCHITECTURE_BUS_SIZE == 8
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return raw_save_B(e,addr,not_used);
}
cl_int_t raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d)
{
    return raw_send_B(e,addr,other_d);
}
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return raw_load_B(e,addr,not_used);
}
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d)
{
    return raw_rcv_B(e,addr,other_d);
}
#elif ARCHITECTURE_BUS_SIZE == 16
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return raw_save_hw(e,addr,not_used);
}
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d)
{
    return raw_send_hw(e,addr,other_d);
}
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return raw_load_hw(e,addr,not_used);
}
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d)
{
    return raw_rcv_hw(e,addr,other_d);
}
#elif ARCHITECTURE_BUS_SIZE == 32
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return raw_save_w(e,addr,not_used);
}
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d)
{
    return raw_send_w(e,addr,other_d);
}
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return raw_load_w(e,addr,not_used);
}
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d)
{
    return raw_rcv_w(e,addr,other_d);
}
#elif ARCHITECTURE_BUS_SIZE == 64
cl_int_t cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return raw_save_dw(e,addr,not_used);
}
cl_int_t cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d)
{
    return raw_send_dw(e,addr,other_d);
}
cl_int_t cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return raw_load_dw(e,addr,not_used);
}
cl_int_t cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d)
{
    return raw_rcv_dw(e,addr,other_d);
}
#endif
