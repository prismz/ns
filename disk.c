#include "disk.h"
#include "mem.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/statvfs.h>

char*
get_free_disk_space(void)
{
    struct statvfs sv;
    int rc = statvfs("/", &sv);

    if (rc != 0)
        return NULL;

    size_t bfree = (size_t)sv.f_bavail;

    /* lots of rounding for precise number */
    double gb = ((double)(bfree * sv.f_bsize) / (double)1024);
    gb = gb / (double)1024;
    gb = round(gb / (double)1024);

    char* buff = smalloc(sizeof(char) * 20);
    snprintf(buff, 20, "%d", (int)gb);
    
    return buff;
}

