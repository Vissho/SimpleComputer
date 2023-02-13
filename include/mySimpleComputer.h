#pragma once

#include <stdio.h>

#define SIZE 100

#define CF 0
#define PF 1
#define AF 3
#define ZF 5
#define SF 6

#define CHECK_FLAG                                                        \
  Register == CF || Register == PF || Register == AF || Register == ZF || \
      Register == SF
#define CHECK_COMMAND                                                     \
  command == 10 || command == 11 || command == 20 || command == 21 ||     \
      (command > 29 && command < 34) || (command > 39 && command < 44) || \
      (command > 50 && command < 77)
#define CHECK_VALUE                                                     \
  (value >> 7) == 10 || (value >> 7) == 11 || (value >> 7) == 20 ||     \
      (value >> 7) == 21 || ((value >> 7) > 29 && (value >> 7) < 34) || \
      ((value >> 7) > 39 && (value >> 7) < 44) ||                       \
      ((value >> 7) > 50 && (value >> 7) < 77)

int sc_memoryInit(void);
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(int Register, int value);
int sc_regGet(int Register, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);

int print_bites(int key);
