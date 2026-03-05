#ifndef INCLUDE_TYPES
#define INCLUDE_TYPES

/*! 
 * \file      types.h
 * \brief     Types and definitions for whole library.
 * \details   
 * Dependencies:
 * - <stdint.h>
 * All types defined and used in this library are directly derived from stdint types.
 * They usually use uint<BUS_SIZE>_t type.
 * - <stdbool.h>
 * Return types for success\failure type of functions
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \pre       Needs to include config.h with valid configuration declarations (TODO)
 */
#include <stdint.h>
#include <stdbool.h>


/*!
* \brief Bus size of CPU used in target mcu
* 
* Possible values are 8,16,32 or 64.
* Default value is 32 and this is also the only value for which
* the library have been extensively tested.
* \todo Move this into config.h file
*/
#define ARCHITECTURE_BUS_SIZE 64

/*! 
* \typedef cl_addr_t
* \brief Type used for addresses
* Simple pointer to unsigned integer with size of architecture bus.
* Most functions in this library use this type every time they work with addresses.
*  
*/

/*!
* \typedef cl_int_t
* \brief Type used for values
* Unsigned integer type with size of architecture bus.
* Arrays of this type are the main data type that this library works with.
*/

/*!
* \def CL_MAX_INT
* \brief Maximum integer size for bus size integer.
* It has minor usage in some function
* and is not very important.
*/

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


/* ========== L2 ==========
* TODO: this should only be included if L2 is enabled
*/

/*!
 * \struct Cl_memory_area_t
 * \brief Part of memory space with distinct role or technicalities.
 *
 * \details This structure is crucial for working with this library. It is
 * called by most of save and load functions and contains metadata necessary
 * for context storage. One variable with \a Cl_memory_area_t type describes
 * distinct array of values in memory. This area can be used to store both source
 * and destination space. Expected use cases are:
 * - array stored in RAM that is important to the user and should be protected when turning off memory
 * - globally defined array in well-protected part of memory that 
 *      serves as a storage place for important application/user data (E.g. register file)
 * - CPU or peripheral registers (provided they are mapped to subsequent addresses in memory)
 * - block of external memory with specific purpose
 * 
 * \details Expected way of defining new variables with this type is quite specific. Because library
 * is expected to work with power modes that regularly turn off parts of or entire RAM memory, it is
 * advised to define this variable \a globally and using \c const keyword to ensure its storage into 
 * non-volatile memory. More importantly, area itself doesn't allocate any space, so before its definition,
 * one should allocate space statically with array definition and create this variable using newly defined 
 * array.
 *
 * 
 * \note It's recommended to check \a platform\ or  \a examples\ folder for usage of this structure.
 * 
 * \todo add READ_WRITE_TYPE that is currently a parameter of L2 functions
 *
 */
typedef struct {
    cl_int_t id;          //! Area unique identifier used as a metadata when storing area
    cl_addr_t start_addr; //! First address of memory area
    cl_addr_t end_addr;   //! Last address of memory area
} Cl_memory_area_t;


/*!
 * \struct Cl_peripheral_area_t
 * \brief Set of addresses (supposedly registers) with distinct role or technicalities.
 *
 * \details Structure is similar to \c Cl_memory_area_t but instead of one continuous block
 * of addresses, it instead represents set of generic addresses. Its main purpose will supposedly be
 * description of CPU or peripheral registers. This area cannot be used as a destination of storage 
 * process.
 *
 * 
 * \note Check \c Cl_memory_area_t documentation for more info. Check examples in \a platform\ and \a examples\ folders
 * 
 * \todo add READ_WRITE_TYPE that is currently a parameter of L2 and L3 functions
 *
 */
typedef struct {
    cl_int_t id;
    cl_int_t addr_num;
    cl_addr_t addresses[];
} Cl_peripheral_area_t;

/*!
* \brief Type of the function used for saving one data element. 
*
* It generalizes saving for different
* element bit sizes and using different strategies (basically RAM write vs specialized function) 
* \param source one value that is to be saved
* \param target address, where value will be saved
* \param custom_d pointer to (presumably) structure that contains any metadata needed for correct 
*  data transfer using special function
*/
typedef cl_int_t (*cl_save_f_t)(cl_int_t source, cl_addr_t target, void *custom_d);

