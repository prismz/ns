#include "uptime.h"
#include "util.h"
#include "mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char*
get_uptime(void)
{
    char* fc = read_file("/proc/uptime");
    char* info = strtok(fc, " ");
    char* b;
    long uptime_sec = strtol(info, &b, 10);
    double hours = (double)((double)uptime_sec / 60) / 60;
    double mins = (double)(hours - floor(hours)) * 60;
    hours = floor(hours);
    mins = floor(mins);
    double days = (double)hours / 24;
    double hourem = (double)days - floor(days);
    hourem *= 24;
    days = floor(days);

    char* str = smalloc(sizeof(char) * 750);
    if (days > 1)
        snprintf(str, 750, "up %d days, %02d:%02d", (int)days, (int)hourem, (int)mins);
    else if (days == 1)
        snprintf(str, 750, "up %d day, %02d:%02d", (int)days, (int)hourem, (int)mins);
    else
        snprintf(str, 750, "up %02d:%02d", (int)hourem, (int)mins);

    free(fc);
    return str;
}