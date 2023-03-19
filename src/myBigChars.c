#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <stdio.h>

int BigC[18][2] = {
  { 0x8181817E, 0x7e818181 }, // 0
  { 0x8890A0C0, 0x80808080 }, { 0x2040827C, 0xFE040810 },
  { 0x6080817E, 0x7E818060 }, { 0xFF818181, 0x80808080 },
  { 0x7F0101FF, 0x7F808080 }, { 0x0101817E, 0x7E81817F },
  { 0x204080FE, 0x02040810 }, { 0x7E81817E, 0x7E818181 },
  { 0x7E81817E, 0x7E808080 }, { 0x7E42423C, 0x42424242 },
  { 0x3E42423E, 0x3E424242 }, { 0x0101017E, 0x7E010101 },
  { 0x4242221E, 0x1E224242 }, { 0x7E02027E, 0x7E020202 },
  { 0x7E02027E, 0x02020202 }, // F
  { 0xFF181818, 0x181818FF }, // +
  { 0xFF000000, 0x000000FF }  // -
};

int
bc_printA (char *str)
{
  if (!str)
    {
      sc_regSet (E, 1);
      return -1;
    }

  printf (ENTER_ALT_CHARSER_MODE);
  printf ("%s", str);
  printf (EXIT_ALT_CHARSER_MODE);

  return 0;
}

int
bc_box (int x1, int y1, int x2, int y2)
{
  for (int i = 1; i <= y2 - 2; i++)
    {
      mt_gotoXY (x1, y1 + i);
      bc_printA (ACS_HLINE);
      mt_gotoXY (x1 + x2 - 1, y1 + i);
      bc_printA (ACS_HLINE);
    }

  for (int i = 1; i <= x2 - 2; i++)
    {
      mt_gotoXY (x1 + i, y1);
      bc_printA (ACS_VLINE);
      mt_gotoXY (x1 + i, y1 + y2 - 1);
      bc_printA (ACS_VLINE);
    }

  mt_gotoXY (x1, y1);
  bc_printA (ACS_ULCORNER);
  mt_gotoXY (x1, y1 + y2 - 1);
  bc_printA (ACS_URCORNER);
  mt_gotoXY (x1 + x2 - 1, y1);
  bc_printA (ACS_LLCORNER);
  mt_gotoXY (x1 + x2 - 1, y1 + y2 - 1);
  bc_printA (ACS_LRCORNER);

  return 0;
}
