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
    RAM[i] = 0;
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
    REGISTER = 1;
    printf("Выход за границы памяти!\n");
    return -1;
  }

  return 0;
}

int sc_memoryGet(int address, int* value) {
  if (address < SIZE && address >= 0) {
    *value = RAM[address];
  } else {
    REGISTER = 1;
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
