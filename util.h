#ifndef UTIL_H
#define UTIL_H

#define ARRLEN(x) sizeof(x) / sizeof(x[0])

void die(char* msg);
int strstw(char* needle, char* haystack);
char* strfsec(int sec);
char* read_file(char* file_name);

#endif