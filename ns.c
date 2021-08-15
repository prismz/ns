#include "ns.h"
#include "util.h"
#include "mem.h"
#include "cmus.h"
#include "cpu.h"
#include "time.h"
#include "uptime.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xlib.h>

void
xsetroot(Display* dpy, char* string)
{
    if (XStoreName(dpy, DefaultRootWindow(dpy), string) < 0)
        die("error: XStoreName allocation failed.");
    
    XFlush(dpy);
}

void
add_to_status(char* status, char* info, char* unit, char* sep)
{
    if (info != NULL)
        strcat(status, info);
    else
        strcat(status, "?");
    if (unit != NULL)
        strcat(status, unit);
    if (sep != NULL)
        strcat(status, sep);
}

int
main(int argc, char** argv)
{
    int s = 0;  /* print to stdout */
    if (argc > 1 && strcmp(argv[1], "--version") && strcmp(argv[1], "-s")) {
        printf("usage: ns [--version] [-s(tdout)]\n");
        return 0;
    }
    if (argc > 1 && !strcmp(argv[1], "--version")) {
        printf("%s\n", VERSION);
        return 0;
    }
    if (argc > 1 && !strcmp(argv[1], "-s"))
        s = 1;

    double duration = 0.0;  /* time taken to generate and set status */
    Display* dpy;
    if (!s) 
        dpy = XOpenDisplay(NULL);
    if (!dpy && !s)
        die("error: could not open display.");

    char* status = smalloc(sizeof(char) * 4096);
    strcpy(status, "");
    while (1) {
        clock_t t = clock();

        int compl = ARRLEN(status_components);

        /* TODO: fix spaghetti */
        for (int i = 0; i < compl; i++) {

            if (status_components[i] == cmus_info) {
                char* cmus = get_cmus_status();
                if (strcmp(cmus, "not playing") && cmus != NULL)
                    add_to_status(status, cmus, NULL, DETR_SEP(i, compl));
                free(cmus);

            } else if (status_components[i] == uptime_info) {
                char* uptime = get_uptime();
                add_to_status(status, uptime, NULL, DETR_SEP(i, compl));
                free(uptime);

            } else if (status_components[i] == loadavg_info) {
                char* lavg = get_loadavg();
                add_to_status(status, lavg, NULL, DETR_SEP(i, compl));
                free(lavg);

            } else if (status_components[i] == mem_info) {
                char* mem = smalloc(sizeof(char) * 10);
                int imem = get_mem();
                snprintf(mem, 10, "%d", imem);
                add_to_status(status, mem, "MiB", DETR_SEP(i, compl));
                free(mem);

            } else if (status_components[i] == statgen_info) {
                char* str = smalloc(sizeof(char) * 20);
                snprintf(str, 20, "%fs", duration);
                add_to_status(status, str, NULL, DETR_SEP(i, compl));
                free(str);

            } else if (status_components[i] == datetime_info) {
                char* dtime = get_time();
                add_to_status(status, dtime, NULL, DETR_SEP(i, compl));
                free(dtime);
            }
        }

        if (s)
            printf("%s\n", status);
        else
            xsetroot(dpy, status);
        strcpy(status, "");
        t = clock() - t;
        duration = ((double)t) / CLOCKS_PER_SEC;
        sleep(1);

    }

    free(status);
    XCloseDisplay(dpy);
}