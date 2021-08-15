#ifndef NS_H
#define NS_H
#include "config.h"
#include <X11/Xlib.h>

/*
 * determine separator using current index and length of components
 * used to ensure there is no extra separator at the end of the status
 */
#define DETR_SEP(i, complen) (i != complen - 1) ? ITEM_SEP : NULL

#define VERSION "1.1"

void xsetroot(Display* dpy, char* string);
void add_to_status(char* status, char* info, char* unit, char* sep);
int main(int argc, char** argv);

#endif
