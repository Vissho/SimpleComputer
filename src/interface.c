#include <interface.h>
#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

static int accumulator = 0;
static int instruction_counter = 0;
static int operation = 0;
static int error_xy = 23;
static int position = 0;
static int prev_position = 0;
static int flag_F5 = 1;
static int flag_F6 = 1;

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
print_accumulator (void)
{
  int temp = 0, flag = 0, command = 0, operand = 0;
  if (flag_F5 == 1)
    error (sc_memoryGet (position, &accumulator));

  bc_box (1, 65, 3, 22);
  mt_gotoXY (2, 73);

  if (flag_F5 == -1)
    mt_setbgcolor (cl_blue);

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
  mt_setbgcolor (cl_default);
  printf (" accumulator ");

  return 0;
}

int
print_instructionCounter (void)
{
  if (flag_F6 == 1)
    instruction_counter = position;
  bc_box (4, 65, 3, 22);
  mt_gotoXY (5, 73);

  if (flag_F6 == -1)
    mt_setbgcolor (cl_blue);

  printf ("%+.4d", instruction_counter);

  mt_gotoXY (4, 66);
  mt_setbgcolor (cl_default);
  printf (" instructionCounter ");

  return 0;
}

int
print_operation (void)
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
print_big_accumulator (void)
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
error (int value)
{
  if (value != 0)
    {

      int temp = value * (-1) - 1;
      mt_gotoXY (error_xy++ + 1, 0);
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

int
clear_position (int position)
{
  int temp = 0, command = 0, operand = 0, flag = 0;

  error (sc_memoryGet (position, &temp));
  flag = error (sc_commandDecode (temp & 0x3FFF, &command, &operand));
  temp = (temp >> 15) & 0x1;
  mt_setbgcolor (cl_default);
  mt_gotoXY (position / 10 + 2, position % 10 * 6 + 3);
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

  return 0;
}

int
print_position (void)
{
  if (position > 99 || position < 0)
    return -3;

  if (flag_F5 == -1 || flag_F6 == -1)
    return 0;

  int temp = 0, command = 0, operand = 0, flag = 0;

  clear_position (prev_position);

  error (sc_memoryGet (position, &temp));
  flag = error (sc_commandDecode (temp & 0x3FFF, &command, &operand));
  temp = (temp >> 15) & 0x1;
  mt_setbgcolor (cl_blue);
  mt_gotoXY (position / 10 + 2, position % 10 * 6 + 3);
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
  mt_setbgcolor (cl_default);

  prev_position = position;
  return 0;
}

int
analysis_k (enum keys k)
{
  if (k == 0 && flag_F5 != -1 && flag_F6 != -1)
    {
      char str[200];
      mt_gotoXY (error_xy++ + 1, 0);
      printf ("Введите название файла: ");
      scanf ("%s", str);
      strcat (str, ".bin");
      error (sc_memoryLoad (str));
    }
  else if (k == 1 && flag_F5 != -1 && flag_F6 != -1)
    {
      char str[200];
      mt_gotoXY (error_xy++ + 1, 0);
      printf ("Введите название файла: ");
      scanf ("%s", str);
      strcat (str, ".bin");
      error (sc_memorySave (str));
    }
  else if (k == 5 && flag_F6 != -1)
    {
      if (flag_F5 == 1)
        {
          clear_position (position);
        }
      flag_F5 *= (-1);
    }
  else if (k == 6 && flag_F5 != -1)
    {
      if (flag_F6 == 1)
        {
          clear_position (position);
        }
      flag_F6 *= (-1);
    }
  else if (k == 7 && flag_F5 != -1 && flag_F6 != -1)
    {
      if (position > 9)
        position -= 10;
    }
  else if (k == 8 && flag_F5 != -1 && flag_F6 != -1)
    {
      if (position < 90)
        position += 10;
    }
  else if (k == 9 && flag_F5 != -1 && flag_F6 != -1)
    {
      if (position % 10 != 0)
        position -= 1;
    }
  else if (k == 10 && flag_F5 != -1 && flag_F6 != -1)
    {
      if (position % 10 != 9)
        position += 1;
    }
  else if (k == 11)
    {
      int value = 0;
      mt_gotoXY (error_xy++ + 1, 0);
      printf ("Введите значение: ");
      scanf ("%d", &value);
      if (flag_F5 == -1)
        {
          accumulator = value;
        }
      else if (flag_F6 == -1)
        {
          if (value > 99 || value < 0)
            return -5;
          instruction_counter = value;
        }
      else
        {
          error (sc_memorySet (position, value));
        }
    }
  else
    {
      return -5;
    }

  return 0;
}

int
interface (void)
{
  setvbuf (stdout, NULL, _IONBF, 0);
  mt_clrscr ();
  error (rk_mytermsave ());

  print_keys ();
  mt_gotoXY (error_xy + 1, 0);

  enum keys k;
  do
    {
      print_memory ();
      print_accumulator ();
      print_instructionCounter ();
      print_operation ();
      print_flags ();
      print_big_accumulator ();
      error (print_position ());
      error (rk_readkey (&k));
      error (analysis_k (k));
    }
  while (k != 12);
  mt_gotoXY (error_xy + 1, 0);

  return 0;
}
