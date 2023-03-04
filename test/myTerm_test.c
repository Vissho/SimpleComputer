#include <ctest.h>
#include <myTerm.h>
#include <stdio.h>

CTEST(mt_clrscr, correctly_mt_clrscr) {
  int flag = mt_clrscr();
  ASSERT_EQUAL(0, flag);
}

CTEST(mt_gotoXY, correctly_mt_gotoXY) {
  int flag = mt_gotoXY(10, 10);
  ASSERT_EQUAL(0, flag);
}

CTEST(mt_getscreensize, correctly_mt_getscreensize) {
  int x = 0, y = 0;
  int flag = mt_getscreensize(&x, &y);
  ASSERT_EQUAL(0, flag);
}

CTEST(mt_setfgcolor, correctly_mt_setfgcolor) {
  int flag = mt_setfgcolor(cl_default);
  ASSERT_EQUAL(0, flag);
}

CTEST(mt_setbgcolor, correctly_mt_setbgcolor) {
  int flag = mt_setbgcolor(cl_default);
  ASSERT_EQUAL(0, flag);
}
