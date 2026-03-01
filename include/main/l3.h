#include "types.h"

#include "../../platform/posix/context_lib_port.h"

cl_int_t cl_area_on( cl_int_t id,void *custom_d);
cl_int_t cl_area_off( cl_int_t id,void *custom_d);

cl_int_t cl_protect_memory(cl_int_t id);
cl_int_t cl_unprotect_memory(cl_int_t id);
cl_int_t cl_change_mode(enum Cl_power_mode_t from_mode, enum Cl_power_mode_t to_mode,void *custom_d);

