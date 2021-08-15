#include "time.h"
#include "util.h"
#include "mem.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char*
get_time(void)
{
    time_t rt;
    time(&rt);
    struct tm* tm = localtime(&rt);
    char* str = smalloc(sizeof(char) * 1024);
    strftime(str, 1024, TIME_FORMAT, tm);
    return str;
}