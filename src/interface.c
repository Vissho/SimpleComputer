#include <interface.h>
#include <myBigChars.h>
#include <myReadkey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdlib.h>
#include <termios.h>

static int accumulator = 0;
static int instruction_counter = 0;
static int operation = 0;
static int error_xy = 23;

static char *ERROR[5]
    = { "Переполнение при выполнении операции.", "Ошибка деления на 0.",
        "Ошибка выхода за границы памяти", "Игнорирование тактовых импульсов.",
        "Указана неверная команда." };

int
print_memory (void)
{
  int temp = 0, flag = 0, command = 0, operand = 0;

  bc_box (1, 1, 12, 63);

  for (int i = 0; i < 10; ++i)
    {
      mt_gotoXY (i + 2, 3);
      for (int j = 0; j < 10; ++j)
        {
          command = 0, operand = 0, flag = 0;
          error (sc_memoryGet (i * 10 + j, &temp));
          flag = error (sc_commandDecode (temp & 0x3FFF, &command, &operand));
          temp = (temp >> 15) & 0x1;
          if (!temp || flag)
            {
              printf ("+");
            }
          else
            {
              printf ("-");
            }
          printf ("%.2X", command);
          printf ("%.2X ", operand);
        }
    }

  mt_gotoXY (1, 28);
  printf (" Memory ");

  return 0;
}

int
print_accumulator (int position)
{
  int temp = 0, flag = 0, command = 0, operand = 0;
  error (sc_memoryGet (position, &accumulator));

  bc_box (1, 65, 3, 22);
  mt_gotoXY (2, 73);

  temp = accumulator;
  flag = error (sc_commandDecode (temp & 0x3FFF, &command, &operand));
  temp = (temp >> 15) & 0x1;
  if (!temp || flag)
    {
      printf ("+");
    }
  else
    {
      printf ("-");
    }
  printf ("%.2X", command);
  printf ("%.2X", operand);

  mt_gotoXY (1, 69);
  printf (" accumulator ");

  return 0;
}

int
print_instructionCounter (int position)
{
  instruction_counter = position;
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
  error (sc_memoryGet (position, &operation));
  int command = 0, operand = 0, flag = 0;

  bc_box (7, 65, 3, 22);
  mt_gotoXY (8, 72);

  int temp = operation;
  flag = error (sc_commandDecode (temp & 0x3FFF, &command, &operand));
  temp = (temp >> 15) & 0x1;
  if (!temp || flag)
    {
      printf ("+");
    }
  else
    {
      printf ("-");
    }
  printf ("%.2X : ", command);
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

  if (!error (sc_regGet (P, &temp)) && temp)
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

  if (!error (sc_regGet (O, &temp)) && temp)
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

  if (!error (sc_regGet (M, &temp)) && temp)
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

  if (!error (sc_regGet (T, &temp)) && temp)
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

  if (!error (sc_regGet (E, &temp)) && temp)
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
print_big_accumulator (int position)
{
  bc_box (13, 1, 10, 48);
  int temp = 0, flag = 0, command = 0, operand = 0;
  error (sc_memoryGet (position, &temp));
  flag = error (sc_commandDecode (temp & 0x3FFF, &command, &operand));
  temp = (temp >> 15) & 0x1;
  if (!temp || flag)
    {
      bc_printbigchar (BigC[16], 14, 3, cl_default, cl_default);
    }
  else
    {
      bc_printbigchar (BigC[17], 14, 3, cl_default, cl_default);
    }
  // printf("%x   %x", command, operand);
  bc_printbigchar (BigC[operand % 16], 14, 39, cl_default, cl_default);
  operand /= 16;
  bc_printbigchar (BigC[operand % 16], 14, 30, cl_default, cl_default);
  bc_printbigchar (BigC[command % 16], 14, 21, cl_default, cl_default);
  command /= 16;
  bc_printbigchar (BigC[command % 16], 14, 12, cl_default, cl_default);

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
  print_big_accumulator (position);
  print_keys ();
  mt_gotoXY (error_xy + 1, 0);

  enum keys k;
  error (rk_readkey (&k));
  printf ("%d\n", k);
  error (rk_mytermsave ());
  error (rk_mytermrestore ());

  return 0;
}

int
error (int value)
{
  if (value != 0)
    {

      int temp = value * (-1) - 1;
      mt_gotoXY (error_xy++, 0);
      printf ("%s", ERROR[temp]);

      if (temp == 0)
        {
          sc_regSet (P, 1);
        }
      else if (temp == 1)
        {
          sc_regSet (O, 1);
        }
      else if (temp == 2)
        {
          sc_regSet (M, 1);
        }
      else if (temp == 3)
        {
          sc_regSet (T, 1);
        }
      else if (temp == 4)
        {
          sc_regSet (E, 1);
        }
    }

  return value;
}
