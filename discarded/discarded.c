/*! 
 * \file      discarded.c
 * \brief     Functions written but at the end not used
 * \details   
 * Contains set of \a save \a array functions that were not used
 * because more complex versions of them are part of second layer of this
 * library
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \todo Get rid of this file
 */

/*
from l1_public.c, functions for saving and loading arrays. 
probably won't be necessary, as saving and loading of arrays is generally a bit complex
    and I don't have any use for them
*/
uint32_t cl_raw_save_arr_B(uint8_t *data, uint8_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data)
{
   uint32_t (*save_f)(uint8_t, uint8_t *,void *);
   switch (save_type) {
      case RAM_WRITE:
         save_f = cl_raw_save_B;
         break;
      case SEND:
         save_f = cl_raw_send_B;
         break;
      case CUSTOM_SEND:
         save_f = cl_raw_send_B;
   }

   uint32_t i;
   for (i = 0; i < arr_size; i++){
         save_f( *(data + i), addr + i,custom_other_data);
   }
   return 0;
}


uint32_t cl_raw_save_arr_hw(uint16_t *data, uint16_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data)
{
   uint32_t (*save_f)(uint16_t, uint16_t *,void *);
   switch (save_type) {
      case RAM_WRITE:
         save_f = cl_raw_save_hw;
         break;
      case SEND:
         save_f = cl_raw_send_hw;
         break;
      case CUSTOM_SEND:
         save_f = cl_raw_send_hw;
   }

   uint32_t i;
   for (i = 0; i < arr_size; i++){
      save_f(*(data + i), addr + i, custom_other_data);
   }
   return 0;
}

uint32_t cl_raw_save_arr_w(uint32_t *data, uint32_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data)
{
   uint32_t (*save_f)(uint32_t, uint32_t *,void *);
   switch (save_type) {
      case RAM_WRITE:
         save_f = cl_raw_save_w;
         break;
      case SEND:
         save_f = cl_raw_send_w;
         break;
      case CUSTOM_SEND:
         save_f = cl_raw_send_w;
   }
   uint32_t i;
   for (i = 0; i < arr_size; i++){
      save_f(*(data + i), addr + i,custom_other_data);
   }
   return 0;
}


uint32_t cl_raw_load_arr_B(uint8_t *buffer, uint8_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data)
{
   uint32_t (*load_f)(uint8_t *, uint8_t *,void *);
   switch (save_type) {
      case RAM_WRITE:
         load_f = cl_raw_load_B;
         break;
      case SEND:
         load_f = cl_raw_rcv_B;
         break;
      case CUSTOM_SEND:
         load_f = cl_raw_custom_rcv_B;
   }
   uint32_t i;
   for (i = 0; i < arr_size; i++){
      load_f(buffer + i, addr + i,custom_other_data);
   }
   return 0;
}


uint32_t cl_raw_load_arr_hw(uint16_t *buffer, uint16_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data)
{
   uint32_t (*load_f)(uint16_t *, uint16_t *,void *);
   switch (save_type) {
      case RAM_WRITE:
         load_f = cl_raw_load_hw;
         break;
      case SEND:
         load_f = cl_raw_rcv_hw;
         break;
      case CUSTOM_SEND:
         load_f = cl_raw_custom_rcv_hw;
   }

   uint32_t i;
   for (i = 0; i < arr_size; i++){
      load_f(buffer + i, addr + i, custom_other_data);
   }
   return 0;
}


uint32_t cl_raw_load_arr_w(uint32_t *buffer, uint32_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data)
{
   uint32_t (*load_f)(uint32_t *, uint32_t *,void *);
   switch (save_type) {
      case RAM_WRITE:
         load_f = cl_raw_load_w;
         break;
      case SEND:
         load_f = cl_raw_rcv_w;
         break;
      case CUSTOM_SEND:
         load_f = cl_raw_custom_rcv_w;
   }

   uint32_t i;
   for (i = 0; i < arr_size; i++){
      load_f(buffer + i, addr + i, custom_other_data);
   }
   return 0;
}


/* Old posix context_lib_port.c */

/*
* Layer 3 metadata
*/

/*!
 * \brief Implement this enumeration in \c types.h
 *
 * \code
 * enum Cl_power_mode_t { RUN, SLEEP, STOP, LLS, VLLS0, VLLS1, VLLS2, VLLS3 };
 * \endcode
 */


const cl_int_t memory_areas_table_size = 12;
const Cl_memory_area_t *memory_areas[] = {&ma255,&ma1,&ma2,&ma10,&ma11,&ma12,&ma100,&ma101,&ma102,&ma103,
        &ma104,&ma105};

const cl_int_t peripheral_areas_table_size = 5;
const Cl_peripheral_area_t *peripheral_areas[] = {&ma200,&ma201,&ma202,&ma203,&ma204};

