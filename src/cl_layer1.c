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
#include "ulog.h"
//#include "../../include/main/cl_layer1_priv.h"

static void save_byte(uint8_t b, uint8_t *addr)
{
   *addr = b; 
}
static void load_byte(uint8_t *b, uint8_t *addr)
{
   *b = *addr;
}

/*
won't work because of missing MCUXpresso enviroment
#include "cl_layer1.h"
#include "ulog.h"
#include "fsl_i2c.h"
#include "fsl_common.h"
#include "fsl_gpio.h"


status_t eeprom_write_b(uint8_t byte, uint8_t *addr) {
    i2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));
    masterXfer.slaveAddress   = 0x50;
    masterXfer.direction      = kI2C_Write;
    masterXfer.subaddress     = (uint8_t)addr;
    masterXfer.subaddressSize = 1;          // 24LC01B uses 1-byte addressing
    masterXfer.data           = &byte;
    masterXfer.dataSize       = 1;
    masterXfer.flags          = kI2C_TransferDefaultFlag;
    status_t result = I2C_MasterTransferBlocking(I2C1, &masterXfer);
    SDK_DelayAtLeastUs(5000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    return result;
}

status_t eeprom_read_b(uint8_t *byte, uint8_t *addr) {
    i2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress   = 0x50;
    masterXfer.direction      = kI2C_Read;
    masterXfer.subaddress     = (uint8_t)addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = byte;
    masterXfer.dataSize       = 1;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    return I2C_MasterTransferBlocking(I2C1, &masterXfer);
}
*/

cl_int_t eeprom_write_b(uint8_t byte, uint8_t *addr)
{
    return 0;
}

status_t eeprom_read_b(uint8_t *byte, uint8_t *addr)
{
    return 0;
}


/* 
* Save functions 
*/

void raw_save_B(uint8_t B, uint8_t *addr, void *not_used)
{
   save_byte( B, addr);
}

void raw_send_B(uint8_t B, uint8_t *addr, void *other_d)
{
   send_byte( B, addr, other_d);
}


void raw_save_hw(uint16_t hw, uint16_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b0 = (uint8_t)(hw & 0xFF);
    uint8_t b1 = (uint8_t)((hw >> 8) & 0xFF);
    save_byte(b0, dst);
    save_byte(b1, dst + 1);
}

void raw_send_hw(uint16_t hw, uint16_t *addr, void *other_d)
{
    uint8_t *dst = (uint8_t*)addr;
    uint8_t b0 = (uint8_t)(hw & 0xFF);
    uint8_t b1 = (uint8_t)((hw >> 8) & 0xFF);
    send_byte(b0, dst,other_d);
    send_byte(b1, dst + 1,other_d);
}


void raw_save_w(uint32_t w, uint32_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;

    save_byte((uint8_t)( w        & 0xFF), dst);
    save_byte((uint8_t)((w >> 8 ) & 0xFF), dst + 1);
    save_byte((uint8_t)((w >> 16) & 0xFF), dst + 2);
    save_byte((uint8_t)((w >> 24) & 0xFF), dst + 3);
}

/*
* Send functions
*/

void raw_send_w(uint32_t w, uint32_t *addr, void *other_d)
{
    uint8_t *dst = (uint8_t*)addr;
    send_byte((uint8_t)( w        & 0xFF), dst,other_d);
    send_byte((uint8_t)((w >> 8 ) & 0xFF), dst + 1,other_d);
    send_byte((uint8_t)((w >> 16) & 0xFF), dst + 2,other_d);
    send_byte((uint8_t)((w >> 24) & 0xFF), dst + 3,other_d);
}


void cl_eeprom_save_e(uint32_t w, uint32_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;

    eeprom_write_b((uint8_t)( w        & 0xFF), dst);
    eeprom_write_b((uint8_t)((w >> 8 ) & 0xFF), dst + 1);
    eeprom_write_b((uint8_t)((w >> 16) & 0xFF), dst + 2);
    eeprom_write_b((uint8_t)((w >> 24) & 0xFF), dst + 3);
}


void cl_eeprom_load_e(uint32_t *w, uint32_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    eeprom_read_b(&b0,src);
    eeprom_read_b(&b1,src + 1);
    eeprom_read_b(&b2,src + 2);
    eeprom_read_b(&b3,src + 3);
    *w =  (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
}

/*
void cl_sdk_load_gpio_e(cl_addr_t addr, cl_addr_t pin,void *port_char)
{
	uint32_t pin_val;
	switch(*(char *)port_char){
		case 'a':
		case 'A':
			pin_val = GPIO_PinRead(GPIOA,(cl_int_t)pin);
			break;
		case 'b':
		case 'B':
			pin_val = GPIO_PinRead(GPIOB,(cl_int_t)pin);
			break;
		case 'c':
		case 'C':
			pin_val = GPIO_PinRead(GPIOC,(cl_int_t)pin);
			break;
		case 'd':
		case 'D':
			pin_val = GPIO_PinRead(GPIOD,(cl_int_t)pin);
			break;
	}
	//PRINTF("\rValue that i read is %d\n",pin_val);
	*addr = pin_val;
}

void cl_sdk_save_gpio_e(cl_int_t val, cl_addr_t pin, void *port_char)
{
	//uint32_t val = *backup_addr;
	switch(*(char *)port_char){
			case 'a':
			case 'A':
				GPIO_PinWrite(GPIOA,(cl_int_t)pin, val);
				break;
			case 'b':
			case 'B':
				GPIO_PinWrite(GPIOB,(cl_int_t)pin,val);
				break;
			case 'c':
			case 'C':
				GPIO_PinWrite(GPIOC,(cl_int_t)pin,val);
				break;
			case 'd':
			case 'D':
				GPIO_PinWrite(GPIOD,(cl_int_t)pin,val);
				break;
		}
}
*/

void cl_sdk_load_gpio_e(cl_addr_t addr, cl_addr_t pin,void *port_char)
{

}
void cl_sdk_save_gpio_e(cl_int_t val, cl_addr_t pin, void *port_char)
{

}

void raw_save_dw(uint64_t dw, uint64_t *addr, void *not_used)
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
}

