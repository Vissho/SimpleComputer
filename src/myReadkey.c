#include <myReadkey.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

static int N = 16;
struct termios tsaved;

int
rk_readkey (enum keys *k) 
{
  char str[N];
  str[0] = '\0';
  if (read (0, str, N) == -1)
    return -5;

  if (str[0] == 'l')
    {
      *k = LOAD;
    }
  else if (str[0] == 's')
    {
      *k = SAVE;
    }
  else if (str[0] == 'r')
    {
      *k = RUN;
    }
  else if (str[0] == 't')
    {
      *k = STEP;
    }
  else if (str[0] == 'i')
    {
      *k = RESET;
    }
  else if (strcmp (str, F5_KEY) == 0)
    {
      *k = F5;
    }
  else if (strcmp (str, F6_KEY) == 0)
    {
      *k = F6;
    }
  else if (strcmp (str, DOWN_KEY) == 0)
    {
      *k = DOWN;
    }
  else if (strcmp (str, UP_KEY) == 0)
    {
      *k = UP;
    }
  else if (strcmp (str, LEFT_KEY) == 0)
    {
      *k = LEFT;
    }
  else if (strcmp (str, RIGHT_KEY) == 0)
    {
      *k = RIGHT;
    }
  else if (strcmp (str, ENTER_KEY) == 0)
    {
      *k = ENTER;
    }
  else
    {
      *k = OTHER;
    }

  return 0;
}

int
rk_mytermsave (void)
{
  if (tcgetattr (0, &tsaved))
    return -5;

  return 0;
}

int
rk_mytermrestore (void)
{
  if (tcsetattr (0, TCSANOW, &tsaved))
    return -5;

  return 0;
}

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios temp;

  if (tcgetattr (0, &temp))
    return -5;

  if (regime == 1)
    {
      temp.c_lflag |= ICANON;
    }
  else if (regime == 0)
    {
      temp.c_lflag &= ~ICANON;
    }
  else
    {
      return -5;
    }

  if (vtime == 1)
    {
      temp.c_lflag |= VTIME;
    }
  else if (vtime == 0)
    {
      temp.c_lflag &= ~VTIME;
    }
  else
    {
      return -5;
    }

  if (vmin == 1)
    temp.c_lflag |= VMIN;
  else if (vmin == 0)
    {
      temp.c_lflag &= ~VMIN;
    }
  else
    {
      return -5;
    }

  if (echo == 1)
    temp.c_lflag |= ECHO;
  else if (echo == 0)
    temp.c_lflag &= ~ECHO;
  else
    {
      return -5;
    }

  if (sigint == 1)
    temp.c_lflag |= ISIG;
  else if (sigint == 0)
    temp.c_lflag &= ~ISIG;
  else
    {
      return -5;
    }

  if (tcsetattr (0, TCSANOW, &temp))
    return -5;

  return 0;
}
