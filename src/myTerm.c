#include <myTerm.h>
#include <stdio.h>

int
mt_clrscr (void)
{
  write (0, "\E[H\E[J", 7);

  return 0;
}

int
mt_gotoXY (int x, int y)
{
  char str[N];
  int size = 0;

  size = sprintf (str, "\E[%d;%dH", x, y);

  write (0, str, size);

  return 0;
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;

  if (!ioctl (1, TIOCGWINSZ, &ws))
    {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
    }
  else
    {
      return -3;
    }

  return 0;
}

int
mt_setfgcolor (enum colors cl)
{
  char str[N];
  int size = 0;

  size = sprintf (str, "\E[3%dm", cl);
  write (0, str, size);

  return 0;
}

int
mt_setbgcolor (enum colors cl)
{
  char str[N];
  int size = 0;

  size = sprintf (str, "\E[4%dm", cl);
  write (0, str, size);

  return 0;
}