void raw_send_dw(uint64_t dw, uint64_t *addr, void *other_d)
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
}


void raw_load_B(uint8_t *B, uint8_t *addr, void *not_used)
{
   load_byte( B, addr);
}

void raw_rcv_B(uint8_t *B, uint8_t *addr, void *other_d)
{
   rcv_byte( B, addr,other_d);
}


void raw_load_hw(uint16_t *hw, uint16_t *addr, void *not_used)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    load_byte(&b0,src);
    load_byte(&b1,src + 1);
    *hw =  (uint16_t)b0 | ((uint16_t)b1 << 8);
}

void raw_rcv_hw(uint16_t *hw, uint16_t *addr, void *other_d)
{
    uint8_t *src = (uint8_t*)addr;
    uint8_t b0;
    uint8_t b1;
    rcv_byte(&b0,src,other_d);
    rcv_byte(&b1,src + 1,other_d);
    *hw =  (uint16_t)b0 | ((uint16_t)b1 << 8);
}


void raw_load_w(uint32_t *w, uint32_t *addr, void *not_used)
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
}

void raw_rcv_w(uint32_t *w, uint32_t *addr, void *other_d)
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
}


void raw_load_dw(uint64_t *dw, uint64_t *addr, void *not_used)
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
}

void raw_rcv_dw(uint64_t *dw, uint64_t *addr, void *other_d)
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
}

void a_save_e(uint64_t e, uint64_t *addr,void *not_used)
{
    uint64_t local_addr = (uint64_t)addr * 2 / 8;
    //printf("A: LOCAL ADDRESS: %ld\n",local_addr);
    if (local_addr > 32)
    {
        printf("a_save_e error: wrong address: %ld\n",local_addr);
        return;
    }
    A_MEM[local_addr + 10] = 0xaa;
    A_MEM[local_addr + 11] = e;
    return;
}
    
void a_load_e(uint64_t *e, uint64_t *addr, void *not_used)
{
    uint64_t local_addr = (uint64_t)addr * 2 / 8;
    //printf("A: LOCAL ADDRESS: %ld\n",local_addr);
    if (local_addr > 32)
    {
        printf("a_load_e error: wrong address: %ld\n",local_addr);
        return;
    }
    A_MEM[local_addr + 10] = 0x00;
    *e = A_MEM[local_addr + 11];
    return;
}


void b_save_e(uint64_t e, uint64_t *addr, void *not_used)
{
    uint64_t local_addr = (uint64_t)addr / 8 + 11;
    //printf("B: LOCAL ADDRESS: %ld\n",local_addr);
    if (local_addr < 11 || local_addr > 15)
    {
        printf("b_save_e error: wrong address: %ld\n",local_addr);
        return;
    }
    B_MEM[local_addr + 5] = 0xbb;
    B_MEM[local_addr - 5] = 0xbb;
    B_MEM[local_addr] = e;
    return;
}
    
void b_load_e(uint64_t *e, uint64_t *addr, void *not_used)
{
    uint64_t local_addr = (uint64_t)addr / 8 + 11;
    //printf("B: LOCAL ADDRESS: %ld\n",local_addr);
    if (local_addr < 11 || local_addr > 15)
    {
        printf("b_load_e error: wrong address: %ld\n",local_addr);
        return;
    }
    *e = B_MEM[local_addr];
    return;
}


// save element functions are chosen based on architecture size
#if ARCHITECTURE_BUS_SIZE == 8
void cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return raw_save_B(e,addr,not_used);
}
void raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d)
{
    return raw_send_B(e,addr,other_d);
}
void cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return raw_load_B(e,addr,not_used);
}
void cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d)
{
    return raw_rcv_B(e,addr,other_d);
}
#elif ARCHITECTURE_BUS_SIZE == 16
void cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return raw_save_hw(e,addr,not_used);
}
void cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d)
{
    return raw_send_hw(e,addr,other_d);
}
void cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return raw_load_hw(e,addr,not_used);
}
void cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d)
{
    return raw_rcv_hw(e,addr,other_d);
}
#elif ARCHITECTURE_BUS_SIZE == 32
void cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return raw_save_w(e,addr,not_used);
}
void cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d)
{
    return raw_send_w(e,addr,other_d);
}
void cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return raw_load_w(e,addr,not_used);
}
void cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d)
{
    return raw_rcv_w(e,addr,other_d);
}
#elif ARCHITECTURE_BUS_SIZE == 64
void cl_raw_save_e(cl_int_t e, cl_addr_t addr, void *not_used)
{
    return raw_save_dw(e,addr,not_used);
}
void cl_raw_send_e(cl_int_t e, cl_addr_t addr, void *other_d)
{
    return raw_send_dw(e,addr,other_d);
}
void cl_raw_load_e(cl_addr_t e, cl_addr_t addr, void *not_used)
{
    return raw_load_dw(e,addr,not_used);
}
void cl_raw_rcv_e(cl_addr_t e, cl_addr_t addr, void *other_d)
{
    return raw_rcv_dw(e,addr,other_d);
}
#endif
