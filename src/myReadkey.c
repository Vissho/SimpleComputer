#include <myReadkey.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

static int N = 16;
struct termios tsaved;

int
rk_readkey (enum keys *k)
{
  char str[N];
  if ((read (0, str, N)) == -1)
    {
      return -5;
    }

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
  if (tcsetattr (0, TCSADRAIN, &tsaved))
    return -5;

  return 0;
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
