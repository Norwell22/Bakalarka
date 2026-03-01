// #include "../../platform/posix/context_lib_port.h" now directly included in context_manager.h
#include <stdio.h>
// #include "../../platform/posix/context_lib_port.h"
#include "../../include/main/context_manager.h"
#include "use_cases.h"


/*
@NOTE
__attribute__((section(".hram_section"))) uint8_t buffer[1024]
*/





int main() {
    use_case1();
    return 0;
}
