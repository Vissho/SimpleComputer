#include <myTerm.h>
#include <stdio.h>

int fd;

int
mt_clrscr (void)
{
  write (fd, "\E[H\E[J", 7);

  return 0;
}

int
mt_gotoXY (int x, int y)
{
  char str[N];
  int size = 0;

  sprintf (str, "\E[%d;%dH", x, y);
  for (; str[size] != '\0'; size++)
    ;

  write (fd, str, size);

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
      printf ("Ошибка получения размера экрана.\n");
      return -1;
    }

  return 0;
}

int
mt_setfgcolor (enum colors cl)
{
  char str[N];
  int size = 0;

  sprintf (str, "\E[3%dm", cl);
  for (; str[size] != '\0'; size++)
    ;

  write (fd, str, size);

  return 0;
}

int
mt_setbgcolor (enum colors cl)
{
  char str[N];
  int size = 0;

  sprintf (str, "\E[4%dm", cl);
  for (; str[size] != '\0'; size++)
    ;

  write (fd, str, size);

  return 0;
}
