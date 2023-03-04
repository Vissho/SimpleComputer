#include <myTerm.h>
#include <stdio.h>

int mt_clrscr(void) {
  int fd = open("/dev/tty", O_WRONLY);
  if (fd == -1) {
    printf("Ошибка открытия терминала.\n");
    return -1;
  }

  write(fd, "\E[H\E[J", 7);

  close(fd);
  return 0;
}

int mt_gotoXY(int x, int y) {
  int fd = open("/dev/tty", O_WRONLY);
  if (fd == -1) {
    printf("Ошибка открытия терминала.\n");
    return -1;
  }

  char str[N];
  int size = 0;

  sprintf(str, "\E[%d;%dH", x, y);
  for (; str[size] != '\0'; size++)
    ;

  write(fd, str, size);

  close(fd);
  return 0;
}

int mt_getscreensize(int *rows, int *cols) {
  struct winsize ws;

  if (!ioctl(1, TIOCGWINSZ, &ws)) {
    *rows = ws.ws_row;
    *cols = ws.ws_col;
  } else {
    printf("Ошибка получения размера экрана.\n");
    return -1;
  }

  return 0;
}

int mt_setfgcolor(enum colors cl) {
  int fd = open("/dev/tty", O_WRONLY);
  if (fd == -1) {
    printf("Ошибка открытия терминала.\n");
    return -1;
  }

  char str[N];
  int size = 0;

  sprintf(str, "\E[3%dm", cl);
  for (; str[size] != '\0'; size++)
    ;

  write(fd, str, size);

  close(fd);
  return 0;
}

int mt_setbgcolor(enum colors cl) {
  int fd = open("/dev/tty", O_WRONLY);
  if (fd == -1) {
    printf("Ошибка открытия терминала.\n");
    return -1;
  }

  char str[N];
  int size = 0;

  sprintf(str, "\E[4%dm", cl);
  for (; str[size] != '\0'; size++)
    ;

  write(fd, str, size);

  close(fd);
  return 0;
}
