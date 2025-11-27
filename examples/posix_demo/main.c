#include "../../include/main/context_manager.h"
#include "../../platform/posix/context_lib_port.h"

int main() {
    context_lib_port_setup();
    blink_led();
    context_lib_port_teardown();
    return 0;
}
