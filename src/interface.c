#include <interface.h>
#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdlib.h>

static int accumulator = 0;
static int instruction_counter = 0;
static int operation = 0;

int
print_memory (void)
{
  printf ("┌────────────────────────── Memory ──────────────────"
          "─────────┐\n");

  for (int i = 0; i < 10; ++i)
    {
      printf ("│ ");
      for (int j = 0; j < 10; ++j)
        {
          printf ("%+.4d ", RAM[i * 10 + j]);
        }
      printf ("│\n");
    }
  printf ("└────────────────────────────────────────────────────"
          "─────────┘\n");

  return 0;
}

int
print_accumulator (int position)
{
  accumulator = RAM[position];
  mt_gotoXY (1, 65);
  printf ("┌─── accumulator ────┐");
  mt_gotoXY (2, 65);
  printf ("│       %+.4d        │", accumulator);
  mt_gotoXY (3, 65);
  printf ("└────────────────────┘");

  return 0;
}

int
print_instructionCounter (void)
{
  mt_gotoXY (4, 65);
  printf ("┌ instructionCounter ┐");
  mt_gotoXY (5, 65);
  printf ("│       %+.4d        │", instruction_counter);
  mt_gotoXY (6, 65);
  printf ("└────────────────────┘");

  return 0;
}

int
print_operation (int position)
{
  operation = RAM[position];
  int command = 0, operand = 0;
  sc_commandDecode (operation, &command, &operand);
  mt_gotoXY (7, 65);
  printf ("┌───── Operation ────┐");
  mt_gotoXY (8, 65);
  printf ("│      %+.2d : %.2d      │", command, operand);
  mt_gotoXY (9, 65);
  printf ("└────────────────────┘");

  return 0;
}

int
print_flags (void)
{
  mt_gotoXY (10, 65);
  printf ("┌─────── Flags ──────┐");
  mt_gotoXY (11, 65);
  printf ("│      ");

  int temp = 0;

  if (!sc_regGet (P, &temp) && temp)
    {
      mt_setfgcolor (cl_red);
      printf ("P ");
      mt_setfgcolor (cl_default);
    }
  else
    {
      mt_setfgcolor (cl_green);
      printf ("P ");
      mt_setfgcolor (cl_default);
    }

  if (!sc_regGet (O, &temp) && temp)
    {
      mt_setfgcolor (cl_red);
      printf ("O ");
      mt_setfgcolor (cl_default);
    }
  else
    {
      mt_setfgcolor (cl_green);
      printf ("O ");
      mt_setfgcolor (cl_default);
    }

  if (!sc_regGet (M, &temp) && temp)
    {
      mt_setfgcolor (cl_red);
      printf ("M ");
      mt_setfgcolor (cl_default);
    }
  else
    {
      mt_setfgcolor (cl_green);
      printf ("M ");
      mt_setfgcolor (cl_default);
    }

  if (!sc_regGet (T, &temp) && temp)
    {
      mt_setfgcolor (cl_red);
      printf ("T ");
      mt_setfgcolor (cl_default);
    }
  else
    {
      mt_setfgcolor (cl_green);
      printf ("T ");
      mt_setfgcolor (cl_default);
    }

  if (!sc_regGet (E, &temp) && temp)
    {
      mt_setfgcolor (cl_red);
      printf ("E ");
      mt_setfgcolor (cl_default);
    }
  else
    {
      mt_setfgcolor (cl_green);
      printf ("E ");
      mt_setfgcolor (cl_default);
    }

  printf ("    │");
  mt_gotoXY (12, 65);
  printf ("└────────────────────┘");

  return 0;
}

int
print_keys (void)
{
  mt_gotoXY (13, 50);
  printf ("┌ Keys: ────────────────────────────┐");
  mt_gotoXY (14, 50);
  printf ("│ l  - load                         │");
  mt_gotoXY (15, 50);
  printf ("│ s  - save                         │");
  mt_gotoXY (16, 50);
  printf ("│ r  - run                          │");
  mt_gotoXY (17, 50);
  printf ("│ t  - step                         │");
  mt_gotoXY (18, 50);
  printf ("│ i  - reset                        │");
  mt_gotoXY (19, 50);
  printf ("│ F5 - accumulator                  │");
  mt_gotoXY (20, 50);
  printf ("│ F6 - instructionCounter           │");
  mt_gotoXY (21, 50);
  printf ("│                                   │");
  mt_gotoXY (22, 50);
  printf ("└───────────────────────────────────┘");

  return 0;
}

int
print_big_num_plus (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("   ██   ");
  mt_gotoXY (x + 1, y);
  printf ("   ██   ");
  mt_gotoXY (x + 2, y);
  printf ("   ██   ");
  mt_gotoXY (x + 3, y);
  printf ("████████");
  mt_gotoXY (x + 4, y);
  printf ("████████");
  mt_gotoXY (x + 5, y);
  printf ("   ██   ");
  mt_gotoXY (x + 6, y);
  printf ("   ██   ");
  mt_gotoXY (x + 7, y);
  printf ("   ██   ");

  return 0;
}

