#include <mySimpleComputer.h>

int print_bites(int key) {
  for (int i = 31; i > 0; --i) {
    printf("%d", (key >> (i - 1)) & 0x1);
  }
  printf("\n");

  return 0;
}

int sc_memoryInit(void) {
  for (int i = 0; i < SIZE; ++i) {
    sc_memorySet(i, 0);
    if (RAM[i] != 0) {
      printf("Массив не инициализирован!\n");
      return -1;
    }
  }

  return 0;
}

int sc_memorySet(int address, int value) {
  if (address < SIZE && address >= 0) {
    RAM[address] = value;
  } else {
    sc_regSet(AF, 1);
    printf("Выход за границы памяти!\n");
    return -1;
  }

  return 0;
}

int sc_memoryGet(int address, int* value) {
  if (address < SIZE && address >= 0) {
    *value = RAM[address];
  } else {
    sc_regSet(AF, 1);
    printf("Выход за границы памяти!\n");
    return -1;
  }

  return 0;
}

int sc_memorySave(char* filename) {
  if (!filename) {
    printf("Нет названия файла!\n");
    return -1;
  }

  FILE* fp;
  fp = fopen(filename, "wb");

  if (!fp) {
    printf("Программа не нашла файл!\n");
    fclose(fp);
    return -1;
  }

  for (int i = 0; i < SIZE; ++i) fwrite(&RAM[i], sizeof(int), 1, fp);

  fclose(fp);
  return 0;
}

int sc_memoryLoad(char* filename) {
  if (!filename) {
    printf("Нет названия файла!\n");
    return -1;
  }

  FILE* fp;
  fp = fopen(filename, "rb");

  if (!fp) {
    printf("Программа не нашла файл!\n");
    fclose(fp);
    return -1;
  }

  for (int i = 0; i < SIZE; ++i) fread(&RAM[i], sizeof(int), 1, fp);

  fclose(fp);
  return 0;
}

int sc_regInit(void) {
  REGISTER = 0;
  return 0;
}

int sc_regSet(int Register, int value) {
  if ((CHECK_FLAG) && (value == 0 || value == 1)) {
    if (value) {
      REGISTER = REGISTER | (1 << (Register - 1));
    } else {
      REGISTER = REGISTER & (~(1 << (Register - 1)));
    }
  } else {
    printf("Некорректные данные!\n");
    return -1;
  }

  return 0;
}

int sc_regGet(int Register, int* value) {
  if (CHECK_FLAG) {
    *value = (REGISTER >> (Register - 1)) & 0x1;
  } else {
    sc_regSet(AF, 1);
    printf("Выход за границы памяти!\n");
    return -1;
  }

  return 0;
}

int sc_commandEncode(int command, int operand, int* value) {
  if ((CHECK_COMMAND) && operand >= 0 && operand < 128) {
    *value = 0 | (command << 7) | operand;
  } else {
    printf("Некорректные данные!\n");
    return -1;
  }

  return 0;
}

int sc_commandDecode(int value, int* command, int* operand) {
  if (CHECK_VALUE) {
    *command = 0 | (value >> 7);
    *operand = 0 | (value & 127);
  } else {
    sc_regSet(SF, 1);
    printf("Ошибочная команда!\n");
    return -1;
  }

  return 0;
}
