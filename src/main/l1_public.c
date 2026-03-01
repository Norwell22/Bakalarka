#include "../../include/main/context_manager.h"
#include "../../platform/posix/context_lib_port.h"
#include <stdio.h> //this would be better if wasn't here
#include <stdbool.h> //this would be better if it wasn't here



cl_int_t cl_raw_save_B(uint8_t B, uint8_t *addr, void *not_used)
{
   save_byte( B, addr);
   return 0;
}

cl_int_t cl_raw_send_B(uint8_t B, uint8_t *addr, void *not_used)
{
   send_byte( B, addr);
   return 0;
}

cl_int_t cl_raw_custom_send_B(uint8_t B, uint8_t *addr, void *custom_other_data)
{
   custom_send_byte( B, addr,custom_other_data);
   return 0;
}


cl_int_t cl_raw_save_hw(uint16_t hw, uint16_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b0 = (uint8_t)(hw & 0xFF);
    uint8_t b1 = (uint8_t)((hw >> 8) & 0xFF);
    save_byte(b0, dst);
    save_byte(b1, dst + 1);
    return 0;
}

cl_int_t cl_raw_send_hw(uint16_t hw, uint16_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b0 = (uint8_t)(hw & 0xFF);
    uint8_t b1 = (uint8_t)((hw >> 8) & 0xFF);
    send_byte(b0, dst);
    send_byte(b1, dst + 1);
    return 0;
}

cl_int_t cl_raw_custom_send_hw(uint16_t hw, uint16_t *addr, void *custom_other_data)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b0 = (uint8_t)(hw & 0xFF);
    uint8_t b1 = (uint8_t)((hw >> 8) & 0xFF);
    custom_send_byte(b0, dst,     custom_other_data);
    custom_send_byte(b1, dst + 1, custom_other_data);
    return 0;
}

cl_int_t cl_raw_save_w(uint32_t w, uint32_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b,i;
    for (i = 0; i < 4; i++){
      b = (uint8_t)(w >> (i*8) & 0xFF);
      save_byte(b,dst + i);
    }
    return 0;
}



cl_int_t cl_raw_send_w(uint32_t w, uint32_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b,i;
    for (i = 0; i < 4; i++){
      b = (uint8_t)(w >> (i*8) & 0xFF);
      send_byte(b,dst + i);
    }
    return 0;
}

cl_int_t cl_raw_custom_send_w(uint32_t w, uint32_t *addr, void *custom_other_data)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b,i;
    for (i = 0; i < 4; i++){
      b = (uint8_t)(w >> (i*8) & 0xFF);
      custom_send_byte(b,dst + i,custom_other_data);
    }
    return 0;
}

cl_int_t cl_raw_save_dw(uint64_t dw, uint64_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b,i;
    for (i = 0; i < 8; i++){
      b = (uint8_t)(dw >> (i*8) & 0xFF);
      save_byte(b,dst + i);
    }
    return 0;
}



cl_int_t cl_raw_send_dw(uint64_t dw, uint64_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b,i;
    for (i = 0; i < 8; i++){
      b = (uint8_t)(dw >> (i*8) & 0xFF);
      send_byte(b,dst + i);
    }
    return 0;
}

cl_int_t cl_raw_custom_send_dw(uint64_t dw, uint64_t *addr, void *custom_other_data)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b,i;
    for (i = 0; i < 8; i++){
      b = (uint8_t)(dw >> (i*8) & 0xFF);
      custom_send_byte(b,dst + i,custom_other_data);
    }
    return 0;
}


//receiving
cl_int_t cl_raw_load_B(uint8_t *B, uint8_t *addr, void *not_used)
{
   load_byte( B, addr);
   return 0;
}

cl_int_t cl_raw_rcv_B(uint8_t *B, uint8_t *addr, void *not_used)
{
   rcv_byte( B, addr);
   return 0;
}

