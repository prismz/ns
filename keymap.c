#include "keymap.h"
#include "mem.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>

int
valid_layout(char* str)
{
    char* invalid[] = { "evdev", "pc", "inet", "base" };
    for (size_t i = 0; i < ARRLEN(invalid); i++) {
        if (!strncmp(str, invalid[i], strlen(invalid[i])))
            return 0;
    }

    return 1;
}

char*
get_keymap(void)
{
    Display* dpy;
    XkbDescRec* desc;
    XkbStateRec state;
    char* symbols;
    char* layout = NULL;

    if (!(dpy = XOpenDisplay(NULL)))
        return NULL;
    if (!(desc = XkbAllocKeyboard()))
        goto end;
    if (XkbGetNames(dpy, XkbSymbolsNameMask, desc))
        goto end;
    if (XkbGetState(dpy, XkbUseCoreKbd, &state))
        goto end;
    if (!(symbols = XGetAtomName(dpy, desc->names->symbols)))
        goto end;

    char* ptr = strtok(symbols, "+:");
    for (int g = 0; ptr && g <= state.group; ptr = strtok(NULL, "+:")) {
        if (!valid_layout(ptr))
            continue;
        else if (strlen(ptr) == 1 && ISNUM(ptr[0]))
            continue;
       
        if (layout != NULL)
            free(layout);
        layout = strdup(ptr);
        g++;
    }
    free(symbols);

end:
    XkbFreeKeyboard(desc, XkbSymbolsNameMask, 1);
    if (XCloseDisplay(dpy))
        return NULL;

    return layout;
}
