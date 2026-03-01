

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
