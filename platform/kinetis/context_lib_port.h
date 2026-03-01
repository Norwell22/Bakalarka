
#define BACKUP_MEM_PTR ( (int *) 0x40041000 ) //register file
#define BACKUP_MEM_SIZE 32  //size in bytes


void context_lib_port_setup();

void platform_toggle_led();

void context_lib_port_teardown();