/*!
* \brief Type of the function used for loading one data element. 
*
* It generalizes loading for different
* element bit sizes and using different strategies (basically RAM write vs specialized function) 
* \param target address where data will be loaded
* \param source address, from which data will be loaded
* \param custom_d pointer to (presumably) structure that contains any metadata needed for correct 
*  data transfer using special function
*/
typedef cl_int_t (*cl_load_f_t)(cl_addr_t target, cl_addr_t source, void *custom_d);


/*!
* \brief Low-level way of storing/loading bytes  
*
* Chooses which low-level function will be used for data storage or loading
* \todo This should be refactored: SEND and CUSTOM_SEND merged and name should be
* changed as this is used for both save and load
* \todo Port creator or user should probably have option to expand this enum.
*/
enum Bare_save_type{ RAM_WRITE, SEND, CUSTOM_SEND};



/* =========== L3 
* TODO: only when L3 is turned on
*/

/*!
* \brief MCU-specific power modes
*
* This list should contain all relevant power modes 
* specific for target microcontroller. Memory areas 
* are mapped to these modes which determines if they 
* are turned on or off. 
* \warning This is the only line of code outside \a context_lib_port.c
* that needs to be implemented by port creator.
* \note Example(default option):
* enum Cl_power_mode_t{RUN,SLEEP,STOP,LLS,VLLS0,VLLS1,VLLS2,VLLS3};
*/
enum Cl_power_mode_t{RUN, SLEEP, STOP, VLLS, VLLS0};


/*!
* \brief State of memory area in power mode
*
* Simple enumeration used in table mapping memory areas to power modes.
* Area is either turned on, off or it can be turned on/off independendly
* of this particular power mode( \c BOTH_VALID option)
*/
enum Cl_memory_state{ON,OFF,BOTH_VALID};

/*!
* \brief For individual power modes determines which parts of address space are turned
* off. 
* \note One table of this type should be implemented by the port creator ( \c area_mode_table )
*/
struct area_in_mode {
    cl_addr_t start_address;
    cl_addr_t end_address;
    enum Cl_power_mode_t mode;
    enum Cl_memory_state state;
};

/*!
* \brief Area to be protected mapped to area where it should be saved
*
* Every memory area that contains data to be protected should be mapped onto 
* one other, better protected area. It will be saved into this area
* \note \c backup_area should generally be bigger than \c area as 
* some metadata are also saved
* \note Saving areas is recursive: if A is mapped onto B and B is mapped onto C,
* context from A will be saved into C if A and B is turned off at once.
*/
struct area_backup {
    const Cl_memory_area_t *area;
    const Cl_memory_area_t *backup_area;
};

/*!
* \brief Peripheral to be protected mapped to area where it should be saved
*
* Every peripheral area that contains data to be protected should be mapped onto 
* some better protected area. It will be saved into this area
* \note \c backup_area should generally be bigger than \c area as 
* some metadata are also saved
* \note Saving areas is recursive: if A is mapped onto B and B is mapped onto C,
* context from A will be saved into C if A and B is turned off at once.
*/
struct peripheral_backup {
    const Cl_peripheral_area_t *area;
    const Cl_memory_area_t *backup_area;
};

extern const cl_int_t memory_areas_table_size;  
/*!
* \note Refer to \c platform/posix/context_lib_port.c for informations
*/
extern const Cl_memory_area_t *memory_areas[];

extern const cl_int_t peripheral_areas_table_size;
/*!
* \note Refer to \c platform/posix/context_lib_port.c for informations
*/
extern const Cl_peripheral_area_t *peripheral_areas[];

extern const cl_int_t  area_mode_table_size;
/*!
* \note Refer to \c platform/posix/context_lib_port.c for informations
*/
extern const struct area_in_mode area_mode_table[];

extern const cl_int_t area_backup_table_size;
/*!
* \note Refer to \c platform/posix/context_lib_port.c for informations
*/
extern const struct area_backup area_backup_table[];

extern const cl_int_t peripheral_backup_table_size;
/*!
* \note Refer to \c platform/posix/context_lib_port.c for informations
*/
extern const struct peripheral_backup peripheral_backup_table[];

#endif