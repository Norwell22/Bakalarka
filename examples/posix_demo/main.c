/*! 
 * \file      main.c
 * \brief     Simple file for library testing
 * \details   
 * Dependencies:
 - "../../include/main/context_manager.h"
 - "use_cases.h"
 * Helper file used for developing and testing general version of this library
 * \author    Michal Zidzik
 * \date      02.03.2026
 * \pre       Needs to include config.h with valid configuration declarations (TODO)
 * \note __attribute__((section(".hram_section"))) uint8_t buffer[1024]
 */
#include "context_manager.h"
#include "tests_helper.h"


int main() {
    cl_init();
    lram_clear();
    cl_clear_mem_area(ma10,NULL); 
    return 0;
}
