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

  bc_box (1, 65, 3, 22);
  mt_gotoXY (2, 73);

  int temp = accumulator;
  if (temp >= 0)
    {
      printf ("+");
    }
  else
    {
      printf ("-");
      temp *= (-1);
    }
  printf ("%.4X", temp);

  mt_gotoXY (1, 69);
  printf (" accumulator ");

  return 0;
}

int
print_instructionCounter (int position)
{
  instruction_counter = position + 1;
  bc_box (4, 65, 3, 22);
  mt_gotoXY (5, 73);

  printf ("%+.4d", instruction_counter);

  mt_gotoXY (4, 66);
  printf (" instructionCounter ");

  return 0;
}

int
print_operation (int position)
{
  operation = RAM[position];
  int command = 0, operand = 0;
  sc_commandDecode (operation, &command, &operand);

  bc_box (7, 65, 3, 22);
  mt_gotoXY (8, 72);

  if (command >= 0)
    {
      printf ("+");
    }
  else
    {
      printf ("-");
      command *= (-1);
    }
  printf ("%.2X : ", command);

  if (operand >= 0)
    {
      printf ("+");
    }
  else
    {
      printf ("-");
      operand *= (-1);
    }
  printf ("%.2X", operand);

  mt_gotoXY (7, 71);
  printf (" Operation ");

  return 0;
}

int
print_flags (void)
{
  bc_box (10, 65, 3, 22);
  mt_gotoXY (11, 71);

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

  mt_gotoXY (10, 71);
  printf (" Flags ");

  return 0;
}

int
print_keys (void)
{
  bc_box (13, 50, 10, 37);

  mt_gotoXY (14, 52);
  printf ("l  - load");
  mt_gotoXY (15, 52);
  printf ("s  - save");
  mt_gotoXY (16, 52);
  printf ("r  - run");
  mt_gotoXY (17, 52);
  printf ("t  - step");
  mt_gotoXY (18, 52);
  printf ("i  - reset");
  mt_gotoXY (19, 52);
  printf ("F5 - accumulator");
  mt_gotoXY (20, 52);
  printf ("F6 - instructionCounter");

  mt_gotoXY (13, 51);
  printf (" Keys: ");

  return 0;
}

int
print_big_accumulator (void)
{
  bc_box (13, 1, 10, 48);
  int temp = accumulator;
  if (temp >= 0)
    {
      bc_printbigchar (BigC[16], 14, 3, cl_default, cl_default);
    }
  else
    {
      bc_printbigchar (BigC[17], 14, 3, cl_default, cl_default);
      temp *= (-1);
    }

  bc_printbigchar (BigC[temp % 16], 14, 39, cl_default, cl_default);
  temp /= 16;
  bc_printbigchar (BigC[temp % 16], 14, 30, cl_default, cl_default);
  temp /= 16;
  bc_printbigchar (BigC[temp % 16], 14, 21, cl_default, cl_default);
  temp /= 16;
  bc_printbigchar (BigC[temp % 16], 14, 12, cl_default, cl_default);

  return 0;
}

int
interface (void)
{
  setvbuf (stdout, NULL, _IONBF, 0);
  mt_clrscr ();

  int position = 0;

  print_memory ();
  print_accumulator (position);
  print_instructionCounter (position);
  print_operation (position);
  print_flags ();
  print_big_accumulator ();
  print_keys ();
  mt_gotoXY (24, 0);

  return 0;
}
