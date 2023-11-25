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

#define CHECK_FLAG                                                   \
    Register == P || Register == O || Register == M || Register == T \
            || Register == E

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
