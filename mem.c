#include "mem.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void*
smalloc(size_t size)
{
    void* m = malloc(size);
    if (m == NULL)
        die("error: malloc() failed.");
    
    return m;
}

void*
srealloc(void* ptr, size_t size)
{
    void* m = realloc(ptr, size);
    if (m == NULL)
        die("error: realloc() failed.");
    
    return m;
}

int
get_mem(void)
{
    int mtotal = 0, mfree = 0, mbuffers = 0, mcache = 0, msreclaimable = 0;
    int stotal = 0, sfree = 0;

    FILE* fp = fopen("/proc/meminfo", "rb");
    if (!fp)
        return 0;
    
    char* cb = smalloc(sizeof(char) * 1024);
    char* cb_cpy = smalloc(sizeof(char) * 1024);
    strcpy(cb, "");
    strcpy(cb_cpy, "");
    while (fgets(cb, 1024, fp) != NULL) {
        strcpy(cb_cpy, cb);
        char* ptr = strtok(cb_cpy, " ");
        ptr = strtok(NULL, " ");
        if (ptr[strlen(ptr) - 1] == '\n')
            ptr[strlen(ptr) - 1] = '\0';

        char* b;
        int val = (int)strtol(ptr, &b, 10);
        
        if (strstw("MemTotal:", cb)) {
            mtotal = val;
        } else if (strstw("MemFree:", cb)) {
            mfree = val;
        } else if (strstw("Buffers:", cb)) {
            mbuffers = val;
        } else if (strstw("Cached:", cb)) {
            mcache = val;
        } else if (strstw("SwapTotal:", cb)) {
            stotal = val;
        } else if (strstw("SwapFree:", cb)) {
            sfree = val;
        } else if (strstw("SReclaimable:", cb)) {
            msreclaimable = val;
        }
    }

    int used = mtotal + stotal - mfree - sfree - mbuffers - mcache - msreclaimable;
    used = (int)round(used / 1024);

    fclose(fp);
    free(cb);
    free(cb_cpy);
    return used;
}