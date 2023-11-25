#include <myALU.h>
#include <mySimpleComputer.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ALU(int command, int operand)
{
    int flag = 0;

    if (command == 0x30) {
        flag = alu_add(operand);
    } else if (command == 0x31) {
        flag = alu_sub(operand);
    } else if (command == 0x32) {
        flag = alu_divide(operand);
    } else if (command == 0x33) {
        flag = alu_mul(operand);
    } else if (command == 0x67) {
        flag = alu_loglc(operand);
    } else {
        return -1;
    }

    return flag;
}

int alu_add(int operand)
{
    int rez = accumulator, flag = 0, minus1 = -1, minus2 = -1, oper = 0;
    if (sc_memoryGet(operand, &oper))
        return -1;

    if (rez & 0x4000) {
        rez &= 0x3fff;
        minus1 = 1;
    }

    if (oper & 0x4000) {
        oper &= 0x3fff;
        minus2 = 1;
    }

    rez = (((-1) * minus1) * rez) + (((-1) * minus2) * oper);

    if (rez < 0) {
        rez *= (-1);
        if (rez <= 0x3fff) {
            rez |= 0x4000;
            flag = 1;
        }
    }

    if (!flag) {
        if (rez <= 0x3fff) {
            accumulator = rez;
        } else {
            sc_regSet(P, 1);
            return -1;
        }
    } else if (flag) {
        if (rez <= 0x7fff) {
            accumulator = rez;
        } else {
            sc_regSet(P, 1);
            return -1;
        }
    }
    return 0;
}

int alu_sub(int operand)
{
    int rez = accumulator, flag = 0, minus1 = -1, minus2 = -1, oper = 0;
    if (sc_memoryGet(operand, &oper))
        return -1;
    if (rez & 0x4000) {
        rez &= 0x3fff;
        minus1 = 1;
    }

    if (oper & 0x4000) {
        oper &= 0x3fff;
        minus2 = 1;
    }

    rez = (((-1) * minus1) * rez) - (((-1) * minus2) * oper);

    if (rez < 0) {
        rez *= (-1);
        if (rez <= 0x3fff) {
            rez |= 0x4000;
            flag = 1;
        }
    }

    if (!flag) {
        if (rez <= 0x3fff) {
            accumulator = rez;
        } else {
            sc_regSet(P, 1);
            return -1;
        }
    } else if (flag) {
        if (rez <= 0x7fff) {
            accumulator = rez;
        } else {
            sc_regSet(P, 1);
            return -1;
        }
    }
    return 0;
}

int alu_divide(int operand)
{
    int rez = accumulator, flag = 0, minus1 = -1, minus2 = -1, oper = 0;
    if (sc_memoryGet(operand, &oper))
        return -1;
    if (rez & 0x4000) {
        rez &= 0x3fff;
        minus1 = 1;
    }

    if (oper & 0x4000) {
        oper &= 0x3fff;
        minus2 = 1;
    }

    rez = rez / oper;
    if (((minus1 == 1 && minus2 == -1) || (minus1 == -1 && minus2 == 1))
        && rez <= 0x7fff) {
        rez |= 0x4000;
        flag = 1;
    }

    if (!flag) {
        if (rez <= 0x3fff) {
            accumulator = rez;
        } else {
            sc_regSet(P, 1);
            return -1;
        }
    } else if (flag) {
        if (rez <= 0x7fff) {
            accumulator = rez;
        } else {
            sc_regSet(P, 1);
            return -1;
        }
    }
    return 0;
}

int alu_mul(int operand)
{
    int rez = accumulator, flag = 0, minus1 = -1, minus2 = -1, oper = 0;
    if (sc_memoryGet(operand, &oper))
        return -1;
    if (rez & 0x4000) {
        rez &= 0x3fff;
        minus1 = 1;
    }

    if (oper & 0x4000) {
        oper &= 0x3fff;
        minus2 = 1;
    }

    rez = rez * oper;
    if (((minus1 == 1 && minus2 == -1) || (minus1 == -1 && minus2 == 1))
        && rez <= 0x7fff) {
        rez |= 0x4000;
        flag = 1;
    }

    if (!flag) {
        if (rez <= 0x3fff) {
            accumulator = rez;
        } else {
            sc_regSet(P, 1);
            return -1;
        }
    } else if (flag) {
        if (rez <= 0x7fff) {
            accumulator = rez;
        } else {
            sc_regSet(P, 1);
            return -1;
        }
    }
    return 0;
}

int alu_loglc(int operand)
{
    int rez = accumulator, oper = 0;
    if (sc_memoryGet(operand, &oper))
        return -1;

    rez = oper << rez;

    if (rez <= 0x3fff) {
        if (sc_memorySet(operand, rez))
            return -1;
    } else {
        sc_regSet(P, 1);
        return -1;
    }
    return 0;
}
