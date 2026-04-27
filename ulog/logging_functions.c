#include "ulog.h"

#ifdef ULOG_ENABLED  // whole file...

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
void console_log(ulog_level_t level,char *msg) {
  printf("[%s]\t%s\n",
  ulog_level_name(level),
  msg);
}
#endif  // #ifdef ULOG_ENABLED