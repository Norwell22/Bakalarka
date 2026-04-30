#include "context_lib_port.h"
/*! 
 * \file      context_lib_port.c
 * \brief     Structures containing device-specific metadata and functions
 * \details   
 * Implementation of everything declared in \c context_lib_port.h. This file
 * is very important as an example and documentation for the person writing 
 * port of this library to new platform.
 * Dependencies:
 * - "context_lib_port.h"
 * 
 * \author    Michal Zidzik
 * \date      02.03.2026
 */


// implement this function in any way that's helpful to you. Use other_d pointer freely
uint32_t send_byte(uint8_t b, uint8_t *addr,void *other_d)
{
    puts("ERROR: context_lib_port.c/send_byte was not implemented and therefore does nothing. Returning 1");
    return 1;
}


uint32_t rcv_byte(uint8_t *b, uint8_t *addr,void *other_d)
{
    puts("ERROR: context_lib_port.c/rcv_byte was not implemented and therefore does nothing. Returning 1");
    return 1;
}

// replace with memory areas that you actually want to use
cl_int_t MEMORY_ARR1[100];
cl_int_t MEMORY_ARR2[100];
const cl_addr_t reg_addr1 = (cl_addr_t)0xaaa00;
const cl_addr_t reg_addr2 = (cl_addr_t)0xaaa04;
const cl_addr_t reg_addr3 = (cl_addr_t)0xaaa08;

// size is 8 for 32-bit architecture, 5 for 64-bit architecture
const Cl_memory_area_t cl_metadata_ma = {255,MEMORY_ARR1,MEMORY_ARR1 + 7,CL_CPU};
const Cl_memory_area_t memory_area_example1 = {1,MEMORY_ARR1 + 10,MEMORY_ARR1 + 30,CL_CPU};
const Cl_memory_area_t memory_area_example2 = {2,MEMORY_ARR2,MEMORY_ARR2 + 50,CL_CPU};
const Cl_peripheral_area_t peripheral_area_example1 = {200, 3,CL_CPU,
    {
        reg_addr1,
        reg_addr2,
        reg_addr3,
    }
};


/*
* Layer 3 metadata
*/

#ifdef CL_ALLOW_L3

/*!
 * \note There is enumeration type in \c include\types.h containing following power modes. If you want to add more,
 * do so in that file. 
 *
 * \code
 * enum Cl_power_mode_t { CL_RUN, CL_SLEEP, CL_STOP, CL_LLS, CL_VLLS0, CL_VLLS1, CL_VLLS2, CL_VLLS3 };
 * \endcode
 */

// memory area example 1 will be saved into memory area example 2
const cl_int_t cl_area_backup_table_size = 1;
struct cl_area_backup cl_area_backup_table[] = {
    {&memory_area_example1, &memory_area_example2,CL_RUN,true}
};

// peripheral area example 1 will be saved into memory area example 2
const cl_int_t cl_peripheral_backup_table_size = 1;
const struct cl_peripheral_backup cl_peripheral_backup_table[] = {
    {&peripheral_area_example1,&memory_area_example2,CL_RUN,true}
};

/*
won't work because of missing MCUXpresso enviroment
#include "cl_layer1.h"
#include "ulog.h"
#include "fsl_i2c.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
*/

void eeprom_write_b(uint8_t byte, uint8_t *addr) {
/*
    i2c_master_transfer_t masterXfer = {0};

    masterXfer.slaveAddress   = 0x50;
    masterXfer.direction      = kI2C_Write;
    masterXfer.subaddress     = (uint8_t)addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = &byte;
    masterXfer.dataSize       = 1;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    (void)I2C_MasterTransferBlocking(I2C1, &masterXfer);

    SDK_DelayAtLeastUs(5000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
*/
}

void eeprom_read_b(uint8_t *byte, uint8_t *addr) {
/*
    i2c_master_transfer_t masterXfer = {0};

    masterXfer.slaveAddress   = 0x50;
    masterXfer.direction      = kI2C_Read;
    masterXfer.subaddress     = (uint8_t)addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = byte;
    masterXfer.dataSize       = 1;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    (void)I2C_MasterTransferBlocking(I2C1, &masterXfer);
*/
}

void cl_sdk_load_gpio_e(cl_addr_t addr, cl_addr_t pin,void *port_char)
{
    /*
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
    */
}

void cl_sdk_save_gpio_e(cl_int_t val, cl_addr_t pin, void *port_char)
{
    /*
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
    */
}

void cl_eeprom_save_e(cl_int_t w, cl_int_t *addr, void *not_used)
{
    uint8_t *dst = (uint8_t*)addr;

    eeprom_write_b((uint8_t)( w        & 0xFF), dst);
    eeprom_write_b((uint8_t)((w >> 8 ) & 0xFF), dst + 1);
    eeprom_write_b((uint8_t)((w >> 16) & 0xFF), dst + 2);
    eeprom_write_b((uint8_t)((w >> 24) & 0xFF), dst + 3);
}


void cl_eeprom_load_e(cl_int_t *w, cl_int_t *addr, void *not_used)
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


#endif