const cl_int_t area_mode_table_size = 8;
const struct area_in_mode area_mode_table[] = {
    {LRAM, LRAM + 1023, RUN, ON},
    {LRAM, LRAM + 1023, SLEEP, ON},
    {LRAM, LRAM + 1023, STOP, ON},
    {LRAM, LRAM + 1023, VLLS, OFF},
    {LRAM, LRAM + 1023, VLLS0, OFF},

    {HRAM, HRAM + 1023, RUN, ON},
    {HRAM, HRAM + 1023, SLEEP, ON},
    {HRAM, HRAM + 1023, STOP, OFF},
    {HRAM, HRAM + 1023, VLLS, OFF},
    {HRAM, HRAM + 1023, VLLS0, OFF},

    {REGISTER_FILE, REGISTER_FILE + 127,RUN,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,SLEEP,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,STOP,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,VLLS,ON},
    {REGISTER_FILE, REGISTER_FILE + 127,VLLS0,OFF},

    {REGISTER_FILE2, REGISTER_FILE2 + 255,RUN,ON},
    {REGISTER_FILE2, REGISTER_FILE2 + 255,SLEEP,ON},
    {REGISTER_FILE2, REGISTER_FILE2 + 255,STOP,ON},
    {REGISTER_FILE2, REGISTER_FILE2 + 255,VLLS,ON},
    {REGISTER_FILE2, REGISTER_FILE2 + 255,VLLS0,ON},

    {OUTSIDE1,OUTSIDE1 + 255, RUN, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, SLEEP, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, STOP, BOTH_VALID},
    {OUTSIDE1,OUTSIDE1 + 255, VLLS, BOTH_VALID},

    {OUTSIDE2,OUTSIDE2 + 255, RUN, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, SLEEP, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, STOP, BOTH_VALID},
    {OUTSIDE2,OUTSIDE2 + 255, VLLS, BOTH_VALID},

    {UART0_REGS, UART0_REGS + 7, RUN, BOTH_VALID},
    {UART0_REGS, UART0_REGS + 7, SLEEP, BOTH_VALID},
    {UART0_REGS, UART0_REGS + 7, STOP, OFF},
    {UART0_REGS, UART0_REGS + 7, VLLS, OFF},

    {SPI0_REGS, SPI0_REGS + 5, RUN, BOTH_VALID},
    {SPI0_REGS, SPI0_REGS + 5, SLEEP, BOTH_VALID},
    {SPI0_REGS, SPI0_REGS + 5, STOP, OFF},
    {SPI0_REGS, SPI0_REGS + 5, VLLS, OFF},

    {I2C0_REGS, I2C0_REGS + 5, RUN, BOTH_VALID},
    {I2C0_REGS, I2C0_REGS + 5, SLEEP, BOTH_VALID},
    {I2C0_REGS, I2C0_REGS + 5, STOP, OFF},
    {I2C0_REGS, I2C0_REGS + 5, VLLS, OFF},

    {TIMER0_REGS, TIMER0_REGS + 9, RUN, BOTH_VALID},
    {TIMER0_REGS, TIMER0_REGS + 9, SLEEP, BOTH_VALID},
    {TIMER0_REGS, TIMER0_REGS + 9, STOP, OFF},
    {TIMER0_REGS, TIMER0_REGS + 9, VLLS, OFF},

    {GPIO_REGS, GPIO_REGS + 15, RUN, BOTH_VALID},
    {GPIO_REGS, GPIO_REGS + 15, SLEEP, BOTH_VALID},
    {GPIO_REGS, GPIO_REGS + 15, STOP, OFF},
    {GPIO_REGS, GPIO_REGS + 15, VLLS, OFF}
};


const cl_int_t area_backup_table_size = 10;
const struct area_backup area_backup_table[] = {
    {&ma255,&ma1},{&ma10,&ma1},{&ma11,&ma1},
    {&ma100,&ma10},{&ma101,&ma10},{&ma102,&ma10},
    {&ma103,&ma10},{&ma104,&ma10},{&ma105,&ma10},
    {&ma1,&ma2}
};

const cl_int_t peripheral_backup_table_size = 5;
const struct peripheral_backup peripheral_backup_table[] = {
    {&ma200,&ma10},{&ma201,&ma10},{&ma202,&ma10},{&ma203,&ma11},
    {&ma204,&ma11}
};

/*
TODO: either delete or use this somehow
cl_int_t cl_bare_save(cl_addr_t data, cl_addr_t addr, cl_int_t byte_size, enum Bare_save_type save_type, void *custom_other_data);
cl_int_t cl_bare_load(cl_addr_t buffer, cl_addr_t addr, cl_int_t byte_size, enum Bare_save_type load_type, void *custom_other_data); 
uint32_t cl_raw_save_arr_B(uint8_t *data, uint8_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_save_arr_hw(uint16_t *data, uint16_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_save_arr_w(uint32_t *data, uint32_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_B(uint8_t *buffer, uint8_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_hw(uint16_t *buffer, uint16_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
uint32_t cl_raw_load_arr_w(uint32_t *buffer, uint32_t *addr, uint32_t arr_size, enum Bare_save_type save_type, void *custom_other_data);
*/