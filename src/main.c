#include <mySimpleComputer.h>

int main() {
  sc_memoryInit();

  int temp;

  printf("sc_memorySet check 1:\n");
  sc_memorySet(55, 55);
  printf("sc_memorySet check 2: ");
  sc_memorySet(120, 9);

  printf("sc_memoryGet check 1: ");
  sc_memoryGet(55, &temp);
  printf("%d\n", temp);
  printf("sc_memoryGet check 2: ");
  sc_memoryGet(120, &temp);
  printf("sc_memoryGet check 2: %d\n", temp);

  printf("sc_memorySave check 1:\n");
  sc_memorySave("test/file.bin");
  printf("sc_memorySave check 2:");
  sc_memorySave(NULL);

  printf("sc_memoryLoad check 1:");
  sc_memoryLoad("test/file.bin");
  sc_memoryGet(55, &temp);
  printf("%d\n", temp);
  printf("sc_memoryLoad check 2:");
  sc_memoryLoad(NULL);

  return 0;
}
