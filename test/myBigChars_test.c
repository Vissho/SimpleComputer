#include <ctest.h>
#include <myBigChars.h>
#include <stdio.h>

CTEST(bc_printA, correctly_mt_bc_printA)
{
    int flag = bc_printA(ACS_CKBOARD);
    ASSERT_EQUAL(0, flag);
}

CTEST(bc_box, correctly_bc_box)
{
    int flag = bc_box(1, 1, 3, 3);
    ASSERT_EQUAL(0, flag);
}

CTEST(bc_printbigchar, correctly_bc_printbigchar)
{
    int flag = bc_printbigchar(BigC[0], 2, 2, cl_default, cl_default);
    ASSERT_EQUAL(0, flag);
}

CTEST(bc_setbigcharpos, correctly_bc_setbigcharpos)
{
    int bb[2];
    int flag = bc_setbigcharpos(bb, 3, 3, 1);
    ASSERT_EQUAL(0, flag);
}

CTEST(bc_getbigcharpos, correctly_bc_getbigcharpos)
{
    int temp = 0;
    bc_getbigcharpos(BigC[0], 1, 3, &temp);
    ASSERT_EQUAL(1, temp);
}

CTEST(bc_bigcharwrite, correctly_bc_bigcharwrite)
{
    int fd = open("x.txt", O_WRONLY);
    int flag = bc_bigcharwrite(fd, BigC[0], 3);
    close(fd);
    ASSERT_EQUAL(0, flag);
}

CTEST(bc_bigcharread, correctly_bc_bigcharread)
{
    int bb[2], temp = 0;
    int fd = open("x.txt", O_RDONLY);
    int flag = bc_bigcharread(fd, bb, 1, &temp);
    close(fd);
    ASSERT_EQUAL(0, flag);
}
