#pragma once

#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define N 200

enum colors
{
  cl_black = 0,
  cl_red = 1,
  cl_green = 2,
  cl_yellow = 3,
  cl_blue = 4,
  cl_purple = 5,
  cl_cyan = 6,
  cl_white = 7,
  cl_default = 9
};

int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors cl);
int mt_setbgcolor (enum colors cl);
