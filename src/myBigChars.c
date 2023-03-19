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

int
bc_printbigchar (int BC[2], int x, int y, enum colors cl1, enum colors cl2)
{
  if (!BC)
    {
      sc_regSet (E, 1);
      return -1;
    }

  mt_setfgcolor (cl1);
  mt_setbgcolor (cl2);

  mt_gotoXY (x, y);
  (BC[0] & 0x00000001) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000002) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000004) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000008) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000010) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000020) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000040) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000080) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  mt_gotoXY (x + 1, y);
  (BC[0] & 0x00000100) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000200) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000400) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00000800) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00001000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00002000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00004000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00008000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  mt_gotoXY (x + 2, y);
  (BC[0] & 0x00010000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00020000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00040000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00080000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00100000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00200000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00400000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x00800000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  mt_gotoXY (x + 3, y);
  (BC[0] & 0x01000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x02000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x04000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x08000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x10000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x20000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x40000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[0] & 0x80000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);

  mt_gotoXY (x + 4, y);
  (BC[1] & 0x00000001) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000002) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000004) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000008) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000010) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000020) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000040) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000080) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  mt_gotoXY (x + 5, y);
  (BC[1] & 0x00000100) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000200) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000400) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00000800) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00001000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00002000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00004000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00008000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  mt_gotoXY (x + 6, y);
  (BC[1] & 0x00010000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00020000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00040000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00080000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00100000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00200000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00400000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x00800000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  mt_gotoXY (x + 7, y);
  (BC[1] & 0x01000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x02000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x04000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x08000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x10000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x20000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x40000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);
  (BC[1] & 0x80000000) == 0 ? printf (" ") : bc_printA (ACS_CKBOARD);

  return 0;
}

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if ((value != 0 && value != 1) || x < 1 || x > 8 || y < 1 || y > 8)
    {
      sc_regSet (E, 1);
      return -1;
    }

  if (x < 5)
    {
      if (value)
        {
          big[0] = big[0] | (1 << (x * y - 1));
        }
      else
        {
          big[0] = big[0] & (~(1 << (x * y - 1)));
        }
    }
  else
    {
      if (value)
        {
          big[1] = big[1] | (1 << (x * y - 1));
        }
      else
        {
          big[1] = big[1] & (~(1 << (x * y - 1)));
        }
    }

  return 0;
}

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (x < 1 || x > 8 || y < 1 || y > 8)
    {
      sc_regSet (E, 1);
      return -1;
    }

  if (x < 5)
    {
      *value = (big[0] >> (x * y - 1)) & 0x1;
    }
  else
    {
      *value = (big[1] >> (x * y - 1)) & 0x1;
    }
  return 0;
}
