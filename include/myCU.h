#pragma once

extern int instruction_counter;
extern int accumulator;
extern int position;
extern int prev_position;
extern int flag_RUN;
extern char empty[];

int CU (void);
int cu_read (int operand);
int cu_write (int operand);
int cu_load (int operand);
int cu_store (int operand);
int cu_jump (int operand);
int cu_jneg (int operand);
int cu_jz (int operand);
int cu_halt (void);
