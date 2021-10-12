#include "cmus.h"
#include "util.h"
#include "mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*
split_attr(void* line)
{
    char* str = smalloc(strlen(line) + 1);
    strcpy(str, line);
    char* ptr = strtok(str, " ");
    ptr = strtok(NULL, " ");
    char* nptr = smalloc(strlen(ptr) + 1);
    strcpy(nptr, ptr);
    free(str);

    return nptr;
}

char*
get_cmus_status(void)
{
    FILE* fp = popen("cmus-remote -Q 2> /dev/null", "r");
    if (!fp)
        return NULL;

    char* filen = smalloc(1024);
    int position = 0;
    int duration = 0;

    int duration_set = 0, position_set = 0, file_set = 0, playing = 0;

    char* cb = smalloc(2048);
    while (fgets(cb, 2048, fp) != NULL) {
        if (strstw("file", cb)) {
            int c_i = 0;
            for (int i = 5; (size_t)i < strlen(cb) - 1; i++) {
                char c = cb[i];
                if (c == '/') {
                    c_i = 0;
                    strcpy(filen, "");
                } else if (c != '\n') {
                    filen[c_i] = c;
                    c_i++;
                }
            }
            filen[c_i] = '\0';
            file_set = 1;
        } else if (strstw("duration", cb)) {
            char* rem = split_attr(cb);
            char* b;
            duration = (int)strtol(rem, &b, 10);

            free(rem);
            duration_set = 1;
        } else if (strstw("position", cb)) {
            char* rem = split_attr(cb);
            char* b;
            position = (int)strtol(rem, &b, 10);

            free(rem);
            position_set = 1;
        } else if (strstw("status", cb)) {
            if (strstr(cb, "playing"))
                playing = 1;
        }
    }

    fclose(fp);
    free(cb);
    char* cmus_status;
    if (duration_set && position_set && file_set) {
        char* fmt_dur = strfsec(duration);
        char* fmt_pos = strfsec(position);

        size_t cmus_status_sz = strlen(fmt_dur) + strlen(fmt_pos) + strlen(filen) + 20;
        cmus_status = smalloc(cmus_status_sz);
        snprintf(cmus_status, cmus_status_sz, "%s %s / %s - %s", (playing) ? "play" : "pause", fmt_pos, fmt_dur, filen);

        free(fmt_dur);
        free(fmt_pos);
    } else {
        cmus_status = smalloc(sizeof(char) * 13);
        strcpy(cmus_status, "not playing");
    }

    free(filen);
    return cmus_status;
}
