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
  int temp = 0;

  bc_box (1, 1, 12, 63);

  for (int i = 0; i < 10; ++i)
    {
      mt_gotoXY (i + 2, 3);
      for (int j = 0; j < 10; ++j)
        {
          temp = RAM[i * 10 + j];
          if (temp >= 0)
            {
              printf ("+");
            }
          else
            {
              printf ("-");
              temp *= (-1);
            }
          printf ("%.4X ", temp);
        }
    }

  mt_gotoXY (1, 28);
  printf (" Memory ");

  return 0;
}

int
print_accumulator (int position)
{
  accumulator = RAM[position];
  mt_gotoXY (1, 65);
  printf ("┌─── accumulator ────┐");
  mt_gotoXY (2, 65);
  printf ("│       %.4X        │", accumulator);
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
  printf ("│       %.4X        │", instruction_counter);
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
  printf ("│      %.2X : %.2X      │", command, operand);
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

  return 0;
}

int
interface (void)
{
  setvbuf (stdout, NULL, _IONBF, 0);
  mt_clrscr ();

  print_memory ();
  // print_accumulator (0);
  // print_instructionCounter ();
  // print_operation (0);
  // print_flags ();
  // print_big_accumulator ();
  // print_keys ();
  mt_gotoXY (24, 0);

  return 0;
}
