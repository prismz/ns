#include "cpu.h"
#include "util.h"
#include "mem.h"

#include <string.h>

char*
get_loadavg(void)
{
    char* fc = read_file("/proc/loadavg");
    if (fc == NULL)
        return NULL;

    char* s = strtok(fc, " ");
    char* s_c = smalloc(strlen(s) + 1);
    strcpy(s_c, s);

    free(fc);

    return s_c;
}