cl_int_t cl_raw_custom_rcv_B(uint8_t *B, uint8_t *addr, void *custom_other_data)
{
   custom_rcv_byte( B, addr,custom_other_data);
   return 0;
}


cl_int_t cl_raw_load_hw(uint16_t *hw, uint16_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    load_byte(&b0,src);
    load_byte(&b1,src + 1);
    *hw =  (uint16_t)b0 | ((uint16_t)b1 << 8);
    return 0;
}

cl_int_t cl_raw_rcv_hw(uint16_t *hw, uint16_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    rcv_byte(&b0,src);
    rcv_byte(&b1,src + 1);
    *hw =  (uint16_t)b0 | ((uint16_t)b1 << 8);
    return 0;
}



cl_int_t cl_raw_custom_rcv_hw(uint16_t *hw, uint16_t *addr, void *custom_other_data)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    custom_rcv_byte(&b0,src,custom_other_data);
    custom_rcv_byte(&b1,src + 1,custom_other_data);
    *hw =  (uint16_t)b0 | ((uint16_t)b1 << 8);
    return 0;
}


cl_int_t cl_raw_load_w(uint32_t *w, uint32_t *addr, void *not_used)
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

cl_int_t cl_raw_rcv_w(uint32_t *w, uint32_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    rcv_byte(&b0,src);
    rcv_byte(&b1,src + 1);
    rcv_byte(&b2,src + 2);
    rcv_byte(&b3,src + 3);
    *w =  (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
    return 0;
}

cl_int_t cl_raw_custom_rcv_w(uint32_t *w, uint32_t *addr, void *custom_other_data)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    custom_rcv_byte(&b0,src, custom_other_data);
    custom_rcv_byte(&b1,src + 1, custom_other_data);
    custom_rcv_byte(&b2,src + 2, custom_other_data);
    custom_rcv_byte(&b3,src + 3, custom_other_data);
    *w =  (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
    return 0;
}

cl_int_t cl_raw_load_dw(uint64_t *dw, uint64_t *addr, void *not_used)
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

cl_int_t cl_raw_rcv_dw(uint64_t *dw, uint64_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0, b1, b2, b3, b4, b5, b6, b7;
    rcv_byte(&b0,src);
    rcv_byte(&b1,src + 1);
    rcv_byte(&b2,src + 2);
    rcv_byte(&b3,src + 3);
    rcv_byte(&b4,src + 4);
    rcv_byte(&b5,src + 5);
    rcv_byte(&b6,src + 6);
    rcv_byte(&b7,src + 7);
    *dw =  (uint64_t)b0 | ((uint64_t)b1 << 8) | ((uint64_t)b2 << 16) | ((uint64_t)b3 << 24)
               | ((uint64_t)b4 << 32) | ((uint64_t)b5 << 40)  | ((uint64_t)b6 << 48) | ((uint64_t)b7 << 56);
    return 0;
}

cl_int_t cl_raw_custom_rcv_dw(uint64_t *dw, uint64_t *addr, void *custom_other_data)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0, b1, b2, b3, b4, b5, b6, b7;
    custom_rcv_byte(&b0,src, custom_other_data);
    custom_rcv_byte(&b1,src + 1, custom_other_data);
    custom_rcv_byte(&b2,src + 2, custom_other_data);
    custom_rcv_byte(&b3,src + 3, custom_other_data);
    custom_rcv_byte(&b4,src + 4, custom_other_data);
    custom_rcv_byte(&b5,src + 5, custom_other_data);
    custom_rcv_byte(&b6,src + 6, custom_other_data);
    custom_rcv_byte(&b7,src + 7, custom_other_data);
    *dw =  (uint64_t)b0 | ((uint64_t)b1 << 8) | ((uint64_t)b2 << 16) | ((uint64_t)b3 << 24)
               | ((uint64_t)b4 << 32) | ((uint64_t)b5 << 40)  | ((uint64_t)b6 << 48) | ((uint64_t)b7 << 56);
    return 0;
}