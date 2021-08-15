#include "util.h"
#include "mem.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

void
die(char* msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int
strstw(char* needle, char* haystack)
{
    if (!strncmp(haystack, needle, strlen(needle)))
        return 1;
    return 0;
}

char*
strfsec(int sec)
{
    char* str = smalloc(500);
    double minr = (double)sec / 60;
    double secr = minr - floor(minr);
    secr *= 60;
    snprintf(str, 500, "%02d:%02d", (int)floor(minr), (int)round(secr));;
    return str;

}

char*
read_file(char* file_name)
{
    FILE* fp = fopen(file_name, "rb");
    if (!fp)
        return NULL;

    size_t copied = 0;
    size_t fb_size = 2048;
    char* fb = smalloc(sizeof(char) * 2048);
    strcpy(fb, "");
    char* cb = smalloc(sizeof(char) * 1024);
    while (fgets(cb, 1024, fp) != NULL) {
        size_t cb_sz = sizeof(cb);
        if (copied + cb_sz > fb_size)
            fb = srealloc(fb, fb_size *= 2);

        strcat(fb, cb);
        copied += cb_sz;
    }
    fclose(fp);
    free(cb);
    return fb;
}