int
print_big_num_minus (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("        ");
  mt_gotoXY (x + 1, y);
  printf ("        ");
  mt_gotoXY (x + 2, y);
  printf ("        ");
  mt_gotoXY (x + 3, y);
  printf ("        ");
  mt_gotoXY (x + 4, y);
  printf ("████████");
  mt_gotoXY (x + 5, y);
  printf ("        ");
  mt_gotoXY (x + 6, y);
  printf ("        ");
  mt_gotoXY (x + 7, y);
  printf ("        ");

  return 0;
}

int
print_big_num_0 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("████████");
  mt_gotoXY (x + 1, y);
  printf ("█      █");
  mt_gotoXY (x + 2, y);
  printf ("█      █");
  mt_gotoXY (x + 3, y);
  printf ("█      █");
  mt_gotoXY (x + 4, y);
  printf ("█      █");
  mt_gotoXY (x + 5, y);
  printf ("█      █");
  mt_gotoXY (x + 6, y);
  printf ("█      █");
  mt_gotoXY (x + 7, y);
  printf ("████████");

  return 0;
}

int
print_big_num_1 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("   ██   ");
  mt_gotoXY (x + 1, y);
  printf (" ████   ");
  mt_gotoXY (x + 2, y);
  printf ("██ ██   ");
  mt_gotoXY (x + 3, y);
  printf ("   ██   ");
  mt_gotoXY (x + 4, y);
  printf ("   ██   ");
  mt_gotoXY (x + 5, y);
  printf ("   ██   ");
  mt_gotoXY (x + 6, y);
  printf ("   ██   ");
  mt_gotoXY (x + 7, y);
  printf ("████████");

  return 0;
}

int
print_big_num_2 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("  ████  ");
  mt_gotoXY (x + 1, y);
  printf ("██    ██");
  mt_gotoXY (x + 2, y);
  printf ("     ██ ");
  mt_gotoXY (x + 3, y);
  printf ("    ██  ");
  mt_gotoXY (x + 4, y);
  printf ("   ██   ");
  mt_gotoXY (x + 5, y);
  printf ("  ██    ");
  mt_gotoXY (x + 6, y);
  printf (" ██     ");
  mt_gotoXY (x + 7, y);
  printf ("████████");

  return 0;
}

int
print_big_num_3 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("  ████  ");
  mt_gotoXY (x + 1, y);
  printf ("██    ██");
  mt_gotoXY (x + 2, y);
  printf ("     ██ ");
  mt_gotoXY (x + 3, y);
  printf ("  █████ ");
  mt_gotoXY (x + 4, y);
  printf ("     ██ ");
  mt_gotoXY (x + 5, y);
  printf ("      ██");
  mt_gotoXY (x + 6, y);
  printf ("██    ██");
  mt_gotoXY (x + 7, y);
  printf ("  ████  ");

  return 0;
}

int
print_big_num_4 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("    ███ ");
  mt_gotoXY (x + 1, y);
  printf ("   █ ██ ");
  mt_gotoXY (x + 2, y);
  printf ("  █  ██ ");
  mt_gotoXY (x + 3, y);
  printf (" █   ██ ");
  mt_gotoXY (x + 4, y);
  printf ("█    ██ ");
  mt_gotoXY (x + 5, y);
  printf ("████████");
  mt_gotoXY (x + 6, y);
  printf ("     ██ ");
  mt_gotoXY (x + 7, y);
  printf ("     ██ ");

  return 0;
}

int
print_big_num_5 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("████████");
  mt_gotoXY (x + 1, y);
  printf ("██      ");
  mt_gotoXY (x + 2, y);
  printf ("██      ");
  mt_gotoXY (x + 3, y);
  printf ("██████  ");
  mt_gotoXY (x + 4, y);
  printf ("      ██");
  mt_gotoXY (x + 5, y);
  printf ("      ██");
  mt_gotoXY (x + 6, y);
  printf ("      ██");
  mt_gotoXY (x + 7, y);
  printf ("██████  ");

  return 0;
}

int
print_big_num_6 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("   ██   ");
  mt_gotoXY (x + 1, y);
  printf ("  ██    ");
  mt_gotoXY (x + 2, y);
  printf (" ██     ");
  mt_gotoXY (x + 3, y);
  printf ("██      ");
  mt_gotoXY (x + 4, y);
  printf ("████████");
  mt_gotoXY (x + 5, y);
  printf ("█      █");
  mt_gotoXY (x + 6, y);
  printf ("█      █");
  mt_gotoXY (x + 7, y);
  printf ("████████");

  return 0;
}

