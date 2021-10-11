#include "portage.h"
#include "util.h"
#include "mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

char*
get_portage_installed(void)
{
    size_t c = 0;
    struct dirent* ent;
    DIR* dir = opendir("/var/db/pkg");
    if (!dir)
        return NULL;

    while ((ent = readdir(dir)) != NULL) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;

        char* p = smalloc(strlen(ent->d_name) + 50);
        snprintf(p, strlen(ent->d_name) + 50, "/var/db/pkg/%s", ent->d_name);

        struct dirent* e2;
        DIR* d2 = opendir(p);
        if (!d2) {
            free(p);
            return NULL;
        }

        while ((e2 = readdir(d2)) != NULL) {
            if (!strcmp(e2->d_name, ".") || !strcmp(e2->d_name, ".."))
                continue;
            c++;
        }

        closedir(d2);
        free(p);
    }

    closedir(dir);

    char* ret = smalloc(sizeof(char) * 512);
    snprintf(ret, 512, "%zu", c);
    return ret;
}
