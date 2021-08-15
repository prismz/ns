#include "uptime.h"
#include "util.h"
#include "mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

char*
get_uptime(void)
{
    char* fc = read_file("/proc/uptime");
    char* info = strtok(fc, " ");
    char* b;

    long uptime_sec = strtol(info, &b, 10);

    int secs_in_hr = 60 * 60;

    int hours = (uptime_sec / secs_in_hr);
    int days = hours / 24;
    int rem_sec = uptime_sec - (hours * secs_in_hr);
    int mins = rem_sec / 60;
    hours = (hours - (24 * days));   

    char* str = smalloc(sizeof(char) * 750);
    if (days > 1)
        snprintf(str, 750, "up %d days, %02d:%02d", days, hours, mins);
    else if (days == 1)
        snprintf(str, 750, "up %d day, %02d:%02d", days, hours, mins);
    else
        snprintf(str, 750, "up %02d:%02d", hours, mins);

    free(fc);
    return str;
}