int
print_big_num_7 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("████████");
  mt_gotoXY (x + 1, y);
  printf ("      ██");
  mt_gotoXY (x + 2, y);
  printf ("     ██ ");
  mt_gotoXY (x + 3, y);
  printf ("    ██  ");
  mt_gotoXY (x + 4, y);
  printf ("   ██   ");
  mt_gotoXY (x + 5, y);
  printf ("  ██    ");
  mt_gotoXY (x + 6, y);
  printf (" ██     ");
  mt_gotoXY (x + 7, y);
  printf ("██      ");

  return 0;
}

int
print_big_num_8 (int x, int y)
{
  mt_gotoXY (x, y);
  printf (" ██████ ");
  mt_gotoXY (x + 1, y);
  printf ("██    ██");
  mt_gotoXY (x + 2, y);
  printf (" ██  ██ ");
  mt_gotoXY (x + 3, y);
  printf ("  ████  ");
  mt_gotoXY (x + 4, y);
  printf (" ██  ██ ");
  mt_gotoXY (x + 5, y);
  printf ("██    ██");
  mt_gotoXY (x + 6, y);
  printf ("██    ██");
  mt_gotoXY (x + 7, y);
  printf (" ██████ ");

  return 0;
}

int
print_big_num_9 (int x, int y)
{
  mt_gotoXY (x, y);
  printf ("████████");
  mt_gotoXY (x + 1, y);
  printf ("█      █");
  mt_gotoXY (x + 2, y);
  printf ("█      █");
  mt_gotoXY (x + 3, y);
  printf ("████████");
  mt_gotoXY (x + 4, y);
  printf ("      ██");
  mt_gotoXY (x + 5, y);
  printf ("     ██ ");
  mt_gotoXY (x + 6, y);
  printf ("    ██  ");
  mt_gotoXY (x + 7, y);
  printf ("   ██   ");

  return 0;
}

int
print_big_num (char sign, int x, int y)
{
  if (sign == '+')
    {
      print_big_num_plus (x, y);
    }
  else if (sign == '-')
    {
      print_big_num_minus (x, y);
    }
  else if (sign == '0')
    {
      print_big_num_0 (x, y);
    }
  else if (sign == '1')
    {
      print_big_num_1 (x, y);
    }
  else if (sign == '2')
    {
      print_big_num_2 (x, y);
    }
  else if (sign == '3')
    {
      print_big_num_3 (x, y);
    }
  else if (sign == '4')
    {
      print_big_num_4 (x, y);
    }
  else if (sign == '5')
    {
      print_big_num_5 (x, y);
    }
  else if (sign == '6')
    {
      print_big_num_6 (x, y);
    }
  else if (sign == '7')
    {
      print_big_num_7 (x, y);
    }
  else if (sign == '8')
    {
      print_big_num_8 (x, y);
    }
  else if (sign == '9')
    {
      print_big_num_9 (x, y);
    }

  return 0;
}

int
print_big_accumulator (void)
{
  mt_gotoXY (13, 0);
  printf ("┌──────────────────────────────────────────────┐");
  mt_gotoXY (14, 0);
  printf ("│ ");
  mt_gotoXY (14, 48);
  printf ("│");
  mt_gotoXY (15, 0);
  printf ("│ ");
  mt_gotoXY (15, 48);
  printf ("│");
  mt_gotoXY (16, 0);
  printf ("│ ");
  mt_gotoXY (16, 48);
  printf ("│");
  mt_gotoXY (17, 0);
  printf ("│ ");
  mt_gotoXY (17, 48);
  printf ("│");
  mt_gotoXY (18, 0);
  printf ("│ ");
  mt_gotoXY (18, 48);
  printf ("│");
  mt_gotoXY (19, 0);
  printf ("│ ");
  mt_gotoXY (19, 48);
  printf ("│");
  mt_gotoXY (20, 0);
  printf ("│ ");
  mt_gotoXY (20, 48);
  printf ("│");
  mt_gotoXY (21, 0);
  printf ("│ ");
  mt_gotoXY (21, 48);
  printf ("│");
  mt_gotoXY (22, 0);
  printf ("└──────────────────────────────────────────────┘");

  if (accumulator >= 0)
    {
      print_big_num ('+', 14, 3);
    }
  else
    {
      print_big_num ('-', 14, 3);
    }

  int temp = accumulator;

  if (temp < 0)
    temp *= (-1);

  print_big_num (temp % 10 + '0', 14, 39);
  temp /= 10;
  print_big_num (temp % 10 + '0', 14, 30);
  temp /= 10;
  print_big_num (temp % 10 + '0', 14, 21);
  temp /= 10;
  print_big_num (temp % 10 + '0', 14, 12);
  temp /= 10;

  return 0;
}

int
interface (void)
{
  setvbuf (stdout, NULL, _IONBF, 0);
  mt_clrscr ();

  bc_printA (ACS_CKBOARD);
  bc_box (10, 5, 10, 10);

  // print_memory ();
  // print_accumulator (0);
  // print_instructionCounter ();
  // print_operation (0);
  // print_flags ();
  // print_big_accumulator ();
  // print_keys ();
  // mt_gotoXY (24, 0);

  return 0;
}
