#pragma once

#include <stdio.h>

#define SIZE 100

extern int RAM[SIZE];
extern int REGISTER;

#define P 0
#define O 1
#define M 3
#define T 5
#define E 6

#define CHECK_FLAG                                                            \
  Register == P || Register == O || Register == M || Register == T            \
      || Register == E
#define CHECK_COMMAND                                                         \
  command == 10 || command == 11 || command == 20 || command == 21            \
      || (command > 29 && command < 34) || (command > 39 && command < 44)     \
      || (command > 50 && command < 77)
#define CHECK_VALUE                                                           \
  (value >> 7) == 10 || (value >> 7) == 11 || (value >> 7) == 20              \
      || (value >> 7) == 21 || ((value >> 7) > 29 && (value >> 7) < 34)       \
      || ((value >> 7) > 39 && (value >> 7) < 44)                             \
      || ((value >> 7) > 50 && (value >> 7) < 77)

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int Register, int value);
int sc_regGet (int Register, int *value);
int sc_commandEncode (int command, int operand, int *value);
int sc_commandDecode (int value, int *command, int *operand);
int print_bites (int key);
