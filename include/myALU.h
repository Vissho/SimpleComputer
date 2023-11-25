#pragma once

extern int accumulator;

int ALU(int command, int operand);
int alu_add(int operand);
int alu_sub(int operand);
int alu_divide(int operand);
int alu_mul(int operand);
int alu_loglc(int operand);
