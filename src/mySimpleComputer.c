#include <mySimpleComputer.h>

int RAM[SIZE];
int REGISTER;

int
sc_memoryInit (void)
{
  for (int i = 0; i < SIZE; ++i)
    {
      sc_memorySet (i, 0);
      if (RAM[i] != 0)
        {
          return -5;
        }
    }

  return 0;
}

int
sc_memorySet (int address, int value)
{
  if (address < SIZE && address >= 0 && value <= 32767 && value >= -32767)
    {
      RAM[address] = value;
    }
  else
    {
      return -3;
    }

  return 0;
}

int
sc_memoryGet (int address, int *value)
{
  if (address < SIZE && address >= 0)
    {
      *value = RAM[address];
    }
  else
    {
      return -3;
    }

  return 0;
}

int
sc_memorySave (char *filename)
{
  if (!filename)
    {
      return -5;
    }

  FILE *fp;
  fp = fopen (filename, "wb");

  if (!fp)
    {
      return -5;
    }

  for (int i = 0; i < SIZE; ++i)
    fwrite (&RAM[i], sizeof (int), 1, fp);

  fclose (fp);
  return 0;
}

int
sc_memoryLoad (char *filename)
{
  if (!filename)
    {
      return -5;
    }

  FILE *fp;
  fp = fopen (filename, "rb");

  if (!fp)
    {
      return -5;
    }

  for (int i = 0; i < SIZE; ++i)
    fread (&RAM[i], sizeof (int), 1, fp);

  fclose (fp);
  return 0;
}

int
sc_regInit (void)
{
  REGISTER = 0;
  return 0;
}

int
sc_regSet (int Register, int value)
{
  if ((CHECK_FLAG) && (value == 0 || value == 1))
    {
      if (value)
        {
          REGISTER = REGISTER | (1 << (Register - 1));
        }
      else
        {
          REGISTER = REGISTER & (~(1 << (Register - 1)));
        }
    }
  else
    {
      return -3;
    }

  return 0;
}

int
sc_regGet (int Register, int *value)
{
  if (CHECK_FLAG)
    {
      *value = (REGISTER >> (Register - 1)) & 0x1;
    }
  else
    {
      return -3;
    }

  return 0;
}

int
sc_commandEncode (int command, int operand, int *value)
{
  *value = 0 | (command << 7) | operand;
  return 0;
}

int
sc_commandDecode (int value, int *command, int *operand)
{
  *command = (value >> 7);
  *operand = (value & 127);
  return 0;
}
