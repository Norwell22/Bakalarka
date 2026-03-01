#ifndef INCLUDE_TYPES
#define INCLUDE_TYPES

#include <stdint.h>
#include <stdbool.h>


// 8 or 16 or 32 or 64
#define ARCHITECTURE_BUS_SIZE 64


#if ARCHITECTURE_BUS_SIZE == 8
typedef uint8_t *cl_addr_t;
typedef uint8_t cl_int_t;
#define CL_MAX_INT UINT8_MAX
#elif ARCHITECTURE_BUS_SIZE == 16
typedef uint16_t *cl_addr_t;
typedef uint16_t cl_int_t;
#define CL_MAX_INT UINT16_MAX
#elif ARCHITECTURE_BUS_SIZE == 32
typedef uint32_t *cl_addr_t;
typedef uint32_t cl_int_t;
#define CL_MAX_INT UINT32_MAX
#elif ARCHITECTURE_BUS_SIZE == 64
typedef uint64_t *cl_addr_t;
typedef uint64_t cl_int_t;
#define CL_MAX_INT UINT64_MAX
#endif


typedef struct {
    cl_int_t id;
    cl_addr_t start_addr;
    cl_addr_t end_addr;
} Cl_memory_area_t;

typedef struct {
    cl_int_t id;
    cl_int_t addr_num;
    cl_addr_t addresses[];
} Cl_peripheral_area_t;


typedef cl_int_t (*cl_save_f_t)(cl_int_t, cl_addr_t, void *);
typedef cl_int_t (*cl_load_f_t)(cl_addr_t, cl_addr_t, void *);


// TODO: do this more inteligent
enum Bare_save_type{ RAM_WRITE, SEND, CUSTOM_SEND};


extern const Cl_memory_area_t *memory_areas[];

// WARNING: this depends on port heavily
enum Cl_power_mode_t{RUN, SLEEP, STOP, VLLS};

enum Cl_memory_state{ON,OFF,BOTH_VALID};
// enum Cl_power_mode_t{RUN,SLEEP,STOP,VLLS};

struct area_in_mode {
    cl_addr_t start_address;
    cl_addr_t end_address;
    enum Cl_power_mode_t mode;
    enum Cl_memory_state state;
};

struct area_backup {
    const Cl_memory_area_t *area;
    const Cl_memory_area_t *backup_area;
};

extern const cl_int_t memory_areas_table_size;
extern const Cl_memory_area_t *memory_areas[];

extern const cl_int_t  area_mode_table_size;
extern const struct area_in_mode area_mode_table[];

extern const cl_int_t area_backup_table_size;
extern const struct area_backup area_backup_table[];

#endif