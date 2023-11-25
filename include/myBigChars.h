#pragma once

#include <myTerm.h>

#define ENTER_ALT_CHARSER_MODE "\E(0"
#define EXIT_ALT_CHARSER_MODE "\E(B"
#define ACS_CKBOARD "a"
#define ACS_HLINE "q"
#define ACS_VLINE "x"
#define ACS_LLCORNER "m"
#define ACS_LRCORNER "j"
#define ACS_ULCORNER "l"
#define ACS_URCORNER "k"

extern int BigC[18][2];

int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int BC[2], int x, int y, enum colors cl1, enum colors cl2);
int bc_setbigcharpos(int* big, int x, int y, int value);
int bc_getbigcharpos(int* big, int x, int y, int* value);
int bc_bigcharwrite(int fd, int* big, int count);
int bc_bigcharread(int fd, int* big, int need_count, int* count);
