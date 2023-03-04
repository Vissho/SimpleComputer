#include <mySimpleComputer.h>
#include <myTerm.h>

int main() {
  sc_memoryInit();
  sc_regInit();

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

  printf("sc_regSet check 1:\n");
  sc_regSet(CF, 1);
  printf("sc_regSet check 2:");
  sc_regSet(9, 1);

  printf("sc_regGet check 1: ");
  sc_regGet(CF, &temp);
  printf("%d\n", temp);
  printf("sc_regGet check 2:");
  sc_regGet(9, &temp);
  printf("sc_regGet check 2: %d\n", temp);

  int n = 0;
  printf("sc_commandEncode check 1:");
  sc_commandEncode(33, 59, &n);
  print_bites(n);
  printf("%d\n", n);
  printf("sc_commandEncode check 2:");
  sc_commandEncode(2, 59, &n);
  print_bites(n);
  printf("%d\n", n);

  int com = 0, oper = 0;
  printf("sc_commandDecode check 1:");
  sc_commandDecode(n, &com, &oper);
  printf("%d %d\n", com, oper);
  printf("sc_commandDecode check 2:");
  sc_commandDecode(__INT_MAX__, &com, &oper);
  printf("%d %d\n", com, oper);

  mt_clrscr();
  mt_gotoXY(10, 100);
  printf("1\n");

  int row = 0, col = 0;
  mt_getscreensize(&row, &col);
  printf("Получен размер экрана.\n");
  printf("Число строк – %d\nЧисло столбцов – %d\n", row, col);

  mt_setfgcolor(cl_red);
  printf("1111\n");

  mt_setbgcolor(cl_black);
  printf("1111\n");

  mt_setfgcolor(cl_default);
  mt_setbgcolor(cl_default);

  return 0;
}
