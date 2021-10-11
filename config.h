#ifndef CONFIG_H
#define CONFIG_H

/* 
 * https://strftime.org 
 * (this is for Python, but should be the same for C.) 
 */
#define TIME_FORMAT "%A %B %d %I:%M:%S %p"
#define ITEM_SEP " | "  /* separator between each item */

typedef enum {
    cmus_info,        /* cmus song and position */
    uptime_info,      /* uptime */
    loadavg_info,     /* load average */
    mem_info,         /* mem usage in MiB */
    statgen_info,     /* time taken to generate and set status */
    datetime_info,    /* date and time according to TIME_FORMAT */
    disk_free,        /* free space on main disk */
    portage_installed /* amount of packages installed with gentoo's package manager */
} component;

static const component status_components[] = { 
    cmus_info, portage_installed, disk_free, uptime_info, loadavg_info, mem_info, datetime_info };

#endif
