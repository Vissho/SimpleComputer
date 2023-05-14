#include <interface.h>
#include <myALU.h>
#include <myCU.h>
#include <mySignal.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
CU (void)
{
  int command = 0, operand = 0, temp = 0, flag = 0;
  if (sc_memoryGet (instruction_counter, &temp))
    return -1;
  if (sc_commandDecode (temp, &command, &operand))
    return -1;

  if (command == 0x10)
    {
      flag = cu_read (operand);
    }
  else if (command == 0x11)
    {
      flag = cu_write (operand);
    }
  else if (command == 0x20)
    {
      flag = cu_load (operand);
    }
  else if (command == 0x21)
    {
      flag = cu_store (operand);
    }
  else if (command == 0x40)
    {
      flag = cu_jump (operand);
    }
  else if (command == 0x41)
    {
      flag = cu_jneg (operand);
    }
  else if (command == 0x42)
    {
      flag = cu_jz (operand);
    }
  else if (command == 0x43)
    {
      flag = cu_halt ();
    }
  else if (command == 0x30 || command == 0x31 || command == 0x32
           || command == 0x33 || command == 0x67)
    {
      flag = ALU (command, operand);
    }
  else
    {
      sc_regSet (E, 1);
      sc_regSet (T, 1);
      if (flag_RUN)
        {
          flag_RUN = 0;
          source ();
        }
      return -1;
    }

  return flag;
}

int
cu_read (int operand)
{
  if (flag_RUN)
    {
      stop_timer ();
    }
  int value = 0;
  mt_gotoXY (24, 0);
  printf ("%s", empty);
  mt_gotoXY (24, 0);
  printf ("Введите значение: ");
  scanf ("%d", &value);
  if (value < 0)
    value = ((-value) & 0x3fff) | 0x4000;
  else
    value = value & 0x3fff;

  if (sc_memorySet (operand, value))
    return -1;

  if (flag_RUN)
    {
      reboot_timer ();
    }

  return 0;
}

int
cu_write (int operand)
{
  int temp = 0, command = 0, oper = 0;
  if (sc_memoryGet (operand, &temp))
    return -1;

  mt_gotoXY (24, 0);
  printf ("%s", empty);
  mt_gotoXY (24, 0);
  printf ("Значение: ");
  int flag = sc_commandDecode (temp & 0x3FFF, &command, &oper);
  if (flag)
    return -1;
  if (!(temp & 0x4000) || flag)
    {
      printf ("+");
    }
  else
    {
      printf ("-");
      temp &= 0x3fff;
    }
  printf ("%d", temp);

  return 0;
}

int
cu_load (int operand)
{
  int temp = 0;
  if (sc_memoryGet (operand, &temp))
    return -1;

  accumulator = temp;
  return 0;
}

int
cu_store (int operand)
{
  if (sc_memorySet (operand, accumulator))
    return -1;

  return 0;
}

int
cu_jump (int operand)
{
  instruction_counter = operand;
  position = operand;
  return 0;
}

int
cu_jneg (int operand)
{
  if (accumulator & 0x4000)
    {
      instruction_counter = operand;
      position = operand;
    }
  return 0;
}

int
cu_jz (int operand)
{
  if (accumulator == 0)
    {
      instruction_counter = operand;
      position = operand;
    }
  return 0;
}

int
cu_halt ()
{
  if (flag_RUN)
    {
      flag_RUN = 0;
      source ();
    }
  return 0;
}
