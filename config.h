#ifndef CONFIG_H
#define CONFIG_H

/* 
 * https://strftime.org 
 * (this is for Python, but should be the same for C.) 
 */
#define TIME_FORMAT "%A %B %d %I:%M:%S %p"
#define ENABLE_XORG  /* comment out if you don't have Xlib headers or won't be using the X root window name. */
#define ITEM_SEP " | "  /* separator between each item */

typedef enum {
    cmus_info,        /* cmus song and position */
    uptime_info,      /* uptime */
    loadavg_info,     /* load average */
    mem_info,         /* mem usage in MiB */
    statgen_info,     /* time taken to generate and set status */
    datetime_info     /* date and time according to TIME_FORMAT */
} component;

static component status_components[] = { 
    cmus_info, uptime_info, loadavg_info, mem_info, datetime_info };

